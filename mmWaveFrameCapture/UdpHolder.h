#pragma once
#include "UdpProfile.h"
#include<ws2tcpip.h>
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib")
constexpr auto UDP_PACKET_SIZE = 1500;
class UdpHolder
{
private:
    UdpProfile* udppf;
    char receBuf[UDP_PACKET_SIZE];
    SOCKET sockServer;
public:
    UdpHolder(UdpProfile *up);
    int recivePacket(char* packetBuffer);
};

