#pragma once
#include <chrono>
#include <list>
class FramePersistance
{
public:
    virtual std::chrono::milliseconds put(__int8* Frame) = 0;
    virtual int count() = 0;
    virtual std::list<std::chrono::milliseconds> getTimeStampLog() = 0;
};

