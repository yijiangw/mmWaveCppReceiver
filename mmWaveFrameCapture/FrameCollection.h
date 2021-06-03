#pragma once
#include <deque>
#include "UdpPacket.h"
#include "FramePersistance.h"
#include "FrameProfile.h"
#include "PacketDeque.h"
class FrameCollection
{
public:
    FrameCollection(PacketDeque* udpPacketDeque, FrameProfile* fp) ;
    FrameCollection(PacketDeque* udpPacketDeque, FrameProfile* fp, FramePersistance* frameSaver);
    int setSaver(FramePersistance* frameSaver);
    int start();
    int stop();
    int setFrameAmount(int frameAmount);
private:
    __int64 getByteCount(char * byteCount3ByteArray);
    int threadFlag = 1;
    PacketDeque* udpPacketDeque;
    FrameProfile* fp;
    FramePersistance* frameSaver = 0;
    int frameAmount = 0;
};

