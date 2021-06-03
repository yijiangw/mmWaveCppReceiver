#pragma once
#include <string>
class UdpProfile
{
public:
    const __int32 BYTES_IN_PACKET;
    const std::string IP;
    const __int16 PORT;
    const __int32 SOCKET_BUFFER_SIZE;

    UdpProfile(__int32 BYTES_IN_PACKET, std::string IP, __int16 PORT, __int32 SOCKET_BUFFER_SIZE) :
        BYTES_IN_PACKET(BYTES_IN_PACKET), IP(IP), PORT(PORT), SOCKET_BUFFER_SIZE(SOCKET_BUFFER_SIZE) {}

};

