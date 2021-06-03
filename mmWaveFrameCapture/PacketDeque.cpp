#include "PacketDeque.h"


int PacketDeque::put(struct UdpPacket packet)
{
    PacketDeque::mtx.lock();
    PacketDeque::udpPacketDeque.push_back(packet);
    PacketDeque::mtx.unlock();
    return 0;
}
struct UdpPacket PacketDeque::getFront()
{
    struct UdpPacket p;
    while (PacketDeque::udpPacketDeque.size() < 1) {

    }
    PacketDeque::mtx.lock();
    p = PacketDeque::udpPacketDeque.front();
    PacketDeque::udpPacketDeque.pop_front();
    PacketDeque::mtx.unlock();
    return p;
}

int PacketDeque::clear()
{
    PacketDeque::mtx.lock();
    PacketDeque::udpPacketDeque.clear();
    PacketDeque::mtx.unlock();
    return 0;
}
