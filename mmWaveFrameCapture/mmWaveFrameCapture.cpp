// mmWaveFrameCapture.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>
#include <future>
#include "PacketDeque.h"
#include "FrameFileSaver.h"
#include "FrameCollection.h"
#include "UdpHolder.h"
#include "PacketCapture.h"
#include "ConfigLoader.h"
#include "FrameFileSaver.h"
int main()
{
    ConfigLoader configLD(std::string("C:\\Users\\wyj19\\source\\repos\\mmWaveCppReceiver\\config\\config.json"));
    PacketDeque* udpPacketDeque = new PacketDeque();
    PacketCapture myPacketCapture(new UdpHolder(configLD.getUdpProfile()), udpPacketDeque);
    FramePersistance* mySaver = new FrameFileSaver(configLD.getFrameProfile(),std::string("frameDataTest.dat"));
    FrameCollection myFrameCollection(udpPacketDeque, configLD.getFrameProfile(), mySaver);
    std::future<int>f = std::async(&PacketCapture::start, &myPacketCapture);
    myFrameCollection.setFrameAmount(10);
    std::future<int> f1=std::async(std::launch::async,&FrameCollection::start, &myFrameCollection);
    f1.get();
    std::cout << "Finished!\n";
    myPacketCapture.stop();
    std::list<std::chrono::milliseconds>  timeStampList = mySaver->getTimeStampLog();
    std::list<std::chrono::milliseconds>::iterator it;
    it = timeStampList.begin();
    while (it != timeStampList.end()) {
        std::cout << it->count() << std::endl;
        it++;
    }
    
    delete mySaver;

    std::cout << "Finished!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
