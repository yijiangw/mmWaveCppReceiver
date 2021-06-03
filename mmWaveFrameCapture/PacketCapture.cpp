#include "PacketCapture.h"

PacketCapture::PacketCapture(UdpHolder* uh, PacketDeque* udpPacketDeque)
{ 
    PacketCapture::uh = uh;
    PacketCapture::udpPacketDeque = udpPacketDeque;
}

int PacketCapture::start()
{
    char* newPacket = (char*)malloc(sizeof(UdpPacket));
    memset(newPacket, 0, sizeof(UdpPacket));
    int packetnum = 0;
    while (PacketCapture::threadFlag) {
        uh->recivePacket(newPacket);
        //UdpPacket t = *(UdpPacket*)newPacket;
        udpPacketDeque->put(*(UdpPacket *)newPacket);
        packetnum++;
    }    
    free(newPacket);
    return packetnum;

}
