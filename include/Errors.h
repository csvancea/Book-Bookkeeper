#pragma once

#include <fmt/ostream.h>

enum class ECode
{
    OK,

    WSA_STARTUP,

    HOST_ADDRINFO,
    HOST_NORESULT,

    SOCKET_CREATE,
    SOCKET_CONNECT,
    SOCKET_SEND,
    SOCKET_RECV,

    CMD_ALREADYREGISTERED,
    CMD_NOTREGISTERED,
    CMD_EMPTY,
    CMD_UNKNOWN
};

std::ostream &operator<<(std::ostream& os, ECode ec);
