#ifndef OMX_AudioRTKExt_h
#define OMX_AudioRTKExt_h

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Each OMX header shall include all required header files to allow the
 * header to compile without errors.  The includes below are required
 * for this header file to compile successfully
 */
#include <OMX_Core.h>

typedef enum OMX_AUDIO_CODINGEXTTYPE_RTKEXT {
    //OMX_AUDIO_CodingVendorStartUnused = 0x7F000000, /**< Reserved region for introducing Vendor Extensions */
    OMX_AUDIO_CodingVendorRTKStartUnused = OMX_AUDIO_CodingVendorStartUnused, /**< Reserved region for introducing Vendor Extensions */
    OMX_AUDIO_CodingDTS,         /**< Any variant of DTS encoded data */
    OMX_AUDIO_CodingWMAPRO,      /**< Any variant of WMAPRO encoded data */
    OMX_AUDIO_CodingDV,          /**< Any variant of DV encoded data */
    OMX_AUDIO_CodingMLP,         /**< Any variant of MLP encoded data */
    OMX_AUDIO_CodingSILK,        /**< Any variant of SILK encoded data */
    OMX_AUDIO_CodingAPE,         /**< Any variant of APE encoded data */
    OMX_AUDIO_CodingALAC,        /**< Any variant of ALAC encoded data */
    OMX_AUDIO_CodingDSD,         /**< Any variant of DSD encoded data */
    OMX_AUDIO_CodingDTSHD,       /**< Any variant of DTSHD encoded data */
    OMX_AUDIO_CodingMPEGH,       /**< Any variant of MPEGH encoded data */
} OMX_AUDIO_CODINGEXTTYPE_RTKEXT;

/** WMAPRO params */
typedef struct OMX_AUDIO_PARAM_WMAPROTYPE {
    OMX_U32 nSize;            /**< size of the structure in bytes */
    OMX_VERSIONTYPE nVersion; /**< OMX specification version information */
    OMX_U32 nPortIndex;       /**< port that this structure applies to */
    OMX_U16 nChannels;        /**< Number of channels */
    OMX_U32 nBitRate;         /**< Bit rate of the input data.  Use 0 for variable
                                   rate or unknown bit rates */
    OMX_U32 nSamplingRate;    /**< Sampling rate of the source data */
} OMX_AUDIO_PARAM_WMAPROTYPE;

/** DV params */
typedef struct OMX_AUDIO_PARAM_DVTYPE {
    OMX_U32 nSize;            /**< size of the structure in bytes */
    OMX_VERSIONTYPE nVersion; /**< OMX specification version information */
    OMX_U32 nPortIndex;       /**< port that this structure applies to */
    OMX_U16 nChannels;        /**< Number of channels */
    OMX_U32 nBitRate;         /**< Bit rate of the input data.  Use 0 for variable
                                   rate or unknown bit rates */
    OMX_U32 nSamplingRate;    /**< Sampling rate of the source data */
} OMX_AUDIO_PARAM_DVTYPE;

/** MLP params */
typedef struct OMX_AUDIO_PARAM_MLPTYPE {
    OMX_U32 nSize;            /**< size of the structure in bytes */
    OMX_VERSIONTYPE nVersion; /**< OMX specification version information */
    OMX_U32 nPortIndex;       /**< port that this structure applies to */
    OMX_U16 nChannels;        /**< Number of channels */
    OMX_U32 nBitRate;         /**< Bit rate of the input data.  Use 0 for variable
                                   rate or unknown bit rates */
    OMX_U32 nSamplingRate;    /**< Sampling rate of the source data */
} OMX_AUDIO_PARAM_MLPTYPE;

/** MPEGH params */
typedef struct OMX_AUDIO_PARAM_MPEGHTYPE {
    OMX_U32 nSize;            /**< size of the structure in bytes */
    OMX_VERSIONTYPE nVersion; /**< OMX specification version information */
    OMX_U32 nPortIndex;       /**< port that this structure applies to */
    OMX_U16 nChannels;        /**< Number of channels */
    OMX_U32 nBitRate;         /**< Bit rate of the input data.  Use 0 for variable
                                   rate or unknown bit rates */
    OMX_U32 nSamplingRate;    /**< Sampling rate of the source data */
} OMX_AUDIO_PARAM_MPEGHTYPE;

