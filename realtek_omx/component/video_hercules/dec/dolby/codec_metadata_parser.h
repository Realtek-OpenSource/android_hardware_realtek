#ifndef CODEC_METADATA_PARSER_H
#define CODEC_METADATA_PARSER_H
#include <stdbool.h>
#include <dv_cdefs.h>
#include "OMX_Core.h"
#include "OMX_Types.h"
#include "rpu_ext_config.h"
#include "RtkControlPath.h"

void release_rpu_parser_engine();
OMX_ERRORTYPE init_rpu_parser_engine();
OMX_ERRORTYPE process_metadata(RpuItem data);
OMX_ERRORTYPE get_rpu_data(DolbyMetadataItem *data);
void invalid_rpu_data_queue();
#endif
