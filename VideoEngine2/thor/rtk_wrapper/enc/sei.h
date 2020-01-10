#include "util.h"

#ifndef SEI_H
#define SEI_H

#define MAX_LAYER_NUMBER 2
#define MAX_DEPENDENT_SUBSEQ 5
// tone mapping information
#define MAX_CODED_BIT_DEPTH  12
#define MAX_SEI_BIT_DEPTH    12
#define MAX_NUM_PIVOTS       (1<<MAX_CODED_BIT_DEPTH)
// This is only temp
//! Buffering Period Information
#define MAX_CPB_CNT_MINUS1 31
#define MAX_PIC_STRUCT_VALUE 16
#define MAX_FN 256

#define AGGREGATION_PACKET_TYPE 4
#define SEI_PACKET_TYPE 5  // Tian Dong: See VCEG-N72, it need updates

#define NORMAL_SEI 0
#define AGGREGATION_SEI 1


//! definition of SEI payload type
typedef enum {
    SEI_BUFFERING_PERIOD = 0,
    SEI_PIC_TIMING,
    SEI_PAN_SCAN_RECT,
    SEI_FILLER_PAYLOAD,
    SEI_USER_DATA_REGISTERED_ITU_T_T35,
    SEI_USER_DATA_UNREGISTERED,
    SEI_RECOVERY_POINT,
    SEI_DEC_REF_PIC_MARKING_REPETITION,
    SEI_SPARE_PIC,
    SEI_SCENE_INFO,
    SEI_SUB_SEQ_INFO,
    SEI_SUB_SEQ_LAYER_CHARACTERISTICS,
    SEI_SUB_SEQ_CHARACTERISTICS,
    SEI_FULL_FRAME_FREEZE,
    SEI_FULL_FRAME_FREEZE_RELEASE,
    SEI_FULL_FRAME_SNAPSHOT,
    SEI_PROGRESSIVE_REFINEMENT_SEGMENT_START,
    SEI_PROGRESSIVE_REFINEMENT_SEGMENT_END,
    SEI_MOTION_CONSTRAINED_SLICE_GROUP_SET,
    SEI_FILM_GRAIN_CHARACTERISTICS,
    SEI_DEBLOCKING_FILTER_DISPLAY_PREFERENCE,
    SEI_STEREO_VIDEO_INFO,
    SEI_POST_FILTER_HINTS,
    SEI_TONE_MAPPING,
    SEI_SCALABILITY_INFO,
    SEI_SUB_PIC_SCALABLE_LAYER,
    SEI_NON_REQUIRED_LAYER_REP,
    SEI_PRIORITY_LAYER_INFO,
    SEI_LAYERS_NOT_PRESENT,
    SEI_LAYER_DEPENDENCY_CHANGE,
    SEI_SCALABLE_NESTING,
    SEI_BASE_LAYER_TEMPORAL_HRD,
    SEI_QUALITY_LAYER_INTEGRITY_CHECK,
    SEI_REDUNDANT_PIC_PROPERTY,
    SEI_TL0_DEP_REP_INDEX,
    SEI_TL_SWITCHING_POINT,
    SEI_PARALLEL_DECODING_INFO,
    SEI_MVC_SCALABLE_NESTING,
    SEI_VIEW_SCALABILITY_INFO,
    SEI_MULTIVIEW_SCENE_INFO,
    SEI_MULTIVIEW_ACQUISITION_INFO,
    SEI_NON_REQUIRED_VIEW_COMPONENT,
    SEI_VIEW_DEPENDENCY_CHANGE,
    SEI_OPERATION_POINTS_NOT_PRESENT,
    SEI_BASE_VIEW_TEMPORAL_HRD,
    SEI_FRAME_PACKING_ARRANGEMENT,

    SEI_MAX_ELEMENTS  //!< number of maximum syntax elements
} SEI_type;

typedef struct
{
    OMX_S32 seq_parameter_set_id;
    OMX_S32 nal_initial_cpb_removal_delay[MAX_CPB_CNT_MINUS1+1];
    OMX_S32 nal_initial_cpb_removal_delay_offset[MAX_CPB_CNT_MINUS1+1];
    OMX_S32 vcl_initial_cpb_removal_delay[MAX_CPB_CNT_MINUS1+1];
    OMX_S32 vcl_initial_cpb_removal_delay_offset[MAX_CPB_CNT_MINUS1+1];

    //Bitstream *data;
    OMX_U8 *data;
    OMX_S32 payloadSize;
} bufferingperiod_information_struct;

//! SEI structure
typedef struct
{
    OMX_BOOL available;
    OMX_S32 payloadSize;
    OMX_U8 subPacketType;
    OMX_U8* data;
} sei_struct;

//! Spare Picture
typedef struct
{
    OMX_S32 target_frame_num;
    OMX_S32 num_spare_pics;
    OMX_S32 payloadSize;
    //Bitstream* data;
    OMX_U8 *data;
} spare_picture_struct;

//! Subseq Information
typedef struct
{
    OMX_S32 subseq_layer_num;
    OMX_S32 subseq_id;
    OMX_U32 last_picture_flag;
    OMX_U32 stored_frame_cnt;

    OMX_S32 payloadSize;
    //Bitstream* data;
    OMX_U8 *data;
} subseq_information_struct;

