#ifndef _CAMERA_HAL3_FACTORY_
#define _CAMERA_HAL3_FACTORY_

//#include "CameraHardware3.h"
#include "CameraHardware3v2.h"

using namespace android;
using namespace androidcamera3;

namespace androidcamera3{

CameraHardware3Base *createCamera(
    int id,
    int v4l2Id,
    int facing);

};

#endif //_CAMERA_HAL3_FACTORY_


