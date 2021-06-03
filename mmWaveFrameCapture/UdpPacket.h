#pragma once
#define PACKET_DATA_SIZE 1456
#define PACKET_BYTECOUNT_SIZE 6
#pragma pack (1)
typedef struct UdpPacket {
    __int32   packetNum;
    __int8    byteCount[PACKET_BYTECOUNT_SIZE];
    __int8    data[PACKET_DATA_SIZE];
}*UdpPacketP;
#pragma pack ()