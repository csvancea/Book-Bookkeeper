#pragma once

#include <HTTP/Response.h>
#include <HTTP/System.h>
#include <HTTP/Map.h>

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
		const Map& query_params = Map(), const std::string& data = "", const std::string& content_type = "",
		const Map& user_headers = Map(), const Map& user_cookies = Map());

	ECode Get(HTTPResponse& response, const std::string& path, const Map& query_params = Map(),
		const Map& user_headers = Map(), const Map& user_cookies = Map());
	ECode Post(HTTPResponse& response, const std::string& path, const Map& query_params = Map(),
		const std::string& data = "", const std::string& content_type = "",
		const Map& user_headers = Map(), const Map& user_cookies = Map());
	ECode Delete(HTTPResponse& response, const std::string& path, const Map& query_params = Map(),
		const Map& user_headers = Map(), const Map& user_cookies = Map());

	ECode ResolveHost();

private:
	SOCKET Connect();
	void Disconnect(SOCKET sockfd);
	ECode Send(SOCKET sockfd, const std::string& request);
	ECode Receive(SOCKET sockfd, HTTPResponse& response);

	std::string FormatRequest(
		const std::string& method, const std::string& path, const Map& query_params, const std::string& data,
		const std::string& content_type, const Map& headers, const Map& cookies);

	ECode ParseResponse(HTTPResponse& response);
	void SetupSystemHeaders();

private:
	std::string _unresolved_host;
	int _port;
	sockaddr _address;

	Map _system_headers;
	Map _system_cookies;

	static constexpr char HTTP_VERSION[] = "HTTP/1.1";
};
