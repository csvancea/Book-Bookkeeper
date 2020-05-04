#pragma once

#include <SMap.h>

class HTTPResponse
{
	friend class HTTPClient;

public:
	void Reset();

	int GetCode() const;
	const std::string& GetStatus() const;

	const SMap& GetHeaders() const;
	const SMap& GetCookies() const;
	const std::string& GetData() const;
	const std::string& GetRaw() const;

private:
	// status line
	int _code;
	std::string _status;
	std::string _protover;

	// headers
	SMap _headers;
	SMap _cookies;

	// data
	std::string _data;

	// full response - raw
	std::string _raw;
};
