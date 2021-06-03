#pragma once
#include "UdpHolder.h"
#include <deque>
#include "UdpPacket.h"
#include "PacketDeque.h"
class PacketCapture
{
public:
    PacketCapture(UdpHolder* uh, PacketDeque* udpPacketDeque);
    int start();
    int stop() { PacketCapture::threadFlag = 0; return 0; }
private:
    UdpHolder* uh;
    int threadFlag = 1;
    PacketDeque* udpPacketDeque;
};