/** SILK params */
typedef struct OMX_AUDIO_PARAM_SILKTYPE {
    OMX_U32 nSize;            /**< size of the structure in bytes */
    OMX_VERSIONTYPE nVersion; /**< OMX specification version information */
    OMX_U32 nPortIndex;       /**< port that this structure applies to */
    OMX_U16 nChannels;        /**< Number of channels */
    OMX_U32 nBitRate;         /**< Bit rate of the input data.  Use 0 for variable
                                   rate or unknown bit rates */
    OMX_U32 nSamplingRate;    /**< Sampling rate of the source data */
} OMX_AUDIO_PARAM_SILKTYPE;

/** APE params */
typedef struct OMX_AUDIO_PARAM_APETYPE {
    OMX_U32 nSize;            /**< size of the structure in bytes */
    OMX_VERSIONTYPE nVersion; /**< OMX specification version information */
    OMX_U32 nPortIndex;       /**< port that this structure applies to */
    OMX_U16 nChannels;        /**< Number of channels */
    OMX_U32 nBitRate;         /**< Bit rate of the input data.  Use 0 for variable
                                   rate or unknown bit rates */
    OMX_U32 nSamplingRate;    /**< Sampling rate of the source data */
} OMX_AUDIO_PARAM_APETYPE;

/** ALAC params */
typedef struct OMX_AUDIO_PARAM_ALACTYPE_COOKIE {
	OMX_U32				frameLength;
	OMX_U8			    compatibleVersion;
	OMX_U8				bitDepth;							// max 32
	OMX_U8				pb;									// 0 <= pb <= 255
	OMX_U8				mb;
	OMX_U8				kb;
	OMX_U8				numChannels;
	OMX_U16				maxRun;
	OMX_U32				maxFrameBytes;
	OMX_U32				avgBitRate;
	OMX_U32				sampleRate;
} OMX_AUDIO_PARAM_ALACTYPE_COOKIE;

typedef struct OMX_AUDIO_PARAM_ALACTYPE {
    OMX_U32 nSize;            /**< size of the structure in bytes */
    OMX_VERSIONTYPE nVersion; /**< OMX specification version information */
    OMX_U32 nPortIndex;       /**< port that this structure applies to */
    OMX_U16 nChannels;        /**< Number of channels */
    OMX_U32 nBitRate;         /**< Bit rate of the input data.  Use 0 for variable
                                   rate or unknown bit rates */
    OMX_U32 nSamplingRate;    /**< Sampling rate of the source data */
    OMX_AUDIO_PARAM_ALACTYPE_COOKIE nConfig;
} OMX_AUDIO_PARAM_ALACTYPE;

/** DSD stream format parameters */
typedef struct OMX_AUDIO_PARAM_DSDTYPE {
    OMX_U32 nSize;              /**< size of the structure in bytes */
    OMX_VERSIONTYPE nVersion;   /**< OMX specification version information */
    OMX_U32 nPortIndex;         /**< port that this structure applies to */
    OMX_U32 nChannels;          /**< Number of channels in the data stream (not
                                     necessarily the same as the number of channels
                                     to be rendered. */
    OMX_U32 nBitsPerSample;     /**< Number of bits in each sample */
    OMX_U32 nSampleRate;        /**< Sampling rate of the source data.  Use 0 for
                                    variable or unknown sampling rate. */
    /* Add by chihualee */
    OMX_U32 nBlock;
    OMX_U32 nChType;
    OMX_U64 nSampleCount;
} OMX_AUDIO_PARAM_DSDTYPE;

/** DTS params */
typedef struct OMX_AUDIO_PARAM_DTSTYPE {
    OMX_U32 nSize;                /**< size of the structure in bytes */
    OMX_VERSIONTYPE nVersion;     /**< OMX specification version information */
    OMX_U32 nPortIndex;           /**< port that this structure applies to */
    OMX_U32 nChannels;            /**< Number of channels in the data stream (not
                                       necessarily the same as the number of channels
                                       to be rendered. */
    OMX_U32 nBitRate;
    OMX_U32 nSamplingRate;
    //OMX_U32 nDtsType;            /** DTS type 1, 2, or 3. */
    //OMX_U32 nFormat;               /** DTS stream is either big/little endian and 16/14 bit packing */
    //OMX_U32 nDtsFrameSizeBytes;    /** DTS frame size in bytes */
    //OMX_AUDIO_CHANNELTYPE eChannelMapping[OMX_AUDIO_MAXCHANNELS]; /**< Slot i contains channel defined by eChannelMapping[i] */
} OMX_AUDIO_PARAM_DTSTYPE;

