#include "FrameCollection.h"
#include <iostream>

FrameCollection::FrameCollection(PacketDeque* udpPacketDeque, FrameProfile* fp) :udpPacketDeque(udpPacketDeque), fp(fp)
{
    
}

FrameCollection::FrameCollection(PacketDeque* udpPacketDeque, FrameProfile* fp, FramePersistance* frameSaver): udpPacketDeque(udpPacketDeque), fp(fp),frameSaver(frameSaver)
{
}

int FrameCollection::setSaver(FramePersistance* frameSaver)
{

    int lastsaver = (int)FrameCollection::frameSaver;
    FrameCollection::frameSaver = frameSaver;
    return lastsaver;
}

int FrameCollection::start()
{
    FrameCollection::udpPacketDeque->clear();
    int wholeFrameSize = fp->getFrameSize();
    char* frameContainer = (char*)malloc(wholeFrameSize);
    memset(frameContainer, 0, wholeFrameSize);
    int packetNum = 0;
    int lastPacketNum = 0;
    int frameNum = 0;
    int lastFramegatheredCount = 0;
    int boundToFinish = 0;
    //get First Frame head
    std::cout << "FrameC" << std::endl;
    while (1) {
        if (FrameCollection::udpPacketDeque->clear()==0) {
            //std::cout << "FrameC1"<< FrameCollection::udpPacketDeque->size() << std::endl;
            UdpPacket newPacket = FrameCollection::udpPacketDeque->getFront();
            __int64 byteCount = getByteCount(newPacket.byteCount);
            //std::cout << "packetNum" << newPacket.packetNum <<"byteCount"<< byteCount << std::endl;
            packetNum = newPacket.packetNum;
            lastPacketNum = packetNum;
            lastFramegatheredCount = byteCount % wholeFrameSize;
            boundToFinish = wholeFrameSize - sizeof(newPacket.data);
            if (lastFramegatheredCount > boundToFinish) {
                memcpy(frameContainer,
                    newPacket.data + wholeFrameSize - lastFramegatheredCount,
                    lastFramegatheredCount + sizeof(newPacket.data) - wholeFrameSize);       
                break;
            }
        }
    }
    std::cout << "FrameC2" << std::endl;
    while (FrameCollection::threadFlag) {

        if (1) {
            UdpPacket newPacket = FrameCollection::udpPacketDeque->getFront();
            __int64 byteCount = getByteCount(newPacket.byteCount);
            packetNum = newPacket.packetNum;
            lastFramegatheredCount = byteCount % wholeFrameSize;
            boundToFinish = wholeFrameSize - sizeof(newPacket.data);
            //std::cout << "FrameC2" << FrameCollection::udpPacketDeque->size() << std::endl;
            //std::cout << "packetNum" << newPacket.packetNum << "byteCount" << byteCount << std::endl;

            if (lastFramegatheredCount > boundToFinish) {
                //finish last frame
                memcpy(frameContainer,
                    newPacket.data,
                    wholeFrameSize - lastFramegatheredCount);

                if (!FrameCollection::frameAmount || frameNum < FrameCollection::frameAmount) {
                    frameNum++;
                    frameSaver->put(frameContainer);    
                    std::cout << "finish frame" << frameNum << std::endl;

                }
                else {
                    std::cout << "return 1" << std::endl;
                    return 1;
                }
                    
                //start new frame
                memset(frameContainer, 0, wholeFrameSize);

                memcpy(frameContainer,
                    newPacket.data + wholeFrameSize - lastFramegatheredCount,
                    lastFramegatheredCount + sizeof(newPacket.data) - wholeFrameSize);
            }
            else {
                if (packetNum - lastPacketNum > 1) {
                    //lost packet     
                    frameSaver->packetLostAnnounce();
                    std::cout << "LOST PACKET" << packetNum - lastPacketNum << std::endl;
                    if (byteCount / wholeFrameSize > (byteCount - (__int64)(packetNum - lastPacketNum - 1) * sizeof(newPacket.data)) / wholeFrameSize) {
                        // if among two Frames
                        if (!FrameCollection::frameAmount || frameNum < FrameCollection::frameAmount) {
                            frameNum++;                            
                            frameSaver->put(frameContainer);
                            frameSaver->packetLostAnnounce();
                            std::cout << "finish frame"<< frameNum  << std::endl;
                            memset(frameContainer, 0, wholeFrameSize);
                        }
                        else {
                            std::cout << "return 0" << std::endl;
                            return 0;
                        }
                    }                    
                }
                memcpy(frameContainer,
                    newPacket.data,
                    sizeof(newPacket.data));                
            }
            lastPacketNum = packetNum;
        }
    }
    std::cout << "return 2" << std::endl;
    return 2;
}

int FrameCollection::stop()
{
    FrameCollection::threadFlag = 0;
    return 0;
}

int FrameCollection::setFrameAmount(int frameAmount)
{
    FrameCollection::frameAmount = frameAmount;
    return 0;
}

__int64 FrameCollection::getByteCount(char* byteCount3ByteArray)
{
    __int64 llCount = 0;
    memcpy((char*)&llCount, byteCount3ByteArray, 6);
    return llCount;
}
