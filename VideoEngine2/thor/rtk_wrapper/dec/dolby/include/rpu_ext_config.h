/**
 * This product contains one or more programs protected under international
 * and U.S. copyright laws as unpublished works.  They are confidential and
 * proprietary to Dolby Laboratories.  Their reproduction or disclosure, in
 * whole or in part, or the production of derivative works therefrom without
 * the express permission of Dolby Laboratories is prohibited.
 * Copyright 2011 - 2015 by Dolby Laboratories.
 * All rights reserved.
 *
 * @brief common data structures.
 * @file rpu_ext_config.h
 *
 * $Id$
 */

#ifndef _RPU_EXT_CONFIG_H_
#define _RPU_EXT_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif


#define MAX_PIVOT       9
#define MAX_POLY_ORDER  2

#define MAX_DM_EXT_BLOCKS 255

#define MD_EXT_BLOCK_LENGTH(arg)  ((int)sizeof(ext_level_ ## arg ## _t))

typedef struct rpu_ext_config_fixpt_main_s
{
    unsigned int  rpu_VDR_bit_depth;
    unsigned int  rpu_BL_bit_depth;
    unsigned int  rpu_EL_bit_depth;
    unsigned int  coefficient_log2_denom;
    unsigned int  num_pivots[3];
    unsigned int  pivot_value[3][MAX_PIVOT];
    unsigned int  mapping_idc[3];
    unsigned int  poly_order[3][MAX_PIVOT-1];
    int           poly_coef_int[3][MAX_PIVOT-1][MAX_POLY_ORDER+1];
    unsigned int  poly_coef[3][MAX_PIVOT-1][MAX_POLY_ORDER+1];
    unsigned int  MMR_order[2];
    int           MMR_coef_int[2][22];
    unsigned int  MMR_coef[2][22];
    unsigned char NLQ_method_idc;
    unsigned char disable_residual_flag;
    unsigned char el_spatial_resampling_filter_flag;
    unsigned char reserved_8bit;
    unsigned int  NLQ_offset[3];
    int           NLQ_coeff_int[3][3];
    unsigned int  NLQ_coeff[3][3];
    unsigned int  spatial_resampling_filter_flag;
    unsigned int  spatial_resampling_explicit_filter_flag;
    unsigned int  spatial_filter_exp_coef_log2_denom;
    unsigned int  spatial_resampling_mode_hor_idc;
    unsigned int  spatial_resampling_mode_ver_idc;
    unsigned int  spatial_resampling_filter_hor_idc[3];
    unsigned int  spatial_resampling_filter_ver_idc[3];
    unsigned int  spatial_resampling_luma_pivot[2];
    int           spatial_filter_coeff_hor_int[3][8];
    unsigned int  spatial_filter_coeff_hor[3][8];
    int           spatial_filter_coeff_ver_int[2][3][6];
    unsigned int  spatial_filter_coeff_ver[2][3][6];
} rpu_ext_config_fixpt_main_t;

typedef struct dm_metadata_base_s
{
    /* signal attributes */
    unsigned char dm_metadata_id; /* affected_dm_metadata_id<<4|current_dm_metadata_id */
    unsigned char scene_refresh_flag;
    unsigned char YCCtoRGB_coef0_hi;
    unsigned char YCCtoRGB_coef0_lo;
    unsigned char YCCtoRGB_coef1_hi;
    unsigned char YCCtoRGB_coef1_lo;
    unsigned char YCCtoRGB_coef2_hi;
    unsigned char YCCtoRGB_coef2_lo;
    unsigned char YCCtoRGB_coef3_hi;
    unsigned char YCCtoRGB_coef3_lo;
    unsigned char YCCtoRGB_coef4_hi;
    unsigned char YCCtoRGB_coef4_lo;
    unsigned char YCCtoRGB_coef5_hi;
    unsigned char YCCtoRGB_coef5_lo;
    unsigned char YCCtoRGB_coef6_hi;
    unsigned char YCCtoRGB_coef6_lo;
    unsigned char YCCtoRGB_coef7_hi;
    unsigned char YCCtoRGB_coef7_lo;
    unsigned char YCCtoRGB_coef8_hi;
    unsigned char YCCtoRGB_coef8_lo;
    unsigned char YCCtoRGB_offset0_byte3;
    unsigned char YCCtoRGB_offset0_byte2;
    unsigned char YCCtoRGB_offset0_byte1;
    unsigned char YCCtoRGB_offset0_byte0;
    unsigned char YCCtoRGB_offset1_byte3;
    unsigned char YCCtoRGB_offset1_byte2;
    unsigned char YCCtoRGB_offset1_byte1;
    unsigned char YCCtoRGB_offset1_byte0;
    unsigned char YCCtoRGB_offset2_byte3;
    unsigned char YCCtoRGB_offset2_byte2;
    unsigned char YCCtoRGB_offset2_byte1;
    unsigned char YCCtoRGB_offset2_byte0;
    unsigned char RGBtoLMS_coef0_hi;
    unsigned char RGBtoLMS_coef0_lo;
    unsigned char RGBtoLMS_coef1_hi;
    unsigned char RGBtoLMS_coef1_lo;
    unsigned char RGBtoLMS_coef2_hi;
    unsigned char RGBtoLMS_coef2_lo;
    unsigned char RGBtoLMS_coef3_hi;
    unsigned char RGBtoLMS_coef3_lo;
    unsigned char RGBtoLMS_coef4_hi;
    unsigned char RGBtoLMS_coef4_lo;
    unsigned char RGBtoLMS_coef5_hi;
    unsigned char RGBtoLMS_coef5_lo;
    unsigned char RGBtoLMS_coef6_hi;
    unsigned char RGBtoLMS_coef6_lo;
    unsigned char RGBtoLMS_coef7_hi;
    unsigned char RGBtoLMS_coef7_lo;
    unsigned char RGBtoLMS_coef8_hi;
    unsigned char RGBtoLMS_coef8_lo;
    unsigned char signal_eotf_hi;
    unsigned char signal_eotf_lo;
    unsigned char signal_eotf_param0_hi;
    unsigned char signal_eotf_param0_lo;
    unsigned char signal_eotf_param1_hi;
    unsigned char signal_eotf_param1_lo;
    unsigned char signal_eotf_param2_byte3;
    unsigned char signal_eotf_param2_byte2;
    unsigned char signal_eotf_param2_byte1;
    unsigned char signal_eotf_param2_byte0;
    unsigned char signal_bit_depth;
    unsigned char signal_color_space;
    unsigned char signal_chroma_format;
    unsigned char signal_full_range_flag;
    /* source display attributes */
    unsigned char source_min_PQ_hi;
    unsigned char source_min_PQ_lo;
    unsigned char source_max_PQ_hi;
    unsigned char source_max_PQ_lo;
    unsigned char source_diagonal_hi;
    unsigned char source_diagonal_lo;
    /* extended metadata */
    unsigned char num_ext_blocks;
} dm_metadata_base_t;

