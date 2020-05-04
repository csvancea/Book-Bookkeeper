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
	void CMD_Register(const SMap& prompts);
	void CMD_Login(const SMap& prompts);
	void CMD_Logout(const SMap& prompts);
	void CMD_Exit(const SMap& prompts);

	bool _running;
	HTTPClient _client;
	CmdProc _cmd_proc;

	bool _logged_in;

	static constexpr char SERVER_HOST[] = "ec2-3-8-116-10.eu-west-2.compute.amazonaws.com";
	static constexpr int  SERVER_PORT   = 8080;
};
