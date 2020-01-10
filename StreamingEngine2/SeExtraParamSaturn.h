////////////////////////////////////////////////////////////////////////////////
// SE Extra Parameters For Saturn
//
// Author: zackchiu@realtek.com
//
// Created: 1/20/2011
////////////////////////////////////////////////////////////////////////////////

#ifndef _SE_EXTRA_PARAM_H_
#define _SE_EXTRA_PARAM_H_

#include "SeLib.h"

// Extra Parameters for Register CLR_FMT on Saturn. Saturn Spec page 6
//
typedef struct _SE_COLOR_FORMAT_EX
{
    bool bInputSrcColorFormatBigEndian;             // For field: big_endian_i1
    bool bInputDestColorFormatBigEndian;            // For field: big_endian_i2
    bool bOutputColorFormatBigEndian;               // For field: big_endian_o
    bool bEnableRoundingOption;                     // For field: rounding_en
} SE_COLOR_FORMAT_EX;

// Extra Parameters for Command Format_conv on Saturn. Saturn Spec page 22
//
typedef struct _SE_FORMAT_CONVERT_EX
{
    SEINFO_ROPMODE ropMode;
    SEINFO_ALPHAMODE destAlphaModeSelect;           // For Word5, field: sel_dest_alpha 
    uint8_t destAplhaValue;
    bool bSyncVO;                                   // For Word5, field: sync_vo
    SEINFO_OUTPUT_ALPHAMODE outputAlphaModeSelect;  // For Word5, field: sel_output_alpha
    SEINFO_ROPCODE ropCode;                         // For Word5, field: ROP code
    SEINFO_ALPHAMODE srcAlphaModeSelect;            // For Word5, field: sel_src_alpha 
    uint8_t srcAplhaValue;
    SEINFO_COLORKEY colorKeySelect;                 // For Word5, field: bitblit_color_key
    SEINFO_SOURCE_COLOR_TRANSFORM srcClrTranform;   // For Word5, field: src_clr_tranform
    bool bEnableSrcClrTransparency;                 // For Word5, field: src_clr_transparency
    bool bEnableDirectFB;                           // For Word2, field: directFB
    bool bEnableDfbDstPremultiply;                  // For Word5, field: fb_dst_premultiply
    bool bEnableDfbSrcPremulcolor;                  // For Word5, field: fb_src_premulcolor
    bool bEnableDfbSrcPremultiply;                  // For Word5, field: fb_src_premultiply
    bool bEnableDfbXor;                             // For Word5, field: fb_xor
    bool bEnableDfbColorize;                        // For Word5, field: fb_colorize
    bool bEnableDfbReplaceSrcAlphaWithConstAlpha;   // For Word5, field: fb_blend_coloralpha
    bool bEnableDfbModulateSrcAlphaWithConstAlpha;  // For Word5, field: fb_blend_alphachannel
    bool bEnableDfbDemultiply;                      // For Word5, field: fb_demultiply
    SEINFO_DFB_CLR_BLEND_MODE selSrcClrBlend;       // For Word5, field: fb_sel_srcclr_blend
    SEINFO_DFB_CLR_BLEND_MODE selDestClrBlend;      // For Word5, field: fb_sel_destclr_blend
    SEINFO_DFB_OPERATION dfbOperation;              // For Word5, field: ROP code
    bool bEnableFormatConvertWithBitblit;           // For Word2, field: Format conversion + Bitblit

    uint8_t constAplhaValue;                        // This will update Register: SRC_ALPHA. For fb_src_premulcolor, fb_blend_coloralpha, fb_blend_alphachannel
    uint32_t constColorValue;                       // This will update the Register: SRC_COLOR. For fb_colorize.

    // The following variables are needed for source color transform
    // Saturn Spec, page 40, Register: SRC_CLR_RED, SCR_CLR_GREEN, SRC_CLR_BLUE, SRC_CLR_ALPHA
    SEREG_SRC_CLR_RED srcColorRed;
    SEREG_SRC_CLR_GREEN srcColorGreen;
    SEREG_SRC_CLR_BLUE srcColorBlue;
    SEREG_SRC_CLR_ALPHA srcColorAlpha;    
} SE_FORMAT_CONVERT_EX;

