#include <Errors.h>

#define CASE(code) case ECode::code: ret = #code; break;
std::ostream &operator<<(std::ostream& os, ECode ec)
{
    std::string ret;

    switch (ec) {
    CASE(OK)
    CASE(WSA_STARTUP)
    CASE(HOST_ADDRINFO)
    CASE(HOST_NORESULT)
    CASE(SOCKET_CREATE)
    CASE(SOCKET_CONNECT)
    CASE(SOCKET_SEND)
    CASE(SOCKET_RECV)
    CASE(CMD_ALREADYREGISTERED)
    CASE(CMD_NOTREGISTERED)
    CASE(CMD_EMPTY)
    CASE(CMD_UNKNOWN)

    default: ret = fmt::format("unknown error ({})", static_cast<int>(ec));      
    }

    return os << ret;
}
