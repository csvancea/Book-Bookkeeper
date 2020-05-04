#pragma once

#include <string>
#include <list>
#include <functional>
#include <unordered_map>

#include <Errors.h>
#include <SMap.h>

class CmdProc
{
public:
	using Callback = std::function<void(SMap&)>;

	CmdProc() = default;
	CmdProc(const CmdProc&) = delete;
	CmdProc& operator=(const CmdProc&) = delete;

	ECode Register(const std::string& name, const std::list<std::string>& prompts, Callback callback);
	ECode Unregister(const std::string& name);

	ECode ProcessNewCommand();

private:
	struct Entry {
		Callback callback;
		std::list<std::string> prompts;
	};

	std::unordered_map<std::string, Entry> _commands;
};