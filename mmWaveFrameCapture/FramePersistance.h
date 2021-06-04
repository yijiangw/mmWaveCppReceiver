#pragma once
#include <chrono>
#include <list>
enum packetLostStatus { FULLY_SAVED, PACKET_LOST };
class FramePersistance
{
public:
    virtual std::chrono::milliseconds put(__int8* Frame) = 0;
    virtual int count() = 0;
    virtual std::list<std::chrono::milliseconds> getTimeStampLog() = 0;
    virtual std::list<packetLostStatus> getPacketLostLog() = 0;
    virtual int packetLostAnnounce() = 0;
};

