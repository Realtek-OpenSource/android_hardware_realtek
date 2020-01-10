#ifndef __E_TYPE_H__
#define __E_TYPE_H__

#define GENERAL_NONE            (0x00000000)
#define GENERAL_SOURCE          (0x01000000)
#define GENERAL_DECODE          (0x02000000)
#define GENERAL_ENCODE          (0x04000000)
#define GENERAL_RENDER          (0x08000000)
#define GENERAL_POST            (0x10000000)

#define MEDIA_VIDEO             (0x00010000)
#define MEDIA_AUDIO             (0x00020000)
#define MEDIA_SPU               (0x00040000)
#define MEDIA_IMAGE             (0x00080000)

#include <OSAL_RTK.h>

typedef enum{
  PIN_STATUS_NONE,
  PIN_STATUS_IDLE,
  PIN_STATUS_RECEIVING,
  PIN_STATUS_FLUSHING
}PIN_STATUS;

typedef enum{
    FILTER_NONE_SPECIFY=        (GENERAL_NONE),

    FILTER_SOURCE=              (GENERAL_SOURCE),

    FILTER_DECODE_VIDEO=        (GENERAL_DECODE| MEDIA_VIDEO),
    FILTER_DECODE_AUDIO=        (GENERAL_DECODE| MEDIA_AUDIO),
    FILTER_DECODE_SPU=          (GENERAL_DECODE| MEDIA_SPU),

    FILTER_ENCODE_VIDEO=        (GENERAL_ENCODE| MEDIA_VIDEO),
    FILTER_ENCODE_AUDIO=        (GENERAL_ENCODE| MEDIA_AUDIO),
    FILTER_ENCODE_SPU=          (GENERAL_ENCODE| MEDIA_SPU),

    FILTER_RENDER_VIDEO=        (GENERAL_RENDER| MEDIA_VIDEO),
    FILTER_RENDER_AUDIO=        (GENERAL_RENDER| MEDIA_AUDIO),

    FILTER_POST_VIDEO=          (GENERAL_POST| MEDIA_VIDEO),
    FILTER_POST_AUDIO=          (GENERAL_POST| MEDIA_AUDIO),

} FILTER_TYPE;

typedef enum{
    FILTER_PROP_PLAYBACK_RATE,   // set playback rate information (long)
    FILTER_PROP_SETAUIDIO_PREFERENCE	// set audio preferences decoding type
} FILTER_PROPERTY;

typedef enum{
    PINDIR_INPUT,
    PINDIR_OUTPUT
} PIN_DIRECTION;

typedef enum{
    FORMAT_None,
    FORMAT_DvInfo,
    FORMAT_MPEG1Video,
    FORMAT_MPEG2Video,
    FORMAT_AudioInfo
} FORMAT_TYPE;

typedef enum{
    State_Stopped,
    State_Paused,
    State_Running,
    State_Paused_Stopped,
    State_Paused_Paused,
    State_Paused_Running,
    State_Transition
} FILTER_STATE;

typedef enum{
    TIME_FORMAT_NONE,                   // No format
    TIME_FORMAT_FRAME,                  // Video frames
    TIME_FORMAT_SAMPLE,                 // Samples in stream
    TIME_FORMAT_FIELD,                  // Interlaced video fields
    TIME_FORMAT_BYTE,                   // Byte offset within the stream
    TIME_FORMAT_MEDIA_TIME              // Media time, in 100-nanosecond units
} TIME_FORMAT;

typedef enum{
    STYLE_RING,
    STYLE_BUFFERLIST
} ALLOCATOR_STYLE;

typedef enum{
    WAIT_BUFFER_NO,
    WAIT_BUFFER_FOREVER
} ALLOCATOR_WAIT;

