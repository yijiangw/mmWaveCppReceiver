#pragma once
#include "PacketDeque.h"
#include "FrameFileSaver.h"
#include "FrameCollection.h"
#include "PacketCapture.h"
#include "ConfigLoader.h"
#include "FrameFileSaver.h"
#include <iostream>
class mmWaveFactory
{
public:
    mmWaveFactory(std::string path);
    PacketCapture getPacketCaptureTask();
    FrameCollection getFrameCollectionTask();
    FrameCollection getFrameCollectionTask(int frameCount, FramePersistance* saver);
    FrameFileSaver* getFrameSaver(std::string path);
       

private:
    ConfigLoader configLD;
    PacketDeque* udpPacketDeque = new PacketDeque();
};