/** DTSHD params */
typedef struct OMX_AUDIO_PARAM_DTSHDTYPE {
    OMX_U32 nSize;                /**< size of the structure in bytes */
    OMX_VERSIONTYPE nVersion;     /**< OMX specification version information */
    OMX_U32 nPortIndex;           /**< port that this structure applies to */
    OMX_U32 nChannels;            /**< Number of channels in the data stream (not
                                       necessarily the same as the number of channels
                                       to be rendered. */
    OMX_U32 nBitRate;
    OMX_U32 nSamplingRate;
} OMX_AUDIO_PARAM_DTSHDTYPE;

#if 1 //rtk
/* =====================MS12 related START here==================== */

#define MS12_7_1_SUPPORT
#define MS12_AC4_SUPPORT

#define OMX_AUDIO_MS_PROGRAM_UUID_LEN_BYTES  16

#define OMX_AUDIO_MS_MAIN_DECODER_IDX         0
#define OMX_AUDIO_MS_ASSOC_DECODER_IDX        1
#define OMX_AUDIO_MS_SYSTEM_SOUNDS_IDX        2
#define OMX_AUDIO_MS_APPLICATION_SOUNDS_IDX   3
#define OMX_AUDIO_MS_MAX_NUM_INPUTS           4

#define OMX_AUDIO_MS_DOWNMIX_OUT_IDX          0
#define OMX_AUDIO_MS_VIRTUALIZER_OUT_IDX      1
#define OMX_AUDIO_MS_DAP_SPEAKER_OUT_IDX      2
#define OMX_AUDIO_MS_DAP_HEADPHONE_OUT_IDX    3

#define OMX_AUDIO_MS_DD_OUT_IDX               4
#define OMX_AUDIO_MS_DDP_OUT_IDX              5

#define OMX_AUDIO_MS_PCMR_OUT_IDX             6

#define OMX_AUDIO_MS_MAX_NUM_PCM_OUTPUTS      4
#define OMX_AUDIO_MS_MAX_NUM_BS_OUTPUTS       2

#define OMX_AUDIO_MS_MAX_NUM_OUTPUTS          7
#define OMX_AUDIO_MS_MAX_OUTPUT_NAME_LEN      256

#define OMX_AUDIO_MS_MAX_NUM_INPUTS           4
#define OMX_AUDIO_MS_MAX_NUM_PCM_OUTPUTS      4
#define OMX_AUDIO_MS_MAX_NUM_BS_OUTPUTS       2
#ifdef MS12_7_1_SUPPORT
#define OMX_AUDIO_MS_MIN_MAX_CHANNEL      6                 /**< Minimum value for max. number of channels        */
#define OMX_AUDIO_MS_MAX_MAX_CHANNEL      8                 /**< Maximum value for max. number of channels        */
#else
#define OMX_AUDIO_MS_MIN_MAX_CHANNEL      6                 /**< Minimum value for max. number of channels        */
#define OMX_AUDIO_MS_MAX_MAX_CHANNEL      6                 /**< Maximum value for max. number of channels        */
#endif

#define OMX_AUDIO_DAP_MAX_BANDS          (20)
#define OMX_AUDIO_DAP_IEQ_MAX_BANDS      OMX_AUDIO_DAP_MAX_BANDS
#define OMX_AUDIO_DAP_GEQ_MAX_BANDS      OMX_AUDIO_DAP_MAX_BANDS
#define OMX_AUDIO_DAP_REG_MAX_BANDS      OMX_AUDIO_DAP_MAX_BANDS
#define OMX_AUDIO_DAP_OPT_MAX_BANDS      OMX_AUDIO_DAP_MAX_BANDS
#define OMX_AUDIO_DAP_MAX_CHANNELS       (OMX_AUDIO_MS_MAX_MAX_CHANNEL)

