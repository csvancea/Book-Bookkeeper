#include <iostream>
#include <Logger.h>
#include <App.h>

int main()
{
#ifdef ENABLE_LOGGING
    Logger::GetInstance().SetOutputToDebugger(true, Logger::RULE_ALL);
	Logger::GetInstance().SetOutputToFile(true, Logger::RULE_ALL, "dbg");
#endif
	Logger::GetInstance().SetOutputToStdout(true, Logger::RULE_MESSAGE | Logger::RULE_ERROR);


	Application& app = Application::GetInstance();
	ECode err;

	err = app.Startup();
	if (err != ECode::OK) {
		LOG_ERROR("Can't start application, errcode: {}", err);
		return EXIT_FAILURE;
	}

	err = app.Run();
	if (err != ECode::OK) {
		LOG_ERROR("Runtime error, errcode: {}", err);
		return EXIT_FAILURE;
	}

	err = app.Shutdown();
	if (err != ECode::OK) {
		LOG_ERROR("Can't shutdown application, errcode: {}", err);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
