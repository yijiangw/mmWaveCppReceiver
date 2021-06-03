#include "FrameProfile.h"

__int32 FrameProfile::getFrameSize()
{
    return chrips*rx*tx*samples*IQ*bytes;
}
