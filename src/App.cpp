#include <App.h>
#include <Logger.h>

Application& Application::GetInstance()
{
	static Application app;
	return app;
}

Application::Application() :
	_running(true), _client(SERVER_HOST, SERVER_PORT)
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

	err = _client.ResolveHost();
	if (err != ECode::OK) {
		LOG_ERROR("Couldn't resolve host, errcode: {}", err);
		return err;
	}

	err = RegisterCommands();
	if (err != ECode::OK) {
		LOG_ERROR("Couldn't register commands, errcode: {}", err);
		return err;
	}

	return ECode::OK;
}

ECode Application::Run()
{
	HTTPResponse response;

	_client.Post(response, "/api/v1/auth/login", SMap(), "username=student&password=student", "application/x-www-form-urlencoded");
	_client.Get(response, "/api/v1/weather/key");

	while (_running) {
		_cmd_proc.ProcessNewCommand();
	}
	return ECode::OK;
}

ECode Application::Shutdown()
{
	return HTTPClient::GlobalShutdown();
}

#define REGISTER(name, ...) _cmd_proc.Register(#name, {## __VA_ARGS__}, std::bind(&Application::CMD_ ## name, this, std::placeholders::_1))
ECode Application::RegisterCommands()
{
	ECode err;

	err = REGISTER(Exit);
	if (err != ECode::OK) return err;

	return ECode::OK;
}

void Application::CMD_Exit(const SMap& prompts)
{
	(void)prompts; // supress unused warning

	_running = false;
}
