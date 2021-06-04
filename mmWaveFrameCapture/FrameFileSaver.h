#pragma once
#include "FramePersistance.h"
#include "FrameProfile.h"
#include <string>
#include <fstream>
#include <chrono>
#include <list>
class FrameFileSaver :
    public FramePersistance
{
public:
    FrameFileSaver();
    FrameFileSaver(FrameProfile *p);
    FrameFileSaver(FrameProfile *p,std::string path);
    ~FrameFileSaver();
    virtual std::chrono::milliseconds put(__int8* Frame);
    virtual int count();
    virtual std::list<std::chrono::milliseconds> getTimeStampLog();
private:
    int frameNum = 0;
    std::list<std::chrono::milliseconds> msTimeStampList;
    int frameSize;
    std::ofstream outfile;
    std::list<packetLostStatus> packetLostList;

    // ͨ�� FramePersistance �̳�
    virtual std::list<packetLostStatus> getPacketLostLog() override;
    packetLostStatus recentPacketLostStatus = FULLY_SAVED;

    // ͨ�� FramePersistance �̳�
    virtual int packetLostAnnounce() override;
};

