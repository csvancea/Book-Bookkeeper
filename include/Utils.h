#pragma once

#include <vector>
#include <string>

namespace Utils
{
	std::vector<std::string> Split(const std::string& str, const std::string& delim);
	std::string Trim(const std::string& str, const std::string& whitespace = " \t");
	std::string ToLower(const std::string& str);
}
