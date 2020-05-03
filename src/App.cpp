#include <App.h>
#include <Logger.h>

Application& Application::GetInstance()
{
	static Application app;
	return app;
}

Application::Application() :
	client(SERVER_HOST, SERVER_PORT)
{

}

ECode Application::Startup()
{
	ECode err;
	
	err = HTTPClient::GlobalStartup();
	if (err != ECode::OK) {
		LOG_ERROR("HTTP GlobalStartup failed, errcode: {}", err);
		return err;
	}

	err = client.ResolveHost();
	if (err != ECode::OK) {
		LOG_ERROR("Couldn't resolve host, errcode: {}", err);
		return err;
	}

	return ECode::OK;
}

ECode Application::Run()
{
	client.Request("POST", "/api/v1/auth/login", Map(), "username=student&password=student", "application/x-www-form-urlencoded", Map(), Map());
	client.Request("GET", "/api/v1/weather/key", Map(), "", "", Map(), Map());
	return ECode::OK;
}

ECode Application::Shutdown()
{
	return HTTPClient::GlobalShutdown();
}
