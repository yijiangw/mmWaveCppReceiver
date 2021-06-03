#pragma once
#include "UdpProfile.h"
#include "FrameProfile.h"
#include "json/json.h"
#include <string>
class ConfigLoader
{
public:
    ConfigLoader();
    ConfigLoader(std::string configJsonPath);

    UdpProfile* getUdpProfile();
    FrameProfile* getFrameProfile();
    ~ConfigLoader();
private:
    UdpProfile* up;
    FrameProfile* fp;
};