#ifdef MS12_AC4_SUPPORT
#define OMX_AUDIO_MS_AC4_NUM_LANG_CHAR    3                 /**< Number of characters used for language selection. */
#define OMX_AUDIO_MS_AC4_LANG_MAX_STRLEN  (OMX_AUDIO_MS_AC4_NUM_LANG_CHAR+1)
#define OMX_AUDIO_AC4_MODE_SINGLE_STREAM_SINGLE_DECODE               0
#define OMX_AUDIO_AC4_MODE_SINGLE_STREAM_DUAL_DECODE_SINGLE_INSTANCE 1
#define OMX_AUDIO_AC4_MODE_SINGLE_STREAM_DUAL_DECODE_DUAL_INSTANCE   2
#define OMX_AUDIO_AC4_MODE_DUAL_STREAM_DUAL_DECODE                   3
#endif


#define OMX_AUDIO_MAX_MS12_UPDATE_PARAM_MEM_SIZE    820  // 820/sizeof(int)
#define OMX_AUDIO_MS12_MAX_NUM_PARAM_UPDATE         32
/**
 * @brief See dap_cpdp.h in the DAPv2 CIDK for a detailed description of the parameter.
 */
typedef struct OMX_AUDIO_dap_params_s
{
    OMX_S32 drc_type;
    OMX_S32 dmx_type;
    OMX_S32 speaker_lfe;
    OMX_S32 pregain;
    OMX_S32 postgain;
    OMX_S32 systemgain;
    OMX_S32 surround_decoder_enable;
    OMX_S32 virtualizer_enable;
    OMX_S32 headphone_reverb;
    OMX_S32 speaker_angle;
    OMX_S32 speaker_start;
    OMX_S32 surround_boost;
    OMX_S32 mi_ieq_enable;
    OMX_S32 mi_dv_enable;
    OMX_S32 mi_de_enable;
    OMX_S32 mi_surround_enable;

    OMX_S32 calibration_boost;

    OMX_S32 leveler_amount;
    OMX_S32 leveler_input;
    OMX_S32 leveler_output;
    OMX_S32 leveler_enable;
    OMX_S32 leveler_ignore_il;

    OMX_S32 modeler_enable;
    OMX_S32 modeler_calibration;

    OMX_S32 ieq_enable;
    OMX_S32 ieq_amount;
    OMX_S32 ieq_nb_bands;
    OMX_S32 a_ieq_band_center[OMX_AUDIO_DAP_IEQ_MAX_BANDS];
    OMX_S32 a_ieq_band_target[OMX_AUDIO_DAP_IEQ_MAX_BANDS];

    OMX_S32 de_enable;
    OMX_S32 de_amount;
    OMX_S32 de_ducking;

    OMX_S32 volmax_boost;

    OMX_S32 eq_enable;
    OMX_S32 eq_nb_bands;
    OMX_S32 a_geq_band_center[OMX_AUDIO_DAP_GEQ_MAX_BANDS];
    OMX_S32 a_geq_band_target[OMX_AUDIO_DAP_GEQ_MAX_BANDS];

    OMX_S32 optimizer_enable;
    OMX_S32 optimizer_nb_bands;
    OMX_S32 a_opt_band_center_freq[OMX_AUDIO_DAP_OPT_MAX_BANDS];
    OMX_S32 a_opt_band_gain[OMX_AUDIO_DAP_MAX_CHANNELS][OMX_AUDIO_DAP_OPT_MAX_BANDS];

    OMX_S32 bass_enable;
    OMX_S32 bass_boost;
    OMX_S32 bass_cutoff;
    OMX_S32 bass_width;

    OMX_S32 reg_nb_bands;
    OMX_S32 a_reg_band_center[OMX_AUDIO_DAP_REG_MAX_BANDS];
    OMX_S32 a_reg_low_thresholds[OMX_AUDIO_DAP_REG_MAX_BANDS];
    OMX_S32 a_reg_high_thresholds[OMX_AUDIO_DAP_REG_MAX_BANDS];
    OMX_S32 a_reg_isolated_bands[OMX_AUDIO_DAP_REG_MAX_BANDS];

    OMX_S32 regulator_overdrive;
    OMX_S32 regulator_timbre;
    OMX_S32 regulator_distortion;
    OMX_S32 regulator_mode;
    OMX_S32 regulator_enable;

    OMX_S32 vb_mode;
    OMX_S32 vb_low_src_freq;
    OMX_S32 vb_high_src_freq;
    OMX_S32 vb_overall_gain;
    OMX_S32 vb_slope_gain;
    OMX_S32 vb_subgain[3];
    OMX_S32 vb_mix_low_freq;
    OMX_S32 vb_mix_high_freq;
} OMX_AUDIO_dap_params_t;

