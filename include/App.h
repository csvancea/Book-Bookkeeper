#pragma once

#include <HTTP/Client.h>
#include <CmdProc.h>

#include <Errors.h>

class Application
{
private:
	Application();
	Application(const Application&) = delete;
	Application(const Application&&) = delete;
	Application& operator=(const Application&) = delete;

public:
	static Application& GetInstance();

	ECode Startup();
	ECode Run();
	ECode Shutdown();

private:
	ECode RegisterCommands();
	void CMD_Register(SMap& prompts);
	void CMD_Login(SMap& prompts);
	void CMD_Logout(SMap& prompts);
	void CMD_Exit(SMap& prompts);

	void CMD_Enter_Library(SMap& prompts);
	void CMD_Get_Books(SMap& prompts);
	void CMD_Get_Book(SMap& prompts);
	void CMD_Add_Book(SMap& prompts);
	void CMD_Delete_Book(SMap& prompts);

	bool _running;
	HTTPClient _client;
	CmdProc _cmd_proc;
	SMap _user_headers;

	static constexpr char SERVER_HOST[] = "ec2-3-8-116-10.eu-west-2.compute.amazonaws.com";
	static constexpr int  SERVER_PORT   = 8080;
};
