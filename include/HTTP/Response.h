#pragma once

#include <HTTP/Map.h>

class HTTPResponse
{
	friend class HTTPClient;

public:
	void Reset();

	int GetCode() const;
	const std::string& GetStatus() const;

	const Map& GetHeaders() const;
	const Map& GetCookies() const;
	const std::string& GetData() const;
	const std::string& GetRaw() const;

private:
	// status line
	int _code;
	std::string _status;
	std::string _protover;

	// headers
	Map _headers;
	Map _cookies;

	// data
	std::string _data;

	// full response - raw
	std::string _raw;
};
