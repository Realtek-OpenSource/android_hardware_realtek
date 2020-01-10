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
 * @file rpu_common.h
 *
 * $Id$
 */

#ifndef _RPU_COMMON_H_
#define _RPU_COMMON_H_

#include <rpu_std.h>
#include <rpu_debug.h>
#include "rpu_api_common.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct level_limits_s
{
    unsigned int num_y_partitions;
    unsigned int num_x_partitions;
    unsigned int num_pivots      ;
    unsigned int nlq_num_pivots  ;
    unsigned int prev_rpu_id     ;
} level_limits_t;

typedef struct profile_limits_s
{
    int mapping_method[16];
    int mapping_cs[16];
    int mapping_cf[4];
    int exp_resample;
    int res_upsample;
} profile_limits_t;


struct rpu_context_s
{
    /*  number of available predictors */
    int num_POLY_param_predictors[3][MAX_NUM_MAPPING_PIVOTS - 1];
    int num_MMR_param_predictors [3][MAX_NUM_MAPPING_PIVOTS - 1];
    int num_POW_param_predictors [3][MAX_NUM_MAPPING_PIVOTS - 1];
    int num_LUT_param_predictors [3][MAX_NUM_MAPPING_PIVOTS - 1];
    int num_chroma_resampling_filter_2D_predictors[2];
    int num_chroma_resampling_filter_1D_predictors[2][2];
    int num_nlq_param_predictors[MAX_NUM_NLQ_PIVOTS-1][3];

    /* this variables are to remember the first partition in a frame with this prediction method */
    int first_POLY_partition[3][MAX_NUM_MAPPING_PIVOTS - 1];
    int first_MMR_partition [3][MAX_NUM_MAPPING_PIVOTS - 1];
    int first_POW_partition [3][MAX_NUM_MAPPING_PIVOTS - 1];
    int first_LUT_partition [3][MAX_NUM_MAPPING_PIVOTS - 1];

    /* maximum levels based on initialization */
    unsigned int max_partitions;
    unsigned int max_num_pivots;
    unsigned int max_nlq_num_pivots;
    unsigned int max_prev_rpu_ids;
};


int validate_level(rpu_data_t* rpu_data, rpu_msg_log_func_t msg_log, print_severity_t print_severity);
int validate_profile(rpu_data_t* rpu_dat, rpu_msg_log_func_t msg_log, print_severity_t print_severitya);
int validate_spatial_filter(rpu_data_t* rpu_data, rpu_msg_log_func_t msg_log, print_severity_t print_severity);
int assign_pivot_values(rpu_data_t* rpu_data);
int assign_nlq_pivot_values(rpu_data_t* rpu_data);

#ifdef __cplusplus
}
#endif

#endif /* _RPU_COMMON_H_ */