typedef enum OMX_AUDIO_ms_bs_output_mode_t
{
    OMX_AUDIO_MS_BS_OUTPUT_MODE_NONE,
    OMX_AUDIO_MS_BS_OUTPUT_MODE_DD,
    OMX_AUDIO_MS_BS_OUTPUT_MODE_DDP,
    OMX_AUDIO_MS_BS_OUTPUT_MODE_SIM_DDP_DD
} OMX_AUDIO_ms_bs_output_mode_t;

typedef enum OMX_AUDIO_ms_dap_mode_t
{
    OMX_AUDIO_MS_DAP_NO_PROC = 0,
    OMX_AUDIO_MS_DAP_CONTENT_PROC = 1,
    OMX_AUDIO_MS_DAP_DEVICE_PROC = 2,
    OMX_AUDIO_MS_DAP_DEVICE_CONTENT_PROC = OMX_AUDIO_MS_DAP_DEVICE_PROC | OMX_AUDIO_MS_DAP_CONTENT_PROC,
    OMX_AUDIO_MS_DAP_SI_PROC = 4,
} OMX_AUDIO_ms_dap_mode_t;

/*! Enumeration of possible input types beeing processed by the multistream decoder */
typedef enum OMX_AUDIO_MS_INPUT_TYPE
{
    OMX_AUDIO_DOLBY_DIGITAL_PLUS,
    OMX_AUDIO_HE_AAC,
#ifdef MS12_AC4_SUPPORT
    OMX_AUDIO_AC4,
#endif
    OMX_AUDIO_EXTERNAL_PCM
} OMX_AUDIO_MS_INPUT_TYPE;


/*! Struct defining the current use case, not all permutations are allowed */
typedef struct OMX_AUDIO_MS_USE_CASE_S
{
    OMX_AUDIO_MS_INPUT_TYPE          input_type; /*!< Either HE-AAC, Dolby Digital Plus or external PCM */
    OMX_S32                          b_low_complexity; /*!< Flag indicating if the Processing Graph is initialized in low complexity mode */
    OMX_S32                          b_dual_input; /*!< Flag indicating if two input streams are present (n/a for external PCM) */
    OMX_S32                          b_dual_main; /*!< Flag indicating if two main input streams are present (DDP only).
                                                    b_dual_main is a special case of b_dual_input. */
    OMX_S32                          b_file_playback; /*!< Flag indicating file playback (HE-AAC with single input only) */
    OMX_S32                          b_restricted_ad; /*!< Flag indicating that the associated instance is restricted to 2 channels (HE-AAC only) */
    OMX_S32                          b_mainonly; /*!< Flag indicating that the UDC shall handle only the main program */
    OMX_S32                          b_system_sounds; /*!< Flag indicating that system sounds are present */
    OMX_S32                          b_app_sounds; /*!< Flag indicating that application sounds are present */
    OMX_S32                          b_eval_mode; /*!< Flag indicating that evaluation mode is enabled */
    OMX_AUDIO_ms_bs_output_mode_t    bs_output_mode; /*!< Either DD, DD+ or both */
    OMX_AUDIO_ms_dap_mode_t          dap_init_mode; /*!< DAP configuration:
                                                  - 0: no DAP
                                                  - 1: content processing only
                                                  - 2: device processing only
                                                  - 3: both with two DAP instances
                                                  - 4: both with single instance DAP processing */
    OMX_S32                          b_dap_vb_enable; /*!< DAP virtual bass configuration */
#ifdef MS12_AC4_SUPPORT
    OMX_S32                          ac4_mode; /**< AC4 decoding mode:
                                                  - 0: single stream, single decode
                                                  - 1: single stream, dual decode, single instance (mixing inside decoder)
                                                  - 2: single stream, dual decode, dual instance (mixing outside decoder)
                                                  - 3: dual stream, dual decode, dual instance (mixing outside decoder) */
#endif

} OMX_AUDIO_MS_USE_CASE;

