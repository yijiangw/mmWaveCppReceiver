#pragma once
#include <deque>
#include <mutex>
#include "UdpPacket.h"
class PacketDeque
{
public:
    int put(struct UdpPacket packet);
    struct UdpPacket getFront();
    int clear();
private:
    const int OverwhlemValue = 10000;
    int antiOverwhlemIndex = 0;
    std::mutex mtx;
    std::deque<struct UdpPacket> udpPacketDeque;
};

