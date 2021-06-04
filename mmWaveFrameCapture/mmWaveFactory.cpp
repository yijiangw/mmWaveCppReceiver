#include "mmWaveFactory.h"

mmWaveFactory::mmWaveFactory(std::string path)
{
    mmWaveFactory::configLD = ConfigLoader(std::string("C:\\Users\\wyj19\\source\\repos\\mmWaveCppReceiver\\config\\config.json"));
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

FrameFileSaver mmWaveFactory::getFrameSaver(std::string path)
{
    return FrameFileSaver(mmWaveFactory::configLD.getFrameProfile(),path);
}