typedef struct OMX_AUDIO_CHANNEL_CONFIG_S
{
  OMX_U16 acmod;         /*!< Audio coding mode as defined for Dolby Digital.
                               The audio coding mode can be ONEPLUSONE=0, MONO=1, STEREO=2, or 3_2=7. */
  OMX_U16 b_lfe_present; /*!< Flag indicating presence of the low frequency enhancement channel. */
  OMX_U16 dsurmod;       /*!< Indicates if the signal is dolby surround encoded (only possible for stereo signals) */
} OMX_AUDIO_CHANNEL_CONFIG;

typedef struct OMX_AUDIO_mix_fade_s
{
    int target_attenuation;  /**< Target attenuation at end of ramp in dB (range: -96...0). */
    int duration_in_ms;      /**< Duration of ramp in milliseconds (range: 0...60000). */
    int type;                /**< Shape of the ramp (0: linear, 1: in cube, 2: out cube). */
} OMX_AUDIO_mix_fade_t;

/** This struct holds all parameters that may change during runtime without re-initialization */
typedef struct OMX_AUDIO_MS_RUNTIME_PARAMS_S
{

  /* Parameters common to DD+, external PCM and HE-AAC */
  OMX_S16 drc_cut_fac_mc;           /**< Determines the percentage of application of DRC
                                         attenuation factors for the multichannel channel output.    */
  OMX_S16 drc_boost_fac_mc;         /**< Determines the percentage of application of DRC
                                         boost factors for the multichannel channel output.          */
  OMX_S16 drc_cut_fac_2ch;          /**< Determines the percentage of application of DRC
                                         attenuation factors for the 2 channel output.               */
  OMX_S16 drc_boost_fac_2ch;        /**< Determines the percentage of application of DRC
                                         boost factors for the 2 channel output.                     */
  OMX_S16 downmix_type;             /**< Indicates which downmix type is used (LtRt,LoRo,ARIB)       */
  OMX_S16 drc_mode;                 /**< Indicates whether to operate in RF or Line mode             */
  OMX_S16 dual_mono;                /**< Dual Mono reproduction mode, (both, left, right)            */
  OMX_S16 cmix_lev;                 /**< Index in center mix level table (-3dB,-4.5dB,-6dB)          */
  OMX_S16 smix_lev;                 /**< Index in surround mix level table (-3dB,-4.5dB,-6dB)        */
  OMX_S16 multichannel_enable;      /**< Indicates if the signal in the multichannel output is valid */
  OMX_S16 associated_audio_mixing;  /**< Enables/Disables mixing in dual decoding use cases          */
  OMX_S16 user_balance_adjustment;  /**< User defined balance between main and associated signal.
                                         Value range is between -32 and +32 (in dB),
                                         -32dB indicates main only (mute associated)
                                         +32dB indicates associated only (mute main)                 */
  OMX_S16 mixer_balance_adjustment; /**< User defined balance between primary and application audio
                                         signal.
                                         Value range is between -32 and +32 (in dB),
                                         -32dB indicates primary audio only (mute application audio)
                                         +32dB indicates application audio only (mute primary audio) */
  OMX_S16 b_sys_app_sound_mixing;   /**< Enables/Disables mixing of systen and application sounds    */

  OMX_AUDIO_mix_fade_t input_mix_input1;      /**< Input mixer input1 gain/fade event.                         */
  OMX_AUDIO_mix_fade_t input_mix_input2;      /**< Input mixer input2 gain/fade event.                         */
  OMX_AUDIO_mix_fade_t syssound_mix_input1;   /**< System/application sound mixer input1 gain/fade event.      */
  OMX_AUDIO_mix_fade_t syssound_mix_input2;   /**< System/application sound mixer input2 gain/fade event.      */
  OMX_AUDIO_mix_fade_t syssound_mix_input3;   /**< System/application sound mixer input3 gain/fade event.      */

  /* External PCM parameters */
  OMX_S32                       extpcm_num_in_samples;          /**< Number of input samples to process  */
  OMX_AUDIO_CHANNEL_CONFIG      extpcm_in_channel_config;       /**< Input channel configuration         */

  /* System Sounds PCM parameters */
  OMX_S32                       sys_sounds_num_in_samples;      /**< Number of input samples to process  */
  OMX_AUDIO_CHANNEL_CONFIG      sys_sounds_channel_config;      /**< Input channel configuration         */

  /* Application Sounds PCM parameters */
  OMX_S32                       app_sounds_num_in_samples;      /**< Number of input samples to process  */
  OMX_AUDIO_CHANNEL_CONFIG      app_sounds_channel_config;      /**< Input channel configuration         */

  /* HE-AAC parameters */
  OMX_S16 heaac_mixing_mode;          /**< Blocking or non-blocking mixing, i.e. does main wait for associated */
  OMX_S16 heaac_default_dialnorm;     /**< Default dialnorm (dB/4) that is used until a valid dialnorm is found in the bitstream */
  OMX_S16 heaac_transport_format;     /**< Specifies the HE-AAC transport format
                                           (can increase robustness compared to auto-detect)   */

  /* DDPlus parameters */
  OMX_S16 ddplus_associated_substream; /**< ID of the substream which should be mixed with the main program */
  OMX_S16 ddplus_outlfe;               /**< Determines if LFE will be present in the DD+ decoded signal  */
  OMX_S16 ddplus_outmode;              /**< Determines which acmod will be set in the DD+ decoded signal */

  OMX_AUDIO_dap_params_t  dap_parameter;         /**< Contains all configurable DAP parameter */
  OMX_S32                 b_mc_5_1_dmx;          /**< Determines if 7.1 signals shall be dowmixed to 5.1 for the multichannel PCM output */

#ifdef MS12_AC4_SUPPORT
  /* AC4 parameters */
  OMX_S8          ac4_1st_pref_lang[OMX_AUDIO_MS_AC4_LANG_MAX_STRLEN]; /**< String containing the preferred language selection */
  OMX_S8          ac4_2nd_pref_lang[OMX_AUDIO_MS_AC4_LANG_MAX_STRLEN]; /**< String containing the preferred language selection */
  OMX_S32         ac4_associated_type;                       /**< Indication of the preferred associated content type */
  OMX_S32         b_ac4_pref_assoc_type_over_lang;           /**< Preferred filter priority (selection of associated content type over language or vice versa) */
  OMX_S32         ac4_de_gain;                               /**< Indicates gain that will be applied to dialog enhancement. Range: 0 to 12 dB (in 1 dB steps) */
  OMX_S32         ac4_pres_index[2];                         /**< Primary and secondary Presentation index to be decoded. Overrides presentation selection by language and assoc. type. */
  OMX_S32         ac4_prog_id_type;                                           /**< Determines whether the program_identifier is present or not and whether it's the short or the long version. */
  OMX_S8          ac4_program_identifier_string[2*OMX_AUDIO_MS_PROGRAM_UUID_LEN_BYTES]; /**< Either the short program identifier (16 bit) or the UUID (128 bit) as a string copied from the command line */
#endif

  /* parameter update status variables */
  OMX_S32    frame;                    /**< Current Frame number (necessary to apply runtime changes) */
  //DLB_TIMESTAMP  next_update;          /**< Indicates the next frame when parameters shall be updated */
} OMX_AUDIO_MS_RUNTIME_PARAMS;