//! Subseq Layer Information
typedef struct
{
    OMX_U16 bit_rate[MAX_LAYER_NUMBER];
    OMX_U16 frame_rate[MAX_LAYER_NUMBER];
    OMX_U8 data[4*MAX_LAYER_NUMBER];
    OMX_S32 layer_number;
    OMX_S32 payloadSize;
} subseq_layer_information_struct;

//! Subseq Characteristics
typedef struct
{
    OMX_S32 subseq_layer_num;
    OMX_S32 subseq_id;
    OMX_S32 duration_flag;
    OMX_U32 subseq_duration;
    OMX_U32 average_rate_flag;
    OMX_U32 average_bit_rate;
    OMX_U32 average_frame_rate;
    OMX_S32 num_referenced_subseqs;
    OMX_S32 ref_subseq_layer_num[MAX_DEPENDENT_SUBSEQ];
    OMX_S32 ref_subseq_id[MAX_DEPENDENT_SUBSEQ];

    //Bitstream* data;
    OMX_U8 *data;
    OMX_S32 payloadSize;
} subseq_char_information_struct;

typedef struct
{
    OMX_S32 scene_id;
    OMX_S32 scene_transition_type;
    OMX_S32 second_scene_id;

    //Bitstream* data;
    OMX_U8 *data;
    OMX_S32 payloadSize;
} scene_information_struct;

//! PanScanRect Information
typedef struct
{
    OMX_BOOL seiHasPanScanRectInfo;
    OMX_S32 pan_scan_rect_id;
    OMX_S32 pan_scan_rect_cancel_flag;
    OMX_S32 pan_scan_cnt_minus1;             //!< ranges from 0 to 2
    OMX_S32 pan_scan_rect_left_offset;
    OMX_S32 pan_scan_rect_right_offset;
    OMX_S32 pan_scan_rect_top_offset;
    OMX_S32 pan_scan_rect_bottom_offset;
    OMX_S32 pac_scan_rect_repetition_period;

    //Bitstream *data;
    OMX_U8 data[16];
    OMX_S32 payloadSize;
} panscanrect_information_struct;
//! User_data_unregistered Information
typedef struct
{
    OMX_U8 *byte;
    OMX_S32 total_byte;
    //Bitstream *data;
    OMX_U8 *data;
    OMX_S32 payloadSize;
} user_data_unregistered_information_struct;

//! User_data_registered_itu_t_t35 Information
typedef struct
{
    OMX_S8 *byte;
    OMX_S32 total_byte;
    OMX_S32 itu_t_t35_country_code;
    OMX_S32 itu_t_t35_country_code_extension_byte;
    //Bitstream *data;
    OMX_U8 *data;
    OMX_S32 payloadSize;
} user_data_registered_itu_t_t35_information_struct;

//! Recovery Point Information
typedef struct
{
    OMX_U32  recovery_frame_cnt;
    OMX_U8 exact_match_flag;
    OMX_U8 broken_link_flag;
    OMX_U8 changing_slice_group_idc;

    //Bitstream *data;
    OMX_U8 *data;
    OMX_S32 payloadSize;
} recovery_point_information_struct;

//! Picture timing Information
typedef struct
{
    OMX_S32 cpb_removal_delay;
    OMX_S32 dpb_output_delay;
    OMX_S32 pic_struct;
    OMX_BOOL clock_timestamp_flag[MAX_PIC_STRUCT_VALUE];
    OMX_S32 ct_type;
    OMX_BOOL nuit_field_based_flag;
    OMX_S32 counting_type;
    OMX_BOOL full_timestamp_flag;
    OMX_BOOL discontinuity_flag;
    OMX_BOOL cnt_dropped_flag;
    OMX_S32 n_frames;
    OMX_S32 seconds_value;
    OMX_S32 minutes_value;
    OMX_S32 hours_value;
    OMX_BOOL seconds_flag;
    OMX_BOOL minutes_flag;
    OMX_BOOL hours_flag;
    OMX_S32 time_offset;

    //Bitstream *data;
    OMX_U8 *data;
    OMX_S32 payloadSize;
} pictiming_information_struct;


//! Decoded reference picture marking repetition Information
typedef struct
{
    OMX_BOOL original_idr_flag;
    OMX_S32 original_frame_num;
    OMX_BOOL original_field_pic_flag;
    OMX_BOOL original_bottom_field_flag;
    //DecRefPicMarking_t *dec_ref_pic_marking_buffer_saved; //Fuchun 20150304 disable, because we didn't need it.

    //Bitstream *data;
    OMX_U8 *data;
    OMX_S32 payloadSize;
} drpm_repetition_information_struct;


