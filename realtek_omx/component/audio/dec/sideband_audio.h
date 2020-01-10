#ifndef SIDEBAND_OMX_AUDIO_H
#define SIDEBAND_OMX_AUDIO_H

#ifdef __cplusplus
extern "C" {
#endif
   int getSharedFd(int resource, int* shareFd);
   int destroySharedFd(int resource);
#ifdef __cplusplus
}
#endif
#endif /* End of SIDEBAND_OMX_AUDIO_H */