// Extra Parameters for Command Bitblit on Saturn. Saturn Spec page 31
//
typedef struct _SE_BITBLIT_EX
{
    bool bSyncVO;                                   // For Word2, field: sync_vo
    SEINFO_SOURCE_COLOR_TRANSFORM srcClrTranform;   // For Word4, field: src_clr_tranform
    bool bEnableSrcClrTransparency;                 // For Word4, field: src_clr_transparency
    bool bEnableDirectFB;                           // For Word4, field: directFB
    bool bEnableDfbDstPremultiply;                  // For Word4, field: fb_dst_premultiply
    bool bEnableDfbSrcPremulcolor;                  // For Word4, field: fb_src_premulcolor
    bool bEnableDfbSrcPremultiply;                  // For Word4, field: fb_src_premultiply
    bool bEnableDfbXor;                             // For Word4, field: fb_xor
    bool bEnableDfbColorize;                        // For Word4, field: fb_colorize
    bool bEnableDfbReplaceSrcAlphaWithConstAlpha;   // For Word4, field: fb_blend_coloralpha
    bool bEnableDfbModulateSrcAlphaWithConstAlpha;  // For Word4, field: fb_blend_alphachannel
    bool bEnableDfbDemultiply;                      // For Word4, field: fb_demultiply
    SEINFO_DFB_CLR_BLEND_MODE selSrcClrBlend;       // For Word4, field: fb_sel_srcclr_blend
    SEINFO_DFB_CLR_BLEND_MODE selDestClrBlend;      // For Word4, field: fb_sel_destclr_blend
    SEINFO_DFB_OPERATION dfbOperation;              // For Word2, field: ROP code

    uint8_t constAplhaValue;                        // This will update Register: SRC_ALPHA. For fb_src_premulcolor, fb_blend_coloralpha, fb_blend_alphachannel
    uint32_t constColorValue;                       // This will update the Register: SRC_COLOR. For fb_colorize.
    
    // The following variables are needed for source color transform
    // Saturn Spec, page 40, Register: SRC_CLR_RED, SCR_CLR_GREEN, SRC_CLR_BLUE, SRC_CLR_ALPHA
    SEREG_SRC_CLR_RED srcColorRed;
    SEREG_SRC_CLR_GREEN srcColorGreen;
    SEREG_SRC_CLR_BLUE srcColorBlue;
    SEREG_SRC_CLR_ALPHA srcColorAlpha;     
} SE_BITBLIT_EX;

// Extra Parameters for Command Format_conv on Saturn. Saturn Spec page 22
//
typedef struct _SE_STRETCH_EX
{
    SEINFO_ALPHAMODE destAlphaModeSelect;           // For Word5, field: sel_dest_alpha 
    uint8_t destAplhaValue;
    bool bSyncVO;                                   // For Word5, field: sync_vo
    SEINFO_OUTPUT_ALPHAMODE outputAlphaModeSelect;  // For Word5, field: sel_output_alpha
    SEINFO_ROPCODE ropCode;                         // For Word5, field: ROP code
    SEINFO_ALPHAMODE srcAlphaModeSelect;            // For Word5, field: sel_src_alpha 
    uint8_t srcAplhaValue;
    SEINFO_COLORKEY colorKeySelect;                 // For Word5, field: bitblit_color_key
    SEINFO_SOURCE_COLOR_TRANSFORM srcClrTranform;   // For Word5, field: src_clr_tranform
    bool bEnableSrcClrTransparency;                 // For Word5, field: src_clr_transparency
    bool bEnableDirectFB;                           // For Word2, field: directFB
    bool bEnableDfbDstPremultiply;                  // For Word5, field: fb_dst_premultiply
    bool bEnableDfbSrcPremulcolor;                  // For Word5, field: fb_src_premulcolor
    bool bEnableDfbSrcPremultiply;                  // For Word5, field: fb_src_premultiply
    bool bEnableDfbXor;                             // For Word5, field: fb_xor
    bool bEnableDfbColorize;                        // For Word5, field: fb_colorize
    bool bEnableDfbReplaceSrcAlphaWithConstAlpha;   // For Word5, field: fb_blend_coloralpha
    bool bEnableDfbModulateSrcAlphaWithConstAlpha;  // For Word5, field: fb_blend_alphachannel
    bool bEnableDfbDemultiply;                      // For Word5, field: fb_demultiply
    SEINFO_DFB_CLR_BLEND_MODE selSrcClrBlend;       // For Word5, field: fb_sel_srcclr_blend
    SEINFO_DFB_CLR_BLEND_MODE selDestClrBlend;      // For Word5, field: fb_sel_destclr_blend
    SEINFO_DFB_OPERATION dfbOperation;              // For Word5, field: ROP code
    bool bEnableStretchWithBitblit;                 // For Word2, field: Stretch + Bitblit

    uint8_t constAplhaValue;                        // This will update Register: SRC_ALPHA. For fb_src_premulcolor, fb_blend_coloralpha, fb_blend_alphachannel
    uint32_t constColorValue;                       // This will update the Register: SRC_COLOR. For fb_colorize.

    // The following variables are needed for source color transform
    // Saturn Spec, page 40, Register: SRC_CLR_RED, SCR_CLR_GREEN, SRC_CLR_BLUE, SRC_CLR_ALPHA
    SEREG_SRC_CLR_RED srcColorRed;
    SEREG_SRC_CLR_GREEN srcColorGreen;
    SEREG_SRC_CLR_BLUE srcColorBlue;
    SEREG_SRC_CLR_ALPHA srcColorAlpha;    
} SE_STRETCH_EX;

// Extra Parameters for Command Alpha on Saturn. Saturn Spec page 60
//
typedef struct _SE_ALPHA_EX
{
    bool bEnbaleDfbSrcColorKey;                     // For Word1, field: fb_src_color_key
    SEINFO_ALPHA_CMD_STREAM_MODE streamType;        // For Word1, field: stream_type
    bool bSrcMaskAlpha;                             // For Word2, field: fb_src_mask_alpha
    bool bSrcMaskColor;                             // For Word2, field: fb_src_mask_color
    bool bStreamIsBigEndian;                        // For Word5, field: stream_big_endian
    bool bStreamAlphaLocationIsRightMost;           // For Word5, field: stream_alp_loc
    uint8_t alphaAddressIndex;                      // For Word5, field: Aaddr_index
    uint16_t inputAY;                               // For Word5, field: input_AY
    uint16_t inputAX;                               // For Word5, field: input_AX    
} SE_ALPHA_EX;

#endif
