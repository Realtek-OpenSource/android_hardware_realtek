#ifndef _RVSD_INBANDAPI_H_
#define _RVSD_INBANDAPI_H_

#include <pthread.h>
//#include "rvsd_def.h"
#include "InbandAPI.h"

#define DUMMY_RING_BUFFER_SIZE      (1024*256*2)
#define DUMMY_PACKET_SIZE (250)

// structure
typedef struct DUMMY_RINGBUFFER
{
    char            *buffer;
    int         ringSize;
    long        readptr;
    long        writeptr;
    int         isEOS;  // wait to remove.
    int         bWillReadFromVobuWptr;  // set 1 when RtkSource::read() needs to prepare the bistream from vobu wptr to next PQ's wptr later. set 0 when prepared the bitstream from vobu wptr to next PQ's wptr.
    unsigned int newVobuWptr;           // the wptr of the new vobu cmd
    unsigned int lastPreparedBSWptr;    // for check if wptr of every prepared data is continuous
#if AUDIO_DECODE_ACODEC
    int         DoFlush;
#endif
    pthread_mutex_t bufferMutex;   // protect this structure
} rvsdRingBuffer_t;

void rvsdRingBuffer_init(rvsdRingBuffer_t *ring);
void rvsdRingBuffer_clean(rvsdRingBuffer_t *ring);
int rvsdRingBuffer_read(rvsdRingBuffer_t *ring, char *buf, int size);
int rvsdRingBuffer_write(rvsdRingBuffer_t *ring, const unsigned char *inbuf, int inbufSize);
int rvsdRingBuffer_getAvail(rvsdRingBuffer_t *ring);
int rvsdRingBuffer_flush(rvsdRingBuffer_t *ring);
int rvsdRingBuffer_peek(rvsdRingBuffer_t *ring, char *buf, int size);
void rvsdRingBuffer_show(rvsdRingBuffer_t *ring);


typedef enum
{
    /* Audio Decoder In-band Command */
    AUDIO_DEC_INBAND_CMD_TYPE_PTS = 0,
    AUDIO_DEC_INBAND_CMD_TYPE_NEW_SEG = 1,      /* let begin_AGC_gain = 1 */
    AUDIO_DEC_INBAMD_CMD_TYPE_NEW_FORMAT = 2,
    AUDIO_DEC_INBAND_CMD_TYPE_EOS = 3,          /* Can not be passed, sent back to system */
    AUDIO_DEC_INBAND_CMD_TYPE_CONTEXT = 4,      /* write debug information, need a RPC_ToSystem command *//*
Can not be passed, sent back to system */
    AUDIO_DEC_INBAND_CMD_TYPE_DECODE = 5,       /* Information for each decoder is inclueded */
    AUDIO_DEC_INABND_CMD_TYPE_PTS_SKIP = 6,
    AUDIO_DEC_INBAND_CMD_TYPE_PRIVATE_INFO = 7,
    AUDIO_DEC_INBAND_CMD_TYPE_VORBIS_PACKETINFO = 8,    /* Information about vorbis packets */

    AUDIO_DEC_INBAND_CMD_TYPE_BS_DISCONTINUITY = 9,
    AUDIO_DEC_INBAND_CMD_TYPE_RESYNC = 10,
    AUDIO_DEC_INBAND_CMD_TYPE_CGMS_INFO = 11,
    AUDIO_DEC_INBAND_CMD_TYPE_RALSD_INFO = 12,
    AUDIO_DEC_INBAND_CMD_TYPE_WMAPRO_DRC = 13,
    AUDIO_DEC_INBAND_CMD_TYPE_WMAPRO_DWNMIX_MTRX = 14,

    AUDIO_DEC_INBAND_CMD_TYPE_EMPHASIS = 15,        // for lpcm emphasis info

#ifndef AUDIO_TV_PLATFORM_TEMP
    AUDIO_DEC_INBAND_CMD_TYPE_APE_SKIP_BIT = 17,
#endif
    /* Audio AO Mixer In-band Command */
    AUDIO_AO_MIXER_INBAND_CMD_TYPE_SET_MIXER_RPTS = 64,
    AUDIO_AO_MIXER_INBAND_CMD_TYPE_SET_BLEND,

    /* Audio DV Mixer In-band Command */
    AUDIO_DV_MIXER_INBAND_CMD_TYPE_SET_BLEND

} AUDIO_INBAND_CMD_TYPE ;

#ifndef __LINUX_MEDIA_NAS__
typedef struct
{
    AUDIO_INBAND_CMD_TYPE   type ;
    long                    size ;
} AUDIO_INBAND_CMD_PKT_HEADER;

typedef struct
{
    AUDIO_INBAND_CMD_PKT_HEADER header;
    unsigned long               wPtr;
    int                         audioType;//AUDIO_DEC_TYPE              audioType;
    long                        privateInfo[8];  // note: privateinfo[6] is used for choosing decoder sync pts method
}   AUDIO_DEC_NEW_FORMAT ;
#endif

typedef struct
{
    INBAND_CMD_PKT_HEADER header ;
    int packet[DUMMY_PACKET_SIZE];//may need to modify later
} VIDEO_VO_INBAND_DUMMY;

#ifndef __LINUX_MEDIA_NAS__
typedef struct
{
    AUDIO_INBAND_CMD_PKT_HEADER header;
    unsigned long 				wPtr ;
    unsigned long				PTSH;
    unsigned long				PTSL;
} AUDIO_DEC_PTS_INFO ;
#endif
#endif
