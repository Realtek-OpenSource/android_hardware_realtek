#ifndef _CAMERA3_EXIF_HELPER_
#define _CAMERA3_EXIF_HELPER_

#include "libjpeg/jpeg-data.h"
#include "Base.h"
#include "Common.h"

using namespace android;

namespace android_camera_hal3 {

ExifEntry* my_exif_create_value (
    ExifData *ed,
    ExifTag tag,
    ExifIfd ifd);

void convert_to_entry (
    const char *set_value,
    double gdvalue,
    ExifEntry *e,
    ExifByteOrder o);

bool add_exif(JPEG_RST_INFO *pInfo,
        uint8_t *metaBuf,
        /* , uint32_t bufSize */
        MISC_FIELD_INFO *pMiscInfo);
};

#endif // _CAMERA3_EXIF_HELPER_
