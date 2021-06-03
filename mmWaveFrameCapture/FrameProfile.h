#pragma once
class FrameProfile
{
public:
    __int32 FrameAmount;
    __int32 chrips;
    __int32 rx;
    __int32 tx;
    __int32 samples;
    __int32 IQ;
    __int32 bytes;
    __int32 LVDStype;
    FrameProfile(__int32 FrameAmount,__int32 chrips,__int32 rx,__int32 tx,__int32 samples,__int32 IQ,__int32 bytes,__int32 LVDStype):FrameAmount(FrameAmount),chrips(chrips), rx(rx),tx(tx),samples(samples),IQ(IQ),bytes(bytes), LVDStype(LVDStype){}
    __int32 getFrameSize();
};