typedef enum{
    MEDIATYPE_None,                     // 0, not available

//  Major Type:                         Description
    MEDIATYPE_AnalogAudio,              // 1, Analog audio.
    MEDIATYPE_AnalogVideo,              // 2, Analog video.
    MEDIATYPE_Audio,                    // 3, Audio.
    MEDIATYPE_Video,                    // 4, Video.
    MEDIATYPE_AUXLine21Data,            // 5, Line 21 data. Used by closed captions.
    MEDIATYPE_DVD_ENCRYPTED_PACK,       // 6, Encrypted DVD data
    MEDIATYPE_MPEG2_PES,                // 7, MPEG-2 PES packets.
    MEDIATYPE_ScriptCommand,            // 8, Data is a script command, used by closed captions.
    MEDIATYPE_Stream,                   // 9, Byte stream with no time stamps.
    MEDIATYPE_Text,                     // 10, Text.
    MEDIATYPE_Image,					// 11, Image
    MEDIATYPE_Directory,				// 12, Direcotory
    MEDIATYPE_NEPTUNE_TP,				// 13

//  Audio Subtype:                      Description
    MEDIASUBTYPE_PCM,                   // 14, PCM audio.(big endian)
    MEDIASUBTYPE_PCM_LITTLE_ENDIAN,     // 15, PCM audio.(little endian)
    MEDIASUBTYPE_MPEG1Packet,           // 16, MPEG1 Audio packet.
    MEDIASUBTYPE_MPEG1ES,               // 17, MPEG1 Audio Payload (Elementary Stream).
    MEDIASUBTYPE_MPEG2_AUDIO,           // 18, MPEG-2 audio data
    MEDIASUBTYPE_DVD_LPCM_AUDIO,        // 19, DVD audio data
    MEDIASUBTYPE_MLP_AUDIO,				// 20, trueHD
    MEDIASUBTYPE_DOLBY_AC3,             // 21, Dolby data
    MEDIASUBTYPE_DOLBY_AC3_SPDIF,       // 22, Dolby AC3 over SPDIF.
    MEDIASUBTYPE_MPEG_AUDIO,            // 23, general MPEG audio
    MEDIASUBTYPE_DTS,                   // 24, DTS audio
    MEDIASUBTYPE_DTS_HD,				// 25, DTS-HD audio
    MEDIASUBTYPE_DTS_HD_EXT,			// 26, DTS-HD extension sub stream
    MEDIASUBTYPE_DTS_HD_CORE,			// 27, DTS_HD core sub stream
    MEDIASUBTYPE_DDP,					// 28, Dolby Digital Plus audio
    MEDIASUBTYPE_SDDS,                  // 29, SDDS audio
    MEDIASUBTYPE_DV,                  	// 30, DV audio
	MEDIASUBTYPE_AAC,					// 31, AAC(Advanced Audio Coding)
	MEDIASUBTYPE_RAW_AAC,				// 32, AAC without header
    MEDIASUBTYPE_OGG_AUDIO,             // 33, OGG vorbis
    MEDIASUBTYPE_WMA,                   // 34, WMA audio
    MEDIASUBTYPE_WMAPRO,                // 35, WMAPRO audio
    MEDIASUBTYPE_MP3,                   // 36, MP3 file
    MEDIASUBTYPE_MP4,                   // 37, MP4 aac file
    MEDIASUBTYPE_LATM_AAC,              // 38, LATM/LOAS AAC file
	MEDIASUBTYPE_WAVE,                  // 39, WAVE audio
    MEDIASUBTYPE_AIFF,                  // 40, AIFF audio
    MEDIASUBTYPE_RTP,                   // 41, RTP
    MEDIASUBTYPE_APE,                   // 42, APE, pure audio

    MEDIASUBTYPE_DVD_SUB_PICTURE,       	// 43, DVD-Video subpicture
	MEDIASUBTYPE_DIVX_SUB_PICTURE,			// 44, DivX Subtitles
	MEDIASUBTYPE_DVB_SUBTITLE_SUB_PICTURE,  // 45, DVB Subtitles
	MEDIASUBTYPE_DVB_TT_SUB_PICTURE,    	// 46, DVB Teletext
	MEDIASUBTYPE_ATSC_CC_SUB_PICTURE,   	// 47, ATSC close caption
	MEDIASUBTYPE_BLURAY_PGS_SUB_PICTURE,	// 48, Blu-ray PGS

// Video Subtype:						Description
	MEDIASUBTYPE_DIVX3_VIDEO,			// 49, DivX 3.11 Video
	MEDIASUBTYPE_DIVX_VIDEO,			// 50, DivX 4/5 Video
	MEDIASUBTYPE_MPEG4_VIDEO,			// 51, MPEG-4 Video
	MEDIASUBTYPE_MJPEG_VIDEO,			// 52, Motion JPEG
	MEDIASUBTYPE_DVSD_VIDEO,			// 53, DV(Standard Definition)Video
	MEDIASUBTYPE_H264_VIDEO,			// 54
	MEDIASUBTYPE_H263_VIDEO,			// 55
	MEDIASUBTYPE_VP6_VIDEO,				// 56
	MEDIASUBTYPE_VC1_VIDEO,				// 57
	MEDIASUBTYPE_VC1_ADVANCED_VIDEO,	// 58
	MEDIASUBTYPE_VC1_WINDOWSMEDIA_VIDEO,// 59
	MEDIASUBTYPE_AVS_VIDEO,				// 60

//  DVD type/Subtype:                        Description
    MEDIATYPE_DVD,						// 61
    MEDIATYPE_SVCD,						// 62
    MEDIATYPE_VCD,						// 63
    MEDIATYPE_CDDA,						// 64
    MEDIATYPE_FILE,						// 65
    MEDIATYPE_PLAYLIST,					// 66
    MEDIATYPE_NET,						// 67
    MEDIATYPE_MMS,						// 68
    MEDIATYPE_TRANSCODE,				// 69
    MEDIATYPE_DV,						// 70
    MEDIATYPE_DV_FILE,					// 71
    MEDIATYPE_STB,                      // 72
    MEDIATYPE_FILESET,					// 73
    MEDIATYPE_FILELINK,					// 74
    MEDIATYPE_RTSP,						// 75
    MEDIATYPE_RTP,                      // 76, hongjian_shen
    MEDIATYPE_PPS,						// 77,
    MEDIATYPE_BESTV,					// 78,
    MEDIATYPE_VOOLETV,					// 79,
    MEDIATYPE_THUNDER_REMOTE,			// 80,
    MEDIATYPE_THUNDER,					// 81,
    MEDIATYPE_CUSTOM_1,					// 82,
    MEDIATYPE_CUSTOM_2,					// 83
    MEDIATYPE_CUSTOM_3,					// 84

    MEDIASUBTYPE_MPEG2_VIDEO,           // 85, MPEG-2 video
    MEDIASUBTYPE_DVD_SUBPICTURE,        // 86, DVD Subpicture
    MEDIASUBTYPE_DVD_RTRW_PLUS,         // 87, DVD +RW
    MEDIASUBTYPE_DVD_RTRW_MINUS,        // 88, DVD -VR
	MEDIASUBTYPE_DVD_RTRW_MINUS_HD,		// 89, DVD -VR on HDD (as special case)
    MEDIASUBTYPE_DVD_VIDEO,             // 90, Recordble DVD -VIDEO
    MEDIASUBTYPE_DVD_VIDEO_ROM,         // 91, DVD ROM
    MEDIASUBTYPE_DVD_RTRW_STILL,        // 92, DVD -VR Still Picture
    MEDIASUBTYPE_DVD_MENU,              // 93, DVD Menu VOB
    MEDIASUBTYPE_SVCD,                  // 94, Recordable SVCD
    MEDIASUBTYPE_SVCD_ROM,              // 95, SVCD Read Only
    MEDIASUBTYPE_VCD,                   // 96, VCD Recordable
    MEDIASUBTYPE_VCD_ROM,               // 97, VCD Read Only
    MEDIASUBTYPE_CDDA,                  // 98, Recordable CDDA
    MEDIASUBTYPE_CDDA_ROM,              // 99, CDDA Read Only
    MEDIASUBTYPE_AVCHD,                 // 100, AVCHD
    MEDIASUBTYPE_AVCHD_ROM,             // 101, AVCHD Read Only
    MEDIASUBTYPE_HTTP,					// 102,
    MEDIASUBTYPE_MMS,					// 103,
    MEDIASUBTYPE_TRANSCODE,				// 104,
    MEDIASUBTYPE_MPEG_PROGRAM,			// 105,
    MEDIASUBTYPE_STB_1394,              // 106, Richard
    MEDIASUBTYPE_FILESET,				// 107,
    MEDIASUBTYPE_FILELINK,				// 108

//  Line 21 Subtype:                    Description
    MEDIASUBTYPE_Line21_BytePair,       // 109, Line 21 data as byte pairs
    MEDIASUBTYPE_Line21_GOPPacket,      // 110, Line 21 data in DVD GOP Packet
    MEDIASUBTYPE_Line21_VBIRawData,     // 111, Line 21 data in raw VBI format

//  MPEG-1 Subtypes:                    Description
    MEDIASUBTYPE_MPEG1Audio,            // 112, MPEG audio
    MEDIASUBTYPE_MPEG1System,           // 113, MPEG system
    MEDIASUBTYPE_MPEG1SystemStream,     // 114, Obsolete. Do not use.
    MEDIASUBTYPE_MPEG1Video,            // 115, MPEG video
    MEDIASUBTYPE_MPEG1VideoCD,          // 116, MPEG video CD
    MEDIASUBTYPE_MPEG1SuperVCD,         // 117, MPEG SVCD

//  MPEG-2 Subtypes:                    Description
    MEDIASUBTYPE_MPEG2_PROGRAM,         // 118, Program stream
    MEDIASUBTYPE_MPEG2_TRANSPORT,       // 119, Transport stream (TS), with 188-byte packets

//  Subpicture Subtypes:                Description
    MEDIASUBTYPE_AI44,                  // 120, For subpicture and text overlays
    MEDIASUBTYPE_IAK2,                  // 121, For subpicture and text overlays,
                                        // 	   2 bits indexed, constant alpha and single color key
    MEDIASUBTYPE_IAK4,                  // 122, For subpicture and text overlays,
                                        //     4 bits indexed, constant alpha and single color key
    MEDIASUBTYPE_IAK8,                  // 123, For subpicture and text overlays,
                                        //     8 bits indexed, constant alpha and single color key.
                                        //     16 programmable palete.
//  External Subtitles
    MEDIASUBTYPE_SRT,					// 124,
    MEDIASUBTYPE_SSA,					// 125,
    MEDIASUBTYPE_ASS,					// 126,
    MEDIASUBTYPE_TXT,					// 127

//  Analog Video Subtypes:              Description
    MEDIASUBTYPE_AnalogVideo_NTSC,      // 128, NTSC
    MEDIASUBTYPE_AnalogVideo_PAL,       // 129, PAL (will be extended)

//  Image Subtypes
    MEDIASUBTYPE_IMAGE_JPEG,            // 130, JPEG Images
    MEDIASUBTYPE_IMAGE_BITMAP,          // 131, BMP Images
    MEDIASUBTYPE_IMAGE_GIF,             // 132, GIF Images
    MEDIASUBTYPE_IMAGE_TIFF,            // 133, TIFF Images
    MEDIASUBTYPE_IMAGE_PNG,             // 134, PNG Images
    MEDIASUBTYPE_IMAGE_DNG,             // 135, DNG Images



    MEDIASUBTYPE_MPEG2_AUDIO_WITH_EXTENSION,	// 136
    MEDIASUBTYPE_MPEG2_AUDIO_WITHOUT_EXTENSION,	//137


	MEDIASUBTYPE_PPSRM,			// 138, PPS RM
	MEDIASUBTYPE_PPSWMA,        // 139, PPS WMA

	MEDIASUBTYPE_BESTVRM,		// 140, PPS RM
	MEDIASUBTYPE_BESTVWMA,      // 141, PPS WMA
	MEDIASUBTYPE_BESTVMP4,

	// Real Media
	MEDIASUBTYPE_RM,			// 142
	MEDIASUBTYPE_RV,			// 143, real video
	MEDIASUBTYPE_RA_COOK,		// 144, RealAudio 8 Low Bit Rate(cook)
	MEDIASUBTYPE_RA_ATRC,		// 145, RealAudio 8 Hight Bit Rate(atrc)
	MEDIASUBTYPE_RA_RAAC,		// 146, AAC(raac)
	MEDIASUBTYPE_RA_SIPR,		// 147, RealAudio Voice(sipr)
	MEDIASUBTYPE_RA_LSD,		// 148, RealAudio Lossless

    MEDIASUBTYPE_ADPCM,         // 149, ADPCM audio
    MEDIASUBTYPE_FLAC,			// 150
    MEDIASUBTYPE_ULAW,			// 151
    MEDIASUBTYPE_ALAW,			// 152

// AVI Container subtype (using DivX specification)
	MEDIASUBTYPE_DMF_0,			// 153, Traditional AVI 1.0
	MEDIASUBTYPE_DMF_1,			// 154, DivX Ultra
	MEDIASUBTYPE_DMF_2,			// 155, OpenDML 2.0

    MEDIASUBTYPE_MP4_VIDEO,     // 156, mp4 video file

//  File Container Type
    MEDIATYPE_Interleaved,      // 157, Interleaved audio and video, aka AVI (Type1 DV AVI will use MEDIATYPE_DV)
    MEDIATYPE_FLASHVIDEO,       // 158, Macromedia Flash Video
    MEDIATYPE_MATROSKA,         // 159, Matroska Container (MKV)
    MEDIASUBTYPE_MATROSKA_DIVX_ENHANCED,	// 160,
    MEDIATYPE_ASF,              // 161, ASF/WMV/WMA file

// HDMV lpcm audio type
	MEDIASUBTYPE_PCM_HDMV, 		// 162

	//used for blue-ray
	MEDIASUBTYPE_HDMV_MLP_AUDIO,	// 163, trueHD audio
	MEDIASUBTYPE_HDMV_DOLBY_AC3,	// 164
	MEDIASUBTYPE_HDMV_DDP,			// 165
	MEDIASUBTYPE_HDMV_DTS,			// 166
	MEDIASUBTYPE_HDMV_DTS_HD,		// 167

	MEDIATYPE_FLASH,				// 168

	MEDIATYPE_PHOTO_ALBUM,			// 169

	MEDIATYPE_NRD, 					// 170
	MEDIASUBTYPE_NRD_2XX,			// 171

	MEDIASUBTYPE_BD,				// 172
	MEDIASUBTYPE_BD_ROM,			// 173

	MEDIASUBTYPE_VP8_VIDEO,			// 174

    MEDIATYPE_DIRECT_CONNECT,		// 175

    MEDIATYPE_HLS, 					// 176, HTTP Live Streaming

    MEDIATYPE_CONFERENCE,			// 177,

    MEDIASUBTYPE_AMRWB_AUDIO,		// 178
    MEDIASUBTYPE_AMRNB_AUDIO,		// 179

    //Used for Skype
    MEDIASUBTYPE_SILK_AUDIO,		// 180
    MEDIASUBTYPE_G729_AUDIO,		// 181

    MEDIASUBTYPE_MVC_DEPENDENT_VIDEO, //182

    //used for camera display
    MEDIATYPE_CAMERA,				// 183
    MEDIASUBTYPE_YUV_VIDEO,			// 184

    MEDIASUBTYPE_APE_AUDIO,			// 185

    MEDIASUBTYPE_WMV7_VIDEO,		// 186
    MEDIASUBTYPE_WMV8_VIDEO,		// 187

    MEDIATYPE_SOCKET,			// 188
    MEDIATYPE_SNDA,             // 189

    MEDIASUBTYPE_IMAGE_JPS,     //190 3d photo
    MEDIASUBTYPE_IMAGE_MPO,     //191 3d photo

    MEDIASUBTYPE_NRD_3XX,		//192
    MEDIATYPE_OMADRMFILE,		//193 omadrm file
    MEDIASUBTYPE_OMADRMMP4,		//194 omadrm mp4
    MEDIASUBTYPE_OMADRMASF,		//195 omadrm asf
    MEDIATYPE_SERVERIO,                //196, client deliver us content via net

    MEDIASUBTYPE_RA_RA1,		//197
	MEDIASUBTYPE_FJPEG_VIDEO,       //198

	MEDIASUBTYPE_ALAC,			// 199 for m4a

	MEDIATYPE_PPTV,				// 200 for PPTV

	MEDIATYPE_UDP,              // 201. UDP
	MEDIASUBTYPE_AC4,           // 202. AC4
	MEDIASUBTYPE_DSD,			// 203  DSD
        MEDIASUBTYPE_OGG_OPUS,      // 204 OGG opus
        MEDIASUBTYPE_MPEGH_AUDIO,   // 205 MPEGH
} ENUM_MEDIA_TYPE;

