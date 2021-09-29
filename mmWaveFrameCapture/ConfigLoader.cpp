#include "ConfigLoader.h"
#include "json/json.h"
#include <iostream>
#include <fstream> 
ConfigLoader::ConfigLoader():ConfigLoader::ConfigLoader("config.json")
{    
}

ConfigLoader::ConfigLoader(std::string configJsonPath)
{
    ConfigLoader::up = NULL;
    ConfigLoader::fp = NULL;
    Json::Value node;
    JSONCPP_STRING err;
    const std::string filepath = configJsonPath;
    std::ifstream ifs(filepath);
    
    if (!ifs.is_open()) {
        std::cout << "Config File cannot be found" << std::endl;
    }
    //char buffer[256]; ifs.getline(buffer, 100);
    //std::cout << "aaaaa" << std::endl;
    //std::cout << ifs.is_open() << std::endl;
    std::string jsonstr((std::istreambuf_iterator<char>(ifs)),
        std::istreambuf_iterator<char>());

    Json::CharReaderBuilder builder;
    const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    if (!reader->parse(jsonstr.c_str(), jsonstr.c_str() + static_cast<int>(jsonstr.length()), &node,
        &err)) {
        std::cout << "Config load Fail" << std::endl;
    }
    else { // success std::cout<<<

        ConfigLoader::up = new UdpProfile(
            (int)node["UdpProfile"]["BYTES_IN_PACKET"].asInt(),
            std::string(node["UdpProfile"]["IP"].asString()),
            (__int16)node["UdpProfile"]["PORT"].asInt(),
            (int)node["UdpProfile"]["SOCKET_BUFFER_SIZE"].asInt()
        );
        ConfigLoader::fp = new FrameProfile(
            (int)node["FrameProfile"]["FrameAmount"].asInt(),
            (int)node["FrameProfile"]["chrips"].asInt(),
            (int)node["FrameProfile"]["rx"].asInt(),
            (int)node["FrameProfile"]["tx"].asInt(),
            (int)node["FrameProfile"]["samples"].asInt(),
            (int)node["FrameProfile"]["IQ"].asInt(),
            (int)node["FrameProfile"]["bytes"].asInt(),
            (int)node["FrameProfile"]["LVDStype"].asInt()
        );

    }
}

UdpProfile* ConfigLoader::getUdpProfile()
{
    return ConfigLoader::up;
}

FrameProfile* ConfigLoader::getFrameProfile()
{
    return ConfigLoader::fp;
}

ConfigLoader::~ConfigLoader()
{
    delete fp;
    delete up;
}