//! Frame packing arrangement Information
typedef struct
{
    OMX_U32  frame_packing_arrangement_id;
    OMX_BOOL       frame_packing_arrangement_cancel_flag;
    OMX_U8 frame_packing_arrangement_type;
    OMX_BOOL       quincunx_sampling_flag;
    OMX_U8 content_interpretation_type;
    OMX_BOOL       spatial_flipping_flag;
    OMX_BOOL       frame0_flipped_flag;
    OMX_BOOL       field_views_flag;
    OMX_BOOL       current_frame_is_frame0_flag;
    OMX_BOOL       frame0_self_contained_flag;
    OMX_BOOL       frame1_self_contained_flag;
    OMX_U8 frame0_grid_position_x;
    OMX_U8 frame0_grid_position_y;
    OMX_U8 frame1_grid_position_x;
    OMX_U8 frame1_grid_position_y;
    OMX_U8 frame_packing_arrangement_reserved_byte;
    OMX_U32  frame_packing_arrangement_repetition_period;
    OMX_BOOL       frame_packing_arrangement_extension_flag;

    //Bitstream *data;
    OMX_U8 *data;
    OMX_S32 payloadSize;
} frame_packing_arrangement_information_struct;


//! Post Filter Hints Information
typedef struct
{
    OMX_U32  filter_hint_size_y;
    OMX_U32  filter_hint_size_x;
    OMX_U32  filter_hint_type;
    OMX_S32           ***filter_hint;
    OMX_U32  additional_extension_flag;

    //Bitstream *data;
    OMX_U8 *data;
    OMX_S32 payloadSize;
} post_filter_information_struct;

typedef struct
{
    OMX_U32  tone_map_id;
    OMX_U8 tone_map_cancel_flag;
    OMX_U32  tone_map_repetition_period;
    OMX_U8 coded_data_bit_depth;
    OMX_U8 sei_bit_depth;
    OMX_U32  model_id;
    // variables for model 0
    OMX_S32  min_value;
    OMX_S32  max_value;
    // variables for model 1
    OMX_S32  sigmoid_midpoint;
    OMX_S32  sigmoid_width;
    // variables for model 2
    OMX_S32 start_of_coded_interval[1<<MAX_SEI_BIT_DEPTH];
    // variables for model 3
    OMX_S32 num_pivots;
    OMX_S32 coded_pivot_value[MAX_NUM_PIVOTS];
    OMX_S32 sei_pivot_value[MAX_NUM_PIVOTS];

    //Bitstream *data;
    OMX_U8 *data;
    OMX_S32 payloadSize;
} ToneMappingSEI;

// Globals
struct sei_params {
    OMX_BOOL seiHasDRPMRepetition_info;
    drpm_repetition_information_struct seiDRPMRepetition;

    //!< sei_message[0]: this struct is to store the sei message packetized independently
    //!< sei_message[1]: this struct is to store the sei message packetized together with slice data
    sei_struct sei_message[2];
    OMX_BOOL seiHasSparePicture;
    //extern OMX_BOOL sei_has_sp;
    spare_picture_struct seiSparePicturePayload;
    OMX_BOOL seiHasSubseqInfo;
    subseq_information_struct seiSubseqInfo[MAX_LAYER_NUMBER];
    OMX_BOOL seiHasSubseqLayerInfo;
    subseq_layer_information_struct seiSubseqLayerInfo;
    OMX_BOOL seiHasSubseqChar;
    subseq_char_information_struct seiSubseqChar;
    OMX_BOOL seiHasSceneInformation;
    scene_information_struct seiSceneInformation;
    OMX_BOOL seiHasPanScanRectInfo;
    panscanrect_information_struct seiPanScanRectInfo;
    OMX_BOOL seiHasUser_data_unregistered_info;
    user_data_unregistered_information_struct seiUser_data_unregistered;
    OMX_BOOL seiHasUser_data_registered_itu_t_t35_info;
    user_data_registered_itu_t_t35_information_struct seiUser_data_registered_itu_t_t35;
    OMX_BOOL seiHasRecoveryPoint_info;
    recovery_point_information_struct seiRecoveryPoint;
    OMX_BOOL seiHasBufferingPeriod_info;
    bufferingperiod_information_struct seiBufferingPeriod;
    OMX_BOOL seiHasPicTiming_info;
    pictiming_information_struct seiPicTiming;
    OMX_BOOL seiHasFramePackingArrangement_info;
    frame_packing_arrangement_information_struct seiFramePackingArrangement;

    OMX_BOOL seiHasTone_mapping;
    ToneMappingSEI seiToneMapping;
    OMX_BOOL seiHasPostFilterHints_info;
    post_filter_information_struct seiPostFilterHints;

    OMX_BOOL seiHasTemporal_reference;
    OMX_BOOL seiHasClock_timestamp;
    OMX_BOOL seiHasPanscan_rect;
    OMX_BOOL seiHasHrd_picture;
    OMX_BOOL seiHasFiller_payload;
    OMX_BOOL seiHasUser_data_registered_itu_t_t35;
    OMX_BOOL seiHasUser_data_unregistered;
    OMX_BOOL seiHasRef_pic_buffer_management_repetition;
    OMX_BOOL seiHasSpare_picture;
    OMX_BOOL seiHasSubseq_information;
    OMX_BOOL seiHasSubseq_layer_characteristics;
    OMX_BOOL seiHasSubseq_characteristics;

};

typedef struct sei_params SEIParameters;

#endif
