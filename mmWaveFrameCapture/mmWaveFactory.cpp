#include "mmWaveFactory.h"

mmWaveFactory::mmWaveFactory(std::string path):configLD(path)
{    
}

PacketCapture mmWaveFactory::getPacketCaptureTask()
{
    PacketCapture task(new UdpHolder(mmWaveFactory::configLD.getUdpProfile()), mmWaveFactory::udpPacketDeque);
    return task;
}

FrameCollection mmWaveFactory::getFrameCollectionTask()
{
    FrameCollection task(mmWaveFactory::udpPacketDeque, mmWaveFactory::configLD.getFrameProfile());
    return task;
}

FrameCollection mmWaveFactory::getFrameCollectionTask(int frameCount, FramePersistance* saver)
{
    FrameCollection task(mmWaveFactory::udpPacketDeque, mmWaveFactory::configLD.getFrameProfile());
    task.setSaver(saver);
    task.setFrameAmount(frameCount);
    return task;
}

FrameFileSaver* mmWaveFactory::getFrameSaver(std::string path)
{
    FrameFileSaver *ffs = new FrameFileSaver(mmWaveFactory::configLD.getFrameProfile(), path);
    return ffs;
}
