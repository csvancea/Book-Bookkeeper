#include <Errors.h>

std::ostream &operator<<(std::ostream& os, ECode ec)
{
    std::string ret;

    switch (ec) {
    case ECode::OK: ret = "OK"; break;
    case ECode::WSA_STARTUP: ret = "WSA_STARTUP"; break;
    case ECode::HOST_ADDRINFO: ret = "HOST_ADDRINFO"; break;
    case ECode::HOST_NORESULT: ret = "HOST_NORESULT"; break;
    case ECode::SOCKET_CREATE: ret = "SOCKET_CREATE"; break;
    case ECode::SOCKET_CONNECT: ret = "SOCKET_CONNECT"; break;
    case ECode::SOCKET_SEND: ret = "SOCKET_SEND"; break;
    case ECode::SOCKET_RECV: ret = "SOCKET_RECV"; break;

    default: ret = fmt::format("unknown error ({})", static_cast<int>(ec));      
    }

    return os << ret;
}