typedef struct ext_level_1_s
{
    unsigned char min_PQ_hi;
    unsigned char min_PQ_lo;
    unsigned char max_PQ_hi;
    unsigned char max_PQ_lo;
    unsigned char avg_PQ_hi;
    unsigned char avg_PQ_lo;
} ext_level_1_t;

typedef struct ext_level_2_s
{
    unsigned char target_max_PQ_hi       ;
    unsigned char target_max_PQ_lo       ;
    unsigned char trim_slope_hi          ;
    unsigned char trim_slope_lo          ;
    unsigned char trim_offset_hi         ;
    unsigned char trim_offset_lo         ;
    unsigned char trim_power_hi          ;
    unsigned char trim_power_lo          ;
    unsigned char trim_chroma_weight_hi  ;
    unsigned char trim_chroma_weight_lo  ;
    unsigned char trim_saturation_gain_hi;
    unsigned char trim_saturation_gain_lo;
    unsigned char ms_weight_hi           ;
    unsigned char ms_weight_lo           ;
} ext_level_2_t;

typedef struct ext_level_4_s
{
    unsigned char anchor_PQ_hi       ;
    unsigned char anchor_PQ_lo       ;
    unsigned char anchor_power_hi    ;
    unsigned char anchor_power_lo    ;
} ext_level_4_t;

typedef struct ext_level_5_s
{
    unsigned char active_area_left_offset_hi  ;
    unsigned char active_area_left_offset_lo  ;
    unsigned char active_area_right_offset_hi ;
    unsigned char active_area_right_offset_lo ;
    unsigned char active_area_top_offset_hi   ;
    unsigned char active_area_top_offset_lo   ;
    unsigned char active_area_bottom_offset_hi;
    unsigned char active_area_bottom_offset_lo;
} ext_level_5_t;

typedef struct ext_level_6_s
{
    unsigned char max_display_mastering_luminance_hi;
    unsigned char max_display_mastering_luminance_lo;
    unsigned char min_display_mastering_luminance_hi;
    unsigned char min_display_mastering_luminance_lo;
    unsigned char max_content_light_level_hi        ;
    unsigned char max_content_light_level_lo        ;
    unsigned char max_frame_average_light_level_hi  ;
    unsigned char max_frame_average_light_level_lo  ;
} ext_level_6_t;

typedef struct ext_level_255_s
{
    unsigned char dm_run_mode   ;
    unsigned char dm_run_version;
    unsigned char dm_debug0     ;
    unsigned char dm_debug1     ;
    unsigned char dm_debug2     ;
    unsigned char dm_debug3     ;
} ext_level_255_t;

typedef struct dm_metadata_ext_s
{
    unsigned char ext_block_length_byte3;
    unsigned char ext_block_length_byte2;
    unsigned char ext_block_length_byte1;
    unsigned char ext_block_length_byte0;
    unsigned char ext_block_level;
    union {
        ext_level_1_t level_1;
        ext_level_2_t level_2;
        ext_level_4_t level_4;
        ext_level_5_t level_5;
        ext_level_6_t level_6;
        ext_level_255_t level_255;
    } l;
} dm_metadata_ext_t;

typedef struct dm_metadata_s {
    dm_metadata_base_t base;
    dm_metadata_ext_t ext[MAX_DM_EXT_BLOCKS];
} dm_metadata_t;

#ifdef __cplusplus
}
#endif

#endif /* _RPU_EXT_CONFIG_H_ */
