#include <App.h>
#include <Logger.h>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

Application& Application::GetInstance()
{
	static Application app;
	return app;
}

Application::Application() :
	_running(true), _client(SERVER_HOST, SERVER_PORT), _logged_in(false)
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

	err = REGISTER(Register, "username", "password"); if (err != ECode::OK) return err;
	err = REGISTER(Login,    "username", "password"); if (err != ECode::OK) return err;
	err = REGISTER(Logout);                           if (err != ECode::OK) return err;
	err = REGISTER(Exit);                             if (err != ECode::OK) return err;

	return ECode::OK;
}

void Application::CMD_Register(const SMap& prompts)
{
	json body(prompts);
	HTTPResponse response;
	ECode err;

	err = _client.Post(response, "/api/v1/tema/auth/register", SMap(), body.dump(), "application/json");
	if (err != ECode::OK) {
		LOG_ERROR("HTTP POST failed, errcode: {}", err);
		return;
	}

	if (response.GetCode() != 201) {
		std::string error;
		try {
			error = json::parse(response.GetData())["error"];
		}
		catch (...) {
			error = "--no error object--";
		}

		LOG_ERROR("Account NOT registered!");
		LOG_ERROR("Response: {} {} - {}", response.GetCode(), response.GetStatus(), error);
		// LOG_DEBUG("Raw HTTP response:\n{}", response.GetRaw());
		return;
	}

	LOG_MESSAGE("Account registered!");
}

void Application::CMD_Login(const SMap& prompts)
{
	if (_logged_in) {
		LOG_ERROR("You are already logged in!");
		return;
	}

	json body(prompts);
	HTTPResponse response;
	ECode err;

	err = _client.Post(response, "/api/v1/tema/auth/login", SMap(), body.dump(), "application/json");
	if (err != ECode::OK) {
		LOG_ERROR("HTTP POST failed, errcode: {}", err);
		return;
	}

	if (response.GetCode() != 200) {
		std::string error;
		try {
			error = json::parse(response.GetData())["error"];
		}
		catch (...) {
			error = "--no error object--";
		}

		LOG_ERROR("Can't log in!");
		LOG_ERROR("Response: {} {} - {}", response.GetCode(), response.GetStatus(), error);
		// LOG_DEBUG("Raw HTTP response:\n{}", response.GetRaw());
		return;
	}

	LOG_MESSAGE("Logged in!");
	_logged_in = true;
}

void Application::CMD_Logout(const SMap& prompts)
{
	if (!_logged_in) {
		LOG_ERROR("You are not logged in!");
		return;
	}

	HTTPResponse response;
	ECode err;

	err = _client.Get(response, "/api/v1/tema/auth/logout");
	if (err != ECode::OK) {
		LOG_ERROR("HTTP GET failed, errcode: {}", err);
		return;
	}

	if (response.GetCode() != 200) {
		std::string error;
		try {
			error = json::parse(response.GetData())["error"];
		}
		catch (...) {
			error = "--no error object--";
		}

		LOG_ERROR("Can't log out!");
		LOG_ERROR("Response: {} {} - {}", response.GetCode(), response.GetStatus(), error);
		// LOG_DEBUG("Raw HTTP response:\n{}", response.GetRaw());
		return;
	}

	LOG_MESSAGE("Logged out!");
	_logged_in = false;
	_client.ClearCookies();
}

void Application::CMD_Exit(const SMap&)
{
	_running = false;
}
