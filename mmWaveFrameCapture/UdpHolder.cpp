#include "UdpHolder.h"


UdpHolder::UdpHolder(UdpProfile* up)
{
    memset(UdpHolder::receBuf, 0, UDP_PACKET_SIZE);
    UdpHolder::udppf = up;
    WSADATA WSAData;

    if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0) {
        printf("初始化失败");
        exit(1);
    }
    UdpHolder::sockServer = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (UdpHolder::sockServer == INVALID_SOCKET)
    {
        printf("Failed socket() \n");
    }
    SOCKADDR_IN addr_Server; //服务器的地址等信息
    addr_Server.sin_family = AF_INET;
    addr_Server.sin_port = htons(UdpHolder::udppf->PORT);
    void* set_addr = malloc(sizeof(in_addr));
    inet_pton(AF_INET, UdpHolder::udppf->IP.c_str(), set_addr);
    addr_Server.sin_addr.S_un.S_addr = ((in_addr*)set_addr)->S_un.S_addr;
    if (bind(UdpHolder::sockServer, (SOCKADDR*)&addr_Server, sizeof(addr_Server)) == SOCKET_ERROR) {//服务器与本地地址绑定
        printf("Failed socket() %d \n", WSAGetLastError());
    }
    int fromlen = sizeof(SOCKADDR);

    int nRecvBuf = UdpHolder::udppf->SOCKET_BUFFER_SIZE;//设置为32K
    setsockopt(UdpHolder::sockServer, SOL_SOCKET, SO_RCVBUF, (const char*)&nRecvBuf, sizeof(int));
}

int UdpHolder::recivePacket(char* packetBuffer)
{
    SOCKADDR_IN addr_Clt;
    int fromlen = sizeof(SOCKADDR);
    recvfrom(UdpHolder::sockServer, UdpHolder::receBuf, UDP_PACKET_SIZE, 0, (SOCKADDR*)&addr_Clt, &fromlen);
    memcpy(packetBuffer, UdpHolder::receBuf, UdpHolder::udppf->BYTES_IN_PACKET);
    return 1;
}
