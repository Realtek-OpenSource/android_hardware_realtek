#ifndef REALTEK_GUI_SIDEBAND_C_H
#define REALTEK_GUI_SIDEBAND_C_H

#include <system/window.h>
#include <android/native_window.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct SidebandUserHandle SidebandUserHandle;
SidebandUserHandle * SidebandUser_createSurface              (char * name, int w, int h, int format, int usage);
int SidebandUser_connect                    (SidebandUserHandle * handle, int api);
int SidebandUser_disconnect                 (SidebandUserHandle * handle );
int SidebandUser_getMinUndequeuedBuffers    (SidebandUserHandle * handle );
int SidebandUser_setBuffersUserDimensions   (SidebandUserHandle * handle, int w, int h);
int SidebandUser_setBufferFormat            (SidebandUserHandle * handle, int format);
int SidebandUser_setAudioHwSync             (SidebandUserHandle * handle, unsigned int nAudioHwSync);
int SidebandUser_setBufferUsage             (SidebandUserHandle * handle, int usage);
int SidebandUser_setBufferCount             (SidebandUserHandle * handle, int count);
int SidebandUser_dequeue                    (SidebandUserHandle * handle, /* ANativeWindowBuffer*/void ** pANativeWindowBuffer, buffer_handle_t * buffer);
int SidebandUser_enqueue                    (SidebandUserHandle * handle, /* ANativeWindowBuffer*/void ** pANativeWindowBuffer);
int SidebandUser_cancelBuffer               (SidebandUserHandle * handle, /* ANativeWindowBuffer*/void ** pANativeWindowBuffer);
int SidebandUser_creatSidebandStream        (SidebandUserHandle * handle, native_handle_t ** ahandle);
int SidebandUser_destroy                    (SidebandUserHandle * handle );
int SidebandUser_flush                      (SidebandUserHandle * handle );

#ifdef __cplusplus
}
#endif
#endif /* End of REALTEK_GUI_SIDEBAND_C_H */
