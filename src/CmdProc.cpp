#include <CmdProc.h>
#include <Logger.h>
#include <Utils.h>

#include <iostream>

ECode CmdProc::Register(const std::string& name, const std::list<std::string>& prompts, Callback callback)
{
	std::string lower_name = Utils::ToLower(name);

	if (_commands.find(lower_name) != _commands.end()) {
		return ECode::CMD_ALREADYREGISTERED;
	}

	Entry e;
	e.callback = callback;
	e.prompts = prompts;

	_commands[lower_name] = std::move(e);
	return ECode::OK;
}

ECode CmdProc::Unregister(const std::string& name)
{
	std::string lower_name = Utils::ToLower(name);

	auto it = _commands.find(lower_name);
	if (it == _commands.end()) {
		return ECode::CMD_NOTREGISTERED;
	}

	_commands.erase(it);
	return ECode::OK;
}

ECode CmdProc::ProcessNewCommand()
{
	std::string cmd_name;
	std::getline(std::cin, cmd_name);
	cmd_name = Utils::ToLower(cmd_name);
	if (cmd_name.length() == 0) {
		return ECode::CMD_EMPTY;
	}

	auto cmd = _commands.find(cmd_name);
	if (cmd == _commands.end()) {
		LOG_WARNING("Invalid command: {}", cmd_name);
		return ECode::CMD_UNKNOWN;
	}

	SMap user_response;
	for (const auto& prompt : cmd->second.prompts) {
		std::cout << prompt << "=";
		std::getline(std::cin, user_response[prompt]);
	}

	cmd->second.callback(user_response);
	return ECode::OK;
}
