#include <iostream>
#include <Logger.h>

int main()
{
#ifdef ENABLE_LOGGING
    Logger::GetInstance().SetOutputToDebugger(true, Logger::RULE_ALL);
	Logger::GetInstance().SetOutputToFile(true, Logger::RULE_ALL, "dbg");
#endif
	Logger::GetInstance().SetOutputToStdout(true, Logger::RULE_MESSAGE | Logger::RULE_ERROR);

	LOG_MESSAGE("ELHO world!");
	return 0;
}