//  Horizontal resolution for the video stream
typedef enum {                          //Description
    VIDEO_SIF,                          //352*240(NTSC) or 352*288(PAL)
    VIDEO_HALF_D1,                      //352*480(NTSC) or 352*576(PAL)
    VIDEO_H480,                         //480*480(NTSC) or 480*576(PAL)
    VIDEO_H544,                         //544*480(NTSC) or 544*576(PAL)
    VIDEO_H704,                         //704*480(NTSC) or 704*576(PAL)
    VIDEO_D1,                           //720*480(NTSC) or 720*576(PAL)
    VIDEO_TotalHResolution
}ENUM_VIDEO_HORIZONTAL_RESOLUTION;

//  The picture Type of the encoded video frame
typedef enum {                          //Description
    VIDEO_I_PIC = 1,                    // I frame
    VIDEO_P_PIC,                        // P frame
    VIDEO_B_PIC                         // B Frame
}ENUM_VIDEO_FRAME_TYPE;

typedef struct{ // unfortunately only ETypes.h can be included by C source, so I have to put this "struct" here ...
    int64_t 					RCD;
    int64_t                     referenceClock;
    int64_t                     videoSystemPTS;
    int64_t                     audioSystemPTS;
    int64_t                     videoRPTS;
    int64_t                     audioRPTS;
    unsigned long               videoContext;
    unsigned long               audioContext;
    long                        videoEndOfSegment;
} PRESENTATION_POSITIONS;

#endif
