#include <HTTP/Response.h>

void HTTPResponse::Reset()
{
	_protover.clear();
	_code = 0;
	_status.clear();
	_headers.clear();
	_cookies.clear();
	_data.clear();
}

int HTTPResponse::GetCode() const
{
	return _code;
}

const std::string& HTTPResponse::GetStatus() const
{
	return _status;
}

const SMap& HTTPResponse::GetHeaders() const
{ 
	return _headers;
}

const SMap& HTTPResponse::GetCookies() const
{
	return _cookies;
}

const std::string& HTTPResponse::GetData() const
{
	return _data;
}

const std::string& HTTPResponse::GetRaw() const
{
	return _raw;
}
