#pragma once

#include <HTTP/Response.h>
#include <HTTP/System.h>

#include <SMap.h>
#include <Errors.h>

#include <string>
#include <unordered_map>

class HTTPClient
{
public:
	HTTPClient(const std::string& server_host, int server_port);
	HTTPClient(const HTTPClient&) = delete;
	HTTPClient& operator=(const HTTPClient&) = delete;

	static ECode GlobalStartup();
	static ECode GlobalShutdown();

	ECode Request(
		HTTPResponse& response, const std::string& method, const std::string& path,
		const SMap& query_params = SMap(), const std::string& data = "", const std::string& content_type = "",
		const SMap& user_headers = SMap(), const SMap& user_cookies = SMap());

	ECode Get(HTTPResponse& response, const std::string& path, const SMap& query_params = SMap(),
		const SMap& user_headers = SMap(), const SMap& user_cookies = SMap());
	ECode Post(HTTPResponse& response, const std::string& path, const SMap& query_params = SMap(),
		const std::string& data = "", const std::string& content_type = "",
		const SMap& user_headers = SMap(), const SMap& user_cookies = SMap());
	ECode Delete(HTTPResponse& response, const std::string& path, const SMap& query_params = SMap(),
		const SMap& user_headers = SMap(), const SMap& user_cookies = SMap());

	void ClearCookies();
	ECode ResolveHost();

private:
	SOCKET Connect();
	void Disconnect(SOCKET sockfd);
	ECode Send(SOCKET sockfd, const std::string& request);
	ECode Receive(SOCKET sockfd, HTTPResponse& response);

	std::string FormatRequest(
		const std::string& method, const std::string& path, const SMap& query_params, const std::string& data,
		const std::string& content_type, const SMap& headers, const SMap& cookies);

	ECode ParseResponse(HTTPResponse& response);
	void SetupSystemHeaders();

private:
	std::string _unresolved_host;
	int _port;
	sockaddr _address;

	SMap _system_headers;
	SMap _system_cookies;

	static constexpr char HTTP_VERSION[] = "HTTP/1.1";
};
