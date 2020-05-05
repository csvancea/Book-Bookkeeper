# tema3pc - Cosmin-Razvan VANCEA - 323CA


Build & Run:
------------
* `make build` - compileaza clientul
* `make run`   - porneste clientul

Pentru un output verbose cu mesaje care arata si cererile/raspunsurile HTTP
in intregime, decomenteaza prima linie din `Makefile`, apoi `make clean && make`


Structura:
----------
* Codul este impartit in 3 parti majore:
  1. client HTTP
  2. procesor de comenzi
  3. aplicatie

* Clientul HTTP (HTTP/Client.cpp) are urmatoarele roluri:
  - deschide si inchide conexiunea cu serverul
  - o instanta a acestei clase reprezinta o conexiune cu un anumit server HTTP
  - trimite si primeste datele
  - genereaza cererea HTTP pe baza datelor primite de la utilizator
  - parseaza raspunsul primit de la server si returneaza un obiect `HTTPResponse`
  (contine status code, headerele, cookie-urile si body-ul primit)
  - tine minte eventualele cookie-uri primite si le insereaza automat in
  request-urile urmatoare
  - face resolve name -> IP
  - clasa expune utilizatorului metode pentru a face cereri GET, POST si DELETE
  - utilizatorul poate specifica daca doreste ca cererea sa sa aiba headere sau
  cookies in plus (parametrii user_headers si user_cookies; functionalitate
  folosita inserarea tokenului JWT in cererile pentru librarie)
  - tema a fost realizata pe Windows (debugging mai usor cu Visual Studio),
  iar pentru a folosi orice functie pe socket trebuie mai intai initializat
  modulul pentru sockets, asa ca din cauza asta exista functiile GlobalStartup
  si GlobalShutdown; pe Linux nu sunt folosite.

* Procesorul de comenzi (CmdProc.cpp) proceseaza comenzile:
  - o comanda este formata din:
    - numele comenzii (eg: `register`)
    - parametrii asteptati (eg: `username` si `password`)
    - un callback care va primi ca parametru un map cu:
      - key   = numele prompt-ului (eg: `username`)
      - value = raspunsul utilizatorului
    
  - dispune de functii care permit adaugarea si stergerea de comenzi
  - procesorul citeste de la stdin, verifica daca s-a citit o comanda,
  se ofera prompt-urile (daca exista), iar la final se apeleaza callbackul
  asociat comenzii

  * Aplicatia (App.cpp) imbina cele 2 componente de mai sus:
    - se ocupa de initializarea clientului HTTP (Application::Startup)
      - incepe resolve name -> IP
      - inregistreaza comenzile la procesorul de comenzi
    - contine functiile asociate comenzilor (eg: CMD_Login)
    - toate comenzile se comporta in general la fel:
      1. se valideaza parametrii (daca e necesar)
      2. se genereaza obiectul JSON pe baza parametrilor comenzii (daca e necesar)
      3. se trimite cererea
      4. se verifica daca a aparut vreo eroare la conectare/trimitere/primire/parsare
      5. se verifica ce status code a dat serverul
         - daca e 2xx, se afiseaza raspunsul (ex: cartile de la get_books) si un mesaj
         de informare
         - daca nu e,  se citeste campul `error` din body (daca exista) si se afiseaza
         status code, status text si mesajul de eroare venit de la server


Biblioteci:
-----------
* nlohmann/json - pentru generarea obiectelor JSON pe baza inputului de la user
                  si pentru citirea raspunsului de la server
* fmtlib        - diverse formatari necesare la logging si la generarea cererii HTTP


Probleme:
---------
* Cateodata cand vreau sa ma conectez la serverul HTTP sa trimit o comanda,
apelul `connect` da timeout peste 10 secunde si returneaza `EAGAIN (11)`
Daca se intampla asta la testare, doar mai rulati comanda o data si ar trebui
sa mearga la urmatoarea incercare.
* Cel mai probabil nu e de la cod, ci de la conexiunea la internet pentru
ca mi se intampla ceva asemanator si in browser, dar merita mentionat totusi :)