/** This struct holds all parameters that are set at initialization time */
typedef struct OMX_AUDIO_MS_INIT_PARAMS_S
{
  /* Input and output filenames */
  const char *input_filename[OMX_AUDIO_MS_MAX_NUM_INPUTS];               /**< Names of the input file(s) - main, associated, sys sounds, app sounds */
  const char *pcm_output_filename[OMX_AUDIO_MS_MAX_NUM_PCM_OUTPUTS];     /**< Names of the PCM output files - downmix, multichannel, dap speaker and headphone  */
  const char *bitstream_output_filename[OMX_AUDIO_MS_MAX_NUM_BS_OUTPUTS];/**< Name of the DD and DD+ bitstream output file. */
  const char *pcmr_output_filename;                            /**< Name of the PCMR output text file. */
  OMX_S32         pcm_out_chans[OMX_AUDIO_MS_MAX_NUM_PCM_OUTPUTS];           /**< Number of channels of the PCM output files */

  OMX_S16     verbose_mode;                 /**< Determines the amout of information that is written to the command line */
  OMX_S32     wav_bit_depth;                /**< Output WAV file bit-depth */
  OMX_S32     max_num_channels;             /**< Determines the maximum number of channels in the signal processing chain */
  OMX_S32     enc_chmod_locking_mode;       /**< Determines whether the encoded channel mode is driven by the input or locked. */
  OMX_S32     b_high_risc_precision;        /**< Determines whether LFRACT or SFRACT data type is used for PCM representation */

  /* PCM parameters */
  OMX_S16     extpcm_compressor_profile;    /**< The compressor profile for external PCM reencoding */

  /* HE-AAC parameters */
  OMX_U16     heaac_allow_partial_feed;        /**< Flag enabling feeding of less input data than necessary to complete an output frame */

  /* DAP parameters */
  OMX_U16     dap_output_mode;                 /**< 2-Bit Bitmask to indicate which of both supported DAP outputs is active */

  OMX_S32     dbg_output_mask;              /**< Used to activate different debug outputs */
} OMX_AUDIO_MS_INIT_PARAMS;


/** This struct contains all multistream decoder parameters separated into init time and runtime settable parameters */
typedef struct OMX_AUDIO_ms12_param_struct_t
{
    //OMX_AUDIO_MS_PARAMS           user_params;
    OMX_AUDIO_MS_RUNTIME_PARAMS   ms_runtime_args; /**< Structure containing all runtime dependant arguments */
    OMX_AUDIO_MS_INIT_PARAMS      ms_init_args;    /**< Structure containing all initialization dependant arguments */
    OMX_AUDIO_MS_USE_CASE         use_case;

} OMX_AUDIO_ms12_param_struct_t;

typedef struct OMX_AUDIO_param_query_s
{
    int   apply_start_sample;
    int   id;           /** Identifies the parameter in the set_param function. */
    //char *switch_name;  /** Name of the command line switch without the leading -. */
    int   param_type;   /** Either PARAM_UPDATE_TYPE_INT or PARAM_UPDATE_TYPE_STRING */
    int   num_bytes;
    //int   num_values;   /** Number of integers (PARAM_UPDATE_TYPE_INT only) */
    //int   b_mandatory;  /** Determines if the parameter is optional or mandatory */
    //char *str_name;     /** Name of the parameter to be used in error messages */
    int   mem_pool_start_offset;
} OMX_AUDIO_param_query;

typedef struct OMX_AUDIO_ms12_params_update_s
{
    OMX_S32                num_param_update;
    OMX_S32                mem_pool_total_used_offset;//num of integer
    OMX_AUDIO_param_query  param_update_table[OMX_AUDIO_MS12_MAX_NUM_PARAM_UPDATE];
    OMX_U8                static_mem_pool[OMX_AUDIO_MAX_MS12_UPDATE_PARAM_MEM_SIZE];
}OMX_AUDIO_ms12_update_params;

/** Dolby MS12 decoder type  */
typedef enum OMX_AUDIO_MS12_INPUT_PIN_TYPE {
    OMX_AUDIO_MS12_INPUT_MAIN = 0,           /**<  Main decoder input */
    OMX_AUDIO_MS12_INPUT_ASSOC,              /**<  Associated decoder input */
    OMX_AUDIO_MS12_INPUT_SYSTEM,
    OMX_AUDIO_MS12_INPUT_APP,
    OMX_AUDIO_MS12_INPUT_EXT_PCM
} OMX_AUDIO_MS12_INPUT_PIN_TYPE;

typedef struct OMX_AUDIO_PARAM_MS12CFG {
    OMX_BOOL                        isListeningTest;
    OMX_U8                          inputPinMap;
    OMX_U8                          dummyInputMap;
    OMX_AUDIO_MS12_INPUT_PIN_TYPE   inputPinType;             /**<  decoder type (main/associated) */
    OMX_AUDIO_ms12_param_struct_t   param_struct;
    char output_file_name[OMX_AUDIO_MS_MAX_NUM_OUTPUTS][OMX_AUDIO_MS_MAX_OUTPUT_NAME_LEN];
    char output_name_len[OMX_AUDIO_MS_MAX_NUM_OUTPUTS];
    OMX_AUDIO_ms12_update_params    update_param_struct;
} OMX_AUDIO_PARAM_MS12CFG;

/* =====================MS12 related END here==================== */
#endif


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMX_AudioRTKExt_h */
/* File EOF */
