#include "FrameFileSaver.h"

FrameFileSaver::FrameFileSaver() {
    FrameFileSaver::frameSize = 0;
}
FrameFileSaver::FrameFileSaver(FrameProfile *p):FrameFileSaver(p,"FrameData.dat"){}
FrameFileSaver::FrameFileSaver(FrameProfile *p, std::string path) {
    FrameFileSaver::frameSize = p->getFrameSize();
    FrameFileSaver::outfile.open(path,std::ios::app);
}
FrameFileSaver::~FrameFileSaver()
{
    FrameFileSaver::outfile.close();
}
std::chrono::milliseconds FrameFileSaver::put(__int8* Frame) {
    outfile.write(Frame, frameSize);
    auto msTimeStamp = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
        );
    msTimeStampList.push_back(msTimeStamp);
    frameNum++;
    return msTimeStamp;
}

std::list<std::chrono::milliseconds> FrameFileSaver::getTimeStampLog() {
    return msTimeStampList;
}

int FrameFileSaver::count() {
    return FrameFileSaver::frameNum;
}