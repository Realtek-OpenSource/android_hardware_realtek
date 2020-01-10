#include <port.h>
#include <OSAL_RTK.h>
#include <string.h> // memset, memcpy
#include "util.h"
#include "dbgtrace.h"
#include <InbandAPI.h>
#include <sys/mman.h>

//RTK VE1 header file
#include "vpuconfig.h"
#include "vpuapi.h"
#include "vpuapifunc.h"
#include "coda9/coda9_regdefine.h"
#include "coda9/coda9_vpuconfig.h"
#include "wave/wave5_regdefine.h"
#include "vpuerror.h"
#include <basecomp.h>
#ifdef ENABLE_TEE_DRM_FLOW
#include "tee_client_api.h"
#include "tee_api.h"
#include <system/SystemMemory.h>
#include <allocator/Allocator.h>
#include <allocator/IonAllocator.h>
#include <allocator/MallocAllocator.h>
#include <system_mem.h>
#endif

struct Ts103433Info
{
    int ts103433_spec_version;
    int ts103433_payload_mode;
};

struct ColourVolumeReconstructionInfo
{
    int cv_rec_id;
    OMX_BOOL cv_rec_cancel_flag;
    OMX_BOOL cv_rec_persistence_flag;
    OMX_BOOL cv_rec_target_info_flag;

    int cv_rec_primaries;
    int cv_rec_matrix_coefficients;

    int tone_mapping_input_signal_black_level_offset;
    int tone_mapping_input_signal_white_level_offset;

    int shadow_gain_control;
    int highlight_gain_control;
    int mid_tone_width_adjustment_factor;
    int tone_mapping_output_fine_tuning_num_val;
    int tone_mapping_output_fine_tuning_x[10];
    int tone_mapping_output_fine_tuning_y[10];

    int saturation_gain_num_val;
    int saturation_gain_x[6];
    int saturation_gain_y[6];
};

typedef struct RTKALLOCATOR_MEM_HDR {
    OSAL_S32    mSize;
    OSAL_U8     *mVirAddr;
    OSAL_U32    mPhyAddr;
    SystemMemory *mBufferMemory;
} RTKALLOCATOR_MEM_HDR;

typedef struct HdrParameterParser
{
    DecHandle handle;
    CodStd bitstreamFormat;
    int coreIdx;

    h265_mastering_display_colour_volume_t m_mastering;
    h265_vui_param_t m_vui;
    h265_colour_remapping_info_t m_remapping;
    h265_content_light_level_info_t m_light_level;
    h265_alternative_transfer_characteristics_t m_alternative_transfer;

    struct Ts103433Info m_ts103433_info;
    struct ColourVolumeReconstructionInfo m_cvri;

    vpu_buffer_t m_vpu_buffer;
    Uint8 *mp_work_buffer;

    int m_query_type;
    unsigned int m_user_data_header;
    unsigned int m_t35_header;

    struct tch_metadata *mp_technicolor_buffer;
#ifdef ENABLE_TEE_DRM_FLOW
    TEEC_Context        *ctx;
    TEEC_Session        *sess;
    RTK_TEEC_Session    *rtk_sess;
    RTKALLOCATOR_MEM_HDR *m_hdr_buffer;
    RTKALLOCATOR_MEM_HDR *m_tch_buffer;
#endif
} HdrParameterParser;

void HdrAllocate(HdrParameterParser *pHdr, DecHandle handle, CodStd bitstreamFormat, int coreIdx);
void HdrRelease(HdrParameterParser *pHdr);

void HdrParseHeaderPicRun(HdrParameterParser *pHdr, DecOutputInfo outputInfo);
void HdrParseHeaderSeqInit(HdrParameterParser *pHdr, DecInitialInfo initialInfo);

void HdrInformSequenceChange(HdrParameterParser *pHdr);

void HdrGetMasteringDisplay(HdrParameterParser *pHdr, private_rtk_v1_data *p_state);
void HdrGetVui(HdrParameterParser *pHdr, private_rtk_v1_data *p_state);

void HdrGetLumaChromaOffsetTableAddr(HdrParameterParser *pHdr, int myIndex, int width, int height, unsigned int *pLumaOffTblAddr, unsigned int *pChromeOffTblAddr);

void HdrGetTechniColor(HdrParameterParser *pHdr, private_rtk_v1_data *p_state, int display_index);
void HdrGetHdr(HdrParameterParser *pHdr, private_rtk_v1_data *p_state, int display_index);
void HdrGetColorAspects(HdrParameterParser *pHdr, ColorAspects *param);
void HdrGetStaticInfo(HdrParameterParser *pHdr, HDRStaticInfo *param);
void HdrGetHdrMetaData(HdrParameterParser *pHdr, void *addr, private_rtk_v1_data *p_state);
#ifdef ENABLE_TEE_DRM_FLOW
void HdrSetTEEParam(HdrParameterParser *pHdr, TEEC_Context *ctx, TEEC_Session *sess, RTK_TEEC_Session *rtk_sess);
#endif
