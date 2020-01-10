//=================================================================================================
// Copyright (c) 2008 Realtek Semiconductor Corp. All Rights Reserved.
//
// Filename: SeReg.h
// Abstract:
//   Related Definitions of Register Set for Columbus Streaming Engine
//
// History:
//   2008-02-14         cyyang          Initial Version
//=================================================================================================

#ifndef _SE_REG_H_
#define _SE_REG_H_

//=================================================================================================
#define SEREG_BASE_ADDRESS              	0xB800C000

//=================================================================================================
typedef union _SEREG_CMDBASE
{
    uint32_t  Value;
    struct
    {    
											//Register: CMDBASE (0x1800_C000)
		uint32_t  Reserved0: 4; 			//IO[3:0]: Reserved 
        uint32_t  base: 24;                 //IO[27:4]: Command ring buffer SDRAM base address, 16B alignment
        uint32_t  Reserved1: 4;             //IO[31:28]: Reserved    
        
    } Fields;
    
} SEREG_CMDBASE;

//=================================================================================================
typedef union _SEREG_CMDLMT
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CMDLMT (0x1800_C00C)
		uint32_t  Reserved0: 4;             //IO[3:0]: Reserved   
        uint32_t  limit: 24;                //IO[27:4]: Command ring buffer limit SDRAM address, 16B alignment
        uint32_t  Reserved1: 4;             //IO[31:28]: Reserved  
        
    } Fields;
    
} SEREG_CMDLMT;

//=================================================================================================
typedef union _SEREG_CMDRPTR
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CMDRPTR (0x1800_C018)
		uint32_t  Reserved0: 4;             //IO[3:0]: Reserved 
        uint32_t  rptr: 24;                 //IO[27:4]: Command ring buffer read pointer, 16B alignment 
        uint32_t  Reserved1: 4;             //IO[31:28]: Reserved    
        
    } Fields;
    
} SEREG_CMDRPTR;

//=================================================================================================
typedef union _SEREG_CMDWPTR
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CMDWPTR (0x1800_C024)  
		uint32_t  Reserved0: 4; 			//IO[3:0]: Reserved 
        uint32_t  wptr: 24;                 //IO[27:4]: Command ring buffer write pointer, 16B alignment   
        uint32_t  Reserved1: 4;             //IO[31:28]: Reserved  
        
    } Fields;
    
} SEREG_CMDWPTR;

//=================================================================================================
typedef union _SEREG_SRWORDCNT
{
    uint32_t  Value;
    struct
    {    
                                            //Register: SRWORDCNT (0x1800_C030)
		uint32_t  srwordcnt: 7; 			//IO[6:0]: Number of 4B word inside SE command FIFO SRAM. 
											//		   This is used for debugging only. 	

        uint32_t  Reserved: 25;             //IO[31:7]: Reserved    
        
    } Fields;
    
} SEREG_SRWORDCNT;

//=================================================================================================
typedef union _SEREG_Q_PRIORITY
{
    uint32_t  Value;
    struct
    {    
                                            //Register: Q_PRIORITY (0x1800_C03C)
		uint32_t  pri1: 2;                  //IO[1:0]: Priority number of command queue1.
		uint32_t  pri2: 2;                  //IO[3:2]: Priority number of command queue2.
		uint32_t  pri3: 2;                  //IO[5:4]: Priority number of command queue3.
        uint32_t  Reserved: 26;             //IO[31:6]: Reserved    
       
    } Fields;
    
} SEREG_Q_PRIORITY;

//=================================================================================================
typedef union _SEREG_CLR_FMT
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CLR_FMT (0x1800_C040)
		uint32_t  Format: 4;				//IO[3:0]: Format
											//		   - 4・b0000: Index2
											//		   - 4・b0001: Index4
											//		   - 4・b0010: Index8
											//		   - 4・b0011: RGB332
											//		   - 4・b0100: RGB565
											//		   - 4・b0101: ARGB1555
											//		   - 4・b0110: ARGB4444
											//		   - 4・b0111: ARGB8888
											//		   - 4・b1000: Y (stretch and decimate command only)
											//		   - 4・b1001: CbCr (stretch and decimate command only)
											//		   - 4・b1010: YCbCr 420 (felics only)
											//		   - 4・b1011: YCbCr 422 (felics only)
											//		   - 4・b1100: YCbCr 444 (felics only)
											//		   - else: reserved
                                   
        uint32_t  write_enable1: 1;         //IO[4]: Write enable for IO[3:0]

		uint32_t  alpha_loc: 1; 		 	//IO[5]: Location of alpha pixel if the format is 8888, 4444, 1555 mode, this bit 
											//		 specifies whether the alpha pixel location is the leftmost (=0) or rightmost 
											//		 of a pixel

		uint32_t  write_enable2: 1; 	  	//IO[6]: Write enable for IO[5]

		uint32_t  clr_loc2: 2;				//IO[8:7]: Specify the output location of 2/6-bit color component within the 332/565 
											//		   formats in format conversion.
											//		   - 2・b00: leftmost
											//		   - 2・b01: middle
											//		   - 2・b10: rightmost
											//		   - else:reserved
											//			
											//		   - Note: For 332, the value must be 2・b10. For 565, the value must be 2・b01. 
											//				   Other values are not well verified.

		uint32_t  write_enable3: 1; 	  	//IO[9]: Write enable for IO[8:7]

		uint32_t  clr_loc1: 2;				//IO[11:10]: Specify the location of 2/6-bit color component within the 332/565 formats.
											//			 - 2・b00: leftmost
											//			 - 2・b01: middle
											//			 - 2・b10: rightmost
											//			 - else:reserved
											//		  
											//			 - Note: For 332, the value must be 2・b10. For 565, the value must be 2・b01. 
											//					 Other values are not well verified. 
	
		uint32_t  write_enable4: 1; 	  	//IO[12]: Write enable for IO[11:10]
	
		uint32_t  alpha_loc2: 1;		 	//IO[13]: Specify the output alpha location in format conversion ARGB to ARGB mode.
		uint32_t  write_enable5: 1; 	 	//IO[14]: Write enable for IO[13]
		uint32_t  Reserved: 17; 		  	//IO[31:15]: Reserved    

    } Fields;
    
} SEREG_CLR_FMT;

//=================================================================================================
typedef union _SEREG_COLOR_KEY
{
    uint32_t  Value;
    struct
    {    
                                            //Register: COLOR_KEY (0x1800_C04C)
        uint32_t  color_key: 24;            //IO[23:0]: color key in variable color formats. 
                                            //          - Index2: use color_key[1:0] as color_key
                                            //          - Index4: use color_key[3:0] as color_key
                                            //          - Index8: use color_key[7:0] as color_key
                                            //          - RGB332: use color_key[7:0] as color_key
                                            //          - RGB565: use color_key[15:0] as color_key
                                            //          - ARGB1555: use color_key[14:0] as color_key
                                            //          - ARGB4444: use color_key[11:0] as color_key
                                            //          - ARGB8888: use color_key[23:0] as color_key

        uint32_t  Reserved: 8;              //IO[31:24]: Reserved    

    } Fields;
    
} SEREG_COLOR_KEY;

//=================================================================================================
typedef union _SEREG_SRC_COLOR
{
    uint32_t  Value;
    struct
    {    
                                            //Register: SRC_COLOR (0x1800_C058)
        uint32_t  src_color: 24;            //IO[23:0]: constant source color in variable color formats.
                                            //          - Index2: use src_color[1:0]
                                            //          - Index4: use src_color[3:0]
                                            //          - Index8: use src_color[7:0]
                                            //          - RGB332: use src_color[7:0]
                                            //          - RGB565: use src_color[15:0]
                                            //          - ARGB1555: use src_color[14:0]
                                            //          - ARGB4444: use src_color[11:0]
                                            //          - ARGB8888: use src_color[23:0]
                                            
        uint32_t  Reserved: 8;              //IO[31:24]: Reserved    

    } Fields;
    
} SEREG_SRC_COLOR;

//=================================================================================================
typedef union _SEREG_SRC_COLOR2
{
    uint32_t  Value;
    struct
    {    
                                            //Register: SRC_COLOR2 (0x1800_C064)
        uint32_t  src_color2: 24;           //IO[23:0]: constant source color2 used in the gradient operation, 
                                            //          in variable color formats.
                                            //          - RGB332: use src_color[7:0]
                                            //          - RGB565: use src_color[15:0]
                                            //          - ARGB1555: use src_color[14:0]
                                            //          - ARGB4444: use src_color[11:0]
                                            //          - ARGB8888: use src_color[23:0]
                                            
        uint32_t  Reserved: 8;              //IO[31:24]: Reserved    

    } Fields;
    
} SEREG_SRC_COLOR2;

//=================================================================================================
typedef union _SEREG_SRC_ALPHA
{
    uint32_t  Value;
    struct
    {    
                                            //Register: SRC_ALPHA (0x1800_C070)
        uint32_t  src_alpha: 8;             //IO[7:0]: constant source alpha; 
                                            //         if 4444, use the LSB [3:0]; if 1555, use the LSB [0]
                                            
        uint32_t  Reserved: 24;             //IO[31:8]: Reserved    

    } Fields;
    
} SEREG_SRC_ALPHA;

//=================================================================================================
typedef union _SEREG_SRC_ALPHA2
{
    uint32_t  Value;
    struct
    {    
                                            //Register: SRC_ALPHA2 (0x1800_C4D0)
        uint32_t  src_alpha2: 8;            //IO[7:0]: constant source alpha2 used in the gradient operation; 
                                            //         if 4444, use the LSB [3:0]; if 1555, use the LSB [0]
                                            
        uint32_t  Reserved: 24;             //IO[31:8]: Reserved    

    } Fields;
    
} SEREG_SRC_ALPHA2;

//=================================================================================================
typedef union _SEREG_DEST_ALPHA
{
    uint32_t  Value;
    struct
    {    
                                            //Register: DEST_ALPHA (0x1800_C07C)
        uint32_t  dest_alpha: 8;           	//IO[7:0]: constant dest alpha; used for dest-alpha calculation by select_dest_alpha; 
                                            //         if 4444, use the LSB [3:0]; if 1555, use the LSB [0]. 

		uint32_t  Reserved: 24; 			//IO[31:8]: Reserved	  

    } Fields;
    
} SEREG_DEST_ALPHA;

//=================================================================================================
typedef union _SEREG_RSLT_ALPHA
{
    uint32_t  Value;
    struct
    {    
                                            //Register: RSLT_ALPHA (0x1800_C088)
        uint32_t  rslt_alpha: 8;            //IO[7:0]: constant result alpha, to overwrite the alpha results after operation. 
                                            //         if 4444, use the LSB [3:0]; if 1555, use the LSB [0].
                                            
		uint32_t  Reserved: 24; 			//IO[31:8]: Reserved	  

    } Fields;
    
} SEREG_RSLT_ALPHA;

//=================================================================================================
typedef union _SEREG_BADDR
{
    uint32_t  Value;
    struct
    {    
                                            //Register: BADDR1 (0x1800_C094)
        uint32_t  baddr: 28;                //IO[27:0]: Base address of a SE address set; 16B-align
		uint32_t  Reserved: 4;				//IO[31:28]: Reserved    

    } Fields;
    
} SEREG_BADDR;

//=================================================================================================
typedef union _SEREG_PITCH
{
    uint32_t  Value;
    struct
    {    
                                            //Register: PITCH1 (0x1800_C0A4)
        uint32_t  pitch: 14;                //IO[13:0]: Pitch of a SE address set, unit in byte. 0 means 16384 bytes. 16B-align.
        uint32_t  interleave: 1;            //IO[14]: interleaving mode for the picture index.
        uint32_t  Reserved: 17;             //IO[31:15]: Reserved    

    } Fields;
    
} SEREG_PITCH;

typedef struct _SEREG_DMAINFO
{
	SEREG_BADDR		SeRegBaseAddress[4];
	SEREG_PITCH		SeRegPitch[4];
	
} SEREG_DMAINFO;

//=================================================================================================
typedef union _SEREG_FADDR
{
    uint32_t  Value;
    struct
    {    
                                            //Register: FADDR1 (0x1800_C0F4)
        uint32_t  faddr: 28;                //IO[27:0]: Base address of a SE Felics bitstream address set, 
                                            //          for Queue 1; 8B-align. The bitstream include header, 
                                            //          both compression and decompression.
                                            
        uint32_t  Reserved: 4;              //IO[31:28]: Reserved    

    } Fields;
    
} SEREG_FADDR;

//=================================================================================================
typedef union _SEREG_BSTLEN
{
    uint32_t  Value;
    struct
    {    
                                            //Register: BSTLEN (0x1800_C124)
        uint32_t  bstlen: 1;                //IO[0]: This register is useless now. The burst length 
                                            //       is always 256B (actually, 240B in current implementation)

        uint32_t  pkgen: 1;                 //IO[1]: pkgen
                                            //       - 1: Enable small request package function.
                                            //       - 0: Disable
                                                                                        
        uint32_t  Reserved: 30;             //IO[31:2]: Reserved    

    } Fields;
    
} SEREG_BSTLEN;

//=================================================================================================
typedef union _SEREG_CLIP_XCOOR
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CLIP_XCOOR1 (0x1800_C128)
        uint32_t  xmax: 12;                 //IO[11:0]: Max X coordinate for clipping; When YC422/420, 
                                            //          this value should be an odd number.

        uint32_t  xmin: 12;                 //IO[23:12]: Min X coordinate for clipping; When YC422/420, 
                                            //           this value should be an even number.
                                            
        uint32_t  clipen: 1;                //IO[24]: Enable clipping function
        	
        uint32_t  Reserved: 7;              //IO[31:25]: Reserved  

    } Fields;
    
} SEREG_CLIP_XCOOR;

//=================================================================================================
typedef union _SEREG_CLIP_YCOOR
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CLIP_YCOOR1 (0x1800_C138)
        uint32_t  ymax: 12;                 //IO[11:0]: Max Y coordinate for clipping; When YC420, 
                                            //          this value should be an odd number.

        uint32_t  ymin: 12;                 //IO[23:12]: Min Y coordinate for clipping; When YC420, 
                                            //           this value should be an even number.
        
        uint32_t  clipen: 1;                //IO[24]: Enable clipping function 
        	                                    
        uint32_t  Reserved: 7;              //IO[31:25]: Reserved  

    } Fields;
    
} SEREG_CLIP_YCOOR;

//=================================================================================================
typedef struct _SEREG_CLIP_INFO
{
	SEREG_CLIP_XCOOR	SeRegClipXCoor[4];
	SEREG_CLIP_YCOOR	SeRegClipYCoor[4];

} SEREG_CLIP_INFO;

//=================================================================================================
typedef union _SEREG_CONVSCALING
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CONVSCALING (0x1800_C188)
        uint32_t  vup: 1;                   //IO[0]: Vertical interpolation when 420 to 444
                                            //       - 0: repeat
                                            //       - 1: [1 1]/2

        uint32_t  hup: 1;                   //IO[1]: Horizontal interpolation when 422/420 to 444
                                            //       - 0: repeat
                                            //       - 1: [1 1]/2

        uint32_t  vdown: 1;                 //IO[2]: Vertical decimation when 444 to 420
                                            //       - 0: drop
                                            //       - 1: [1 1]/2

        uint32_t  hdown: 1;                 //IO[3]: Horizontal decimation when 444 to 422/420
                                            //       - 0: drop
                                            //       - 1: [1 1]/2

        uint32_t  Reserved: 28;             //IO[31:4]: Reserved  
     
    } Fields;
    
} SEREG_CONVSCALING;

//=================================================================================================
typedef union _SEREG_CONVCOEF1
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CONVCOEF1 (0x1800_C194)
        uint32_t  m00: 12;                  //IO[11:0]: Coefficient with format (sign,1,10)
        uint32_t  m01: 12;                  //IO[23:12]: Coefficient with format (sign,1,10)
        uint32_t  Reserved: 8;              //IO[31:24]: Reserved  

    } Fields;
    
} SEREG_CONVCOEF1;

//=================================================================================================
typedef union _SEREG_CONVCOEF2
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CONVCOEF2 (0x1800_C1A0)
        uint32_t  m02: 12;                  //IO[11:0]: Coefficient with format (sign,1,10)
        uint32_t  m10: 12;                  //IO[23:12]: Coefficient with format (sign,1,10) 
        uint32_t  Reserved: 8;              //IO[31:24]: Reserved  

    } Fields;
    
} SEREG_CONVCOEF2;

//=================================================================================================
typedef union _SEREG_CONVCOEF3
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CONVCOEF3 (0x1800_C1AC)
        uint32_t  m11: 12;                  //IO[11:0]: Coefficient with format (sign,1,10)
        uint32_t  m12: 12;                  //IO[23:12]: Coefficient with format (sign,1,10)
        uint32_t  Reserved: 8;              //IO[31:24]: Reserved  
         
        

    } Fields;
    
} SEREG_CONVCOEF3;

//=================================================================================================
typedef union _SEREG_CONVCOEF4
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CONVCOEF4 (0x1800_C1B8)
        uint32_t  m20: 12;                  //IO[11:0]: Coefficient with format (sign,1,10)
        uint32_t  m21: 12;                  //IO[23:12]: Coefficient with format (sign,1,10)
        uint32_t  Reserved: 8;              //IO[31:24]: Reserved  

    } Fields;
    
} SEREG_CONVCOEF4;

//=================================================================================================
typedef union _SEREG_CONVCOEF5
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CONVCOEF5 (0x1800_C1C4)
        uint32_t  m22: 12;                  //IO[11:0]: Coefficient with format (sign,1,10) 
        uint32_t  Reserved: 20;             //IO[31:12]: Reserved  

    } Fields;
    
} SEREG_CONVCOEF5;

//=================================================================================================
typedef union _SEREG_CONVCOEF6
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CONVCOEF1 (0x1800_C1D0)
        uint32_t  a0: 9;                    //IO[8:0]: Coefficient with format of (sign,8)
        uint32_t  a1: 9;                    //IO[17:9]: Coefficient with format of (sign,8)
        uint32_t  a2: 9;                    //IO[26:18]: Coefficient with format of (sign,8)
        uint32_t  Reserved: 5;              //IO[31:27]: Reserved  
  
    } Fields;
    
} SEREG_CONVCOEF6;

//=================================================================================================
typedef union _SEREG_STRETCH
{
    uint32_t  Value;
    struct
    {    
                                            //Register: STRETCH (0x1800_C1DC)
        uint32_t  vodd: 1;                  //IO[0]: This bit is only used when apply FIR algorithm.
                                            //       - 1: Using odd type FIR for V-scaling. 
                                            //       - 0: Using even type FIR for V-scaling.
        
        uint32_t  hodd: 1;                  //IO[1]: This bit is only used when apply FIR algorithm.
                                            //       - 1: Using odd type FIR for H-scaling. 
                                            //       - 0: Using even type FIR for H-scaling. 

        uint32_t  vtype: 1;                 //IO[2]: vtype
                                            //       - 0: 2-tap FIR 
                                            //       - 1: 4-tap FIR

        uint32_t  htype: 2;                 //IO[4:3]: htype
                                            //         - 00: 2-tap FIR 
                                            //         - 01: 4-tap FIR
                                            //         - 10: 8-tap FIR

		uint32_t  ref_alpha: 1;             //IO[5]: Reference alpha option for transparency function

		uint32_t  ds_thx: 9;                //IO[14:6]: Directional scaling threshold.

        uint32_t  Reserved: 17;             //IO[31:15]: Reserved  

    } Fields;
    
} SEREG_STRETCH;

//=================================================================================================
typedef union _SEREG_HDHS
{
    uint32_t  Value;
    struct
    {    
                                            //Register: HDHS (0x1800_C1E8)
		uint32_t  H_scaling_dph_lsb: 14;    //IO[13:0]: LSB of the H-scaling delta-phase in (3,14) format
		uint32_t  H_scaling_dph_msb: 3;     //IO[16:14]: MSB of the H-scaling delta-phase in (3,14) format
		uint32_t  H_scaling_iniph: 3;       //IO[19:17]: Initial phase of Y coordinate for H-scaling
        uint32_t  Reserved: 12;             //IO[31:20]: Reserved  

    } Fields;
    
} SEREG_HDHS;

//=================================================================================================
typedef union _SEREG_VDHS
{
    uint32_t  Value;
    struct
    {    
                                            //Register: VDHS (0x1800_C1F4)
        uint32_t  V_scaling_dph_lsb: 14;    //IO[13:0]: LSB of the V-scaling delta-phase in (3,14) format
        uint32_t  V_scaling_dph_msb: 3;     //IO[16:14]: MSB of the V-scaling delta-phase in (3,14) format
        uint32_t  V_scaling_iniph: 3;       //IO[19:17]: Initial phase of Y coordinate for V-scaling
        uint32_t  Reserved: 12;             //IO[31:20]: Reserved  
   
    } Fields;
    
} SEREG_VDHS;

//=================================================================================================
typedef union _SEREG_HCOEF
{
    uint32_t  Value;
    struct
    {    
                                            //Register: HCOEF1 (0x1800_C200)
        uint32_t  hcoef: 14;                //IO[13:0]: Coefficient in (sign, 1, 12) format (2・s complement)
        uint32_t  Reserved: 18;             //IO[31:14]: Reserved  

    } Fields;
    
} SEREG_HCOEF;

//=================================================================================================
typedef union _SEREG_VCOEF
{
    uint32_t  Value;
    struct
    {    
                                            //Register: VCOEF1 (0x1800_C280)
        uint32_t  vcoef: 14;                //IO[13:0]: Coefficient in (sign, 1, 12) format (2・s complement)
        uint32_t  Reserved: 18;             //IO[31:14]: Reserved  

    } Fields;
    
} SEREG_VCOEF;

typedef struct _SEREG_COEFINFO
{
	SEREG_HCOEF		SeRegHCoef[32];
	SEREG_VCOEF		SeRegVCoef[16];
	
} SEREG_COEFINFO;

//=================================================================================================
typedef union _SEREG_2TO4_MAP
{
    uint32_t  Value;
    struct
    {    
                                            //Register: 2TO4_MAP (0x1800_C440)
        uint32_t  map: 16;                  //IO[15:0]: 2 to 4 bit mapping table for DVB. Entry 0 is map[15:12].
        uint32_t  Reserved: 16;             //IO[31:16]: Reserved  

    } Fields;
    
} SEREG_2TO4_MAP;

//=================================================================================================
typedef union _SEREG_2TO8_MAP
{
    uint32_t  Value;
    struct
    {    
                                            //Register: 2TO8_MAP (0x1800_C444)
        uint32_t  map;                      //IO[31:0]: 2 to 8 bit mapping table for DVB. Entry 0 is map[31:24]

    } Fields;
    
} SEREG_2TO8_MAP;

//=================================================================================================
typedef union _SEREG_4TO8_MAP
{
    uint32_t  Value;
    struct
    {    
                                            //Register: 4TO8_MAP (0x1800_C4C0)
        uint32_t  map;                      //IO[31:0]: 4 to 8 bit mapping table for DVB. Entry 0 is STD_4TO8_MAP[0][31:24].

    } Fields;
    
} SEREG_4TO8_MAP;

//=================================================================================================
typedef union _SEREG_FELICS_ABORT
{
    uint32_t  Value;
    struct
    {    
                                            //Register: FELICS_ABORT (0x1800_C44C)
        uint32_t  threshold: 27;            //IO[26:0]: If bit length of any one component >= threshold and en == 1, 
                                            //          the compression process will abort.
        uint32_t  Enable: 1;                //IO[27]: Enable the abort mechanism
        uint32_t  Reserved: 4;              //IO[31:28]: Reserved  

    } Fields;
    
} SEREG_FELICS_ABORT;

//=================================================================================================
typedef union _SEREG_CTRL
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CTRL (0x1800_C458)
        uint32_t  write_data: 1;            //IO[0]: write_data
        
        uint32_t  go: 1;                    //IO[1]: SE operation of the command queue can only start when go = 1. 
                                            //       Once it starts the command queue will only stop when this bit is 
                                            //       set to 0 and when it completes the current instruction
        
        uint32_t  endiswap: 1;              //IO[2]: When this bit is == 1, the command endianness will be swapped. 
                                            //       It will change the byte order to {cmd[7:0],cmd[15:8], cmd[23:16], cmd[31:24]}
                                            	
        uint32_t  Reserved: 29;             //IO[31:3]: Reserved  

    } Fields;
    
} SEREG_CTRL;

//=================================================================================================
typedef union _SEREG_IDLE
{
    uint32_t  Value;
    struct
    {    
                                            //Register: IDLE (0x1800_C464)
        uint32_t  idle: 1;                  //IO[0]: indicate the command queue of SE is idle (all instruction has been 
                                            //       executed and in both the internal and external command list, or when 
                                            //       go bit = 0 and the command queue of SE is stopped.

        uint32_t  Reserved: 31;             //IO[31:1]: Reserved  
                                      
    } Fields;
    
} SEREG_IDLE;

//=================================================================================================
typedef union _SEREG_INTSEL
{
    uint32_t  Value;
    struct
    {    
                                            //Register: INTSEL (0x1800_C470)
        uint32_t  Sel1: 1;                  //IO[0]: Select which CPU to interrupt for command queue 1: 
                                            //       - 0: SCPU
                                            //       - 1: VCPU 

        uint32_t  Sel2: 1;                  //IO[1]: Select which CPU to interrupt for command queue 2: 
                                            //       - 0: SCPU
                                            //       - 1: VCPU

        uint32_t  Sel3: 1;                  //IO[2]: Select which CPU to interrupt for command queue 3: 
                                            //       - 0: SCPU
                                            //       - 1: VCPU

        uint32_t  Reserved: 28;             //IO[31:3]: Reserved  
                                
    } Fields;
    
} SEREG_INTSEL;

//=================================================================================================
typedef union _SEREG_INTS
{
    uint32_t  Value;
    struct
    {    
                                            //Register: INTS (0x1800_C474)
		uint32_t  write_data: 1;            //IO[0]: write_data
		uint32_t  sync: 1;                  //IO[1]: Interrupt enable of sync interrupt 	
		uint32_t  com_err: 1;               //IO[2]: Interrupt enable of command decoding error. The command will be ignored.
		uint32_t  com_empty: 1;             //IO[3]: Interrupt enable. SDRAM and internal command lists both empty, 
											//		 and the execution of all commands is done.
		uint32_t  dvb_err_t: 1;             //IO[4]: DVB data type is not defined 
		uint32_t  dvb_err_s: 1;             //IO[5]: DVB stuff_bits is non-zero.
		uint32_t  dvb_err_m: 1;             //IO[6]: DVB insufficient data for map-table. 
		uint32_t  dvb_err_e: 1;             //IO[7]: DVB insufficient data for decode. 
		uint32_t  bdrle_rlerr: 1;           //IO[8]: BD run_length code error 
		uint32_t  bdrle_long_h: 1;          //IO[9]: decoded ling number is larger than object height 
		uint32_t  bdrle_long_w: 1;          //IO[10]: decoded line length is larger than object width 	
		uint32_t  bdrle_isbl: 1;            //IO[11]: bitstreamend and the symbol is incomplete or not end_of_line_signal 	
		uint32_t  Felics_err: 1;            //IO[12]: error symbol; the unary run exceed 63	
		uint32_t  Felics_long: 1;           //IO[13]: extra bitstream 
		uint32_t  Felics_short: 1;          //IO[14]: incomplete bitstream; the bitstream run out before a complete 
											//		  object is decompressed.
		uint32_t  Felics_range: 1;          //IO[15]: The decoded value is out of the valid range 
		uint32_t  Reserved: 16;             //IO[31:16]: Reserved  
	
    } Fields;   
                
} SEREG_INTS;   

//=================================================================================================
typedef union _SEREG_INTE
{
    uint32_t  Value;
    struct
    {    
                                            //Register: INTE (0x1800_C480)
		uint32_t  write_data: 1;            //IO[0]: write_data
		uint32_t  sync: 1;                  //IO[1]: Interrupt enable of sync interrupt 
		uint32_t  com_err: 1;               //IO[2]: Interrupt enable of command decoding error. The command will be ignored.
		uint32_t  com_empty: 1;             //IO[3]: Interrupt enable. SDRAM and internal command lists both empty, 
											//		 and the execution of all commands is done.
		uint32_t  dvb_err_t: 1;             //IO[4]: DVB data type is not defined
		uint32_t  dvb_err_s: 1;             //IO[5]: DVB stuff_bits is non-zero. 
		uint32_t  dvb_err_m: 1;             //IO[6]: DVB insufficient data for map-table.  
		uint32_t  dvb_err_e: 1;             //IO[7]: DVB insufficient data for decode.
		uint32_t  bdrle_rlerr: 1;           //IO[8]: BD run_length code error 
		uint32_t  bdrle_long_h: 1;          //IO[9]: decoded ling number is larger than object height	
		uint32_t  bdrle_long_w: 1;          //IO[10]: decoded line length is larger than object width
		uint32_t  bdrle_isbl: 1;            //IO[11]: bitstreamend and the symbol is incomplete or not end_of_line_signal 
		uint32_t  Felics_err: 1;            //IO[12]: error symbol; the unary run exceed 63
		uint32_t  Felics_long: 1;           //IO[13]: extra bitstream
		uint32_t  Felics_short: 1;          //IO[14]: incomplete bitstream; the bitstream run out before a complete object is decompressed.
		uint32_t  Felics_range: 1;      	//IO[15]: The decoded value is out of the valid range
		uint32_t  Reserved: 16;             //IO[31:16]: Reserved  
                                             
    } Fields;   
                
} SEREG_INTE; 
 
//=================================================================================================
typedef union _SEREG_INSTCNT
{
    uint32_t  Value;
    struct
    {    
                                            //Register: INSTCNT (0x1800_C48C)
        uint32_t  instcnt: 16;              //IO[15:0]: number of commands encountered.  This field will increment by 1 
                                            //          whenever an command is completed execution. It will wrap to 0 after 16・hffff.
        
        uint32_t  Reserved: 16;             //IO[31:16]: Reserved  
                                    
    } Fields;
    
} SEREG_INSTCNT; 

//=================================================================================================
typedef union _SEREG_CLUT_RADR
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CLUT_RADR (0x1800_C498)
        uint32_t  radr: 8;                  //IO[7:0]: CLUT SRAM read address. 
        uint32_t  Reserved: 24;             //IO[31:8]: Reserved  
                                  
    } Fields;
    
} SEREG_CLUT_RADR; 
 
//=================================================================================================
typedef union _SEREG_CLUT_VALUE
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CLUT_VALUE (0x1800_C49C)
        uint32_t  value;                    //IO[31:0]: The 32b content inside the CLUT SRAM addressed by SE_CLUT_RADR.
        
    } Fields;
    
} SEREG_CLUT_VALUE;  

//=================================================================================================
typedef union _SEREG_DBG
{
    uint32_t  Value;
    struct
    {    
                                            //Register: CLUT_RADR (0x1800_C4A0)
        uint32_t  dbg_en: 1;                //IO[0]: Debug enable
                                            //       - When set, selected signals can be probed via debug ports. 
                                            //       - When clear, both se_dbg_out0 and se_dbg_out1 are static 16・h0.

        uint32_t  dbg_sel0: 3;              //IO[3:1]: Select debug signal sets to be probed via se_dbg_out0
        uint32_t  dbg_sel1: 3;              //IO[6:4]: Select debug signal sets to be probed via se_dbg_out1
        uint32_t  Reserved: 25;             //IO[31:7]: Reserved  
                   
    } Fields;
    
} SEREG_DBG; 

//=================================================================================================
typedef union _SEREG_SCTCH
{
    uint32_t  Value;
    struct
    {    
                                            //Register: SCTCH (0x1800_C4A4)
        uint32_t  Reg0: 16;                 //IO[15:0]: Dummy registers with default value 0 
        uint32_t  Reg1: 16;                 //IO[31:16]: Dummy registers with default value 1
              
    } Fields;
    
} SEREG_SCTCH; 

//=================================================================================================
typedef union _SEREG_GCRA_CTRL
{
    uint32_t  Value;
    struct
    {    
                                            //Register: GCRA_CTRL (0x1800_C4A8)
        uint32_t  Gcra_en: 1;               //IO[0]: SE request GCRA algorithm enable
        uint32_t  Reserved: 31;             //IO[31:1]: Reserved
                    
    } Fields;
    
} SEREG_GCRA_CTRL; 

//=================================================================================================
typedef union _SEREG_GCRA_REQ_CNT
{
    uint32_t  Value;
    struct
    {    
                                            //Register: GCRA_REQ_CNT (0x1800_C4AC)
        uint32_t  Gcra_req_num: 24;         //IO[23:0]: Request number for current period.
        uint32_t  Reserved: 8;              //IO[31:24]: Reserved
                        
    } Fields;
    
} SEREG_GCRA_REQ_CNT; 

//=================================================================================================
typedef union _SEREG_GCRA_TIM_CNT
{
    uint32_t  Value;
    struct
    {    
                                            //Register: GCRA_TIM_CNT (0x1800_C4B0)
        uint32_t  Gcra_tim_cnt;             //IO[31:0]: Timer counter
                        
    } Fields;
    
} SEREG_GCRA_TIM_CNT; 

//=================================================================================================
typedef union _SEREG_GCRA_TIM_THR
{
    uint32_t  Value;
    struct
    {    
                                            //Register: GCRA_TIM_THR (0x1800_C4B4)
        uint32_t  Gcra_tim_thr;             //IO[31:0]: Timer counter threshold. When timer reach this threshold, 
                                            //          HW will clear timer counter and request number
                        
    } Fields;
    
} SEREG_GCRA_TIM_THR; 

//=================================================================================================
typedef union _SEREG_GCRA_REQ_THR
{
    uint32_t  Value;
    struct
    {    
                                            //Register: GCRA_REQ_THR (0x1800_C4B8)
        uint32_t  Gcra_req_thr: 24;         //IO[23:0]: Request number threshold. When SE request number reach this 
                                            //          threshold, HW will stop to access.
        uint32_t  Reserved: 8;              //IO[31:24]: Reserved
                       
    } Fields;
    
} SEREG_GCRA_REQ_THR; 

//=================================================================================================
typedef union _SEREG_DC1SPACE
{
    uint32_t  Value;
    struct
    {    
                                            //Register: DC1SPACE (0x1800_C4BC)
        uint32_t  dc1_space_ctrl: 2;        //IO[1:0]: DC1 memory size control.
                                            //         This is used for DC1 and DC2 memory map partition. 
                                            //         The field specifies the DC1 DRAM space. DC2 space begins at the address above this area.
                                            //         - 2・h0: 32MBytes. Indicating DC1 address space ranges from 0x0 to 0x1FFFF, while DC1 space start from 0x20000.
                                            //         - 2・h1: 64MByte. 
                                            //         - 2・h2: 128MByte.
                                            //         - 2・h3: Reserved.
        uint32_t  Reserved: 30;             //IO[31:2]: Reserved

    } Fields;
    
} SEREG_DC1SPACE; 

//=================================================================================================
typedef struct _SEREG_INFO
{               
    SEREG_CMDBASE           SeCmdBase[3];           //0x1800_C000: Register: CMDBASE
    SEREG_CMDLMT            SeCmdLimit[3];          //0x1800_C00C: Register: SEREG_CMDLMT
    SEREG_CMDRPTR           SeCmdReadPtr[3];        //0x1800_C018: Register: CMDRPTR
    SEREG_CMDWPTR           SeCmdWritePtr[3];       //0x1800_C024: Register: CMDWPTR
    SEREG_SRWORDCNT         SeSramWordCount[3];     //0x1800_C030: Register: SRWORDCNT
    SEREG_Q_PRIORITY        SeQueuePriority;        //0x1800_C03C: Register: Q_PRIORITY
    
    SEREG_CLR_FMT           SeColorFormat[3];       //0x1800_C040: Register: CLR_FMT
    SEREG_COLOR_KEY         SeColorKey[3];          //0x1800_C04C: Register: COLOR_KEY
    SEREG_SRC_COLOR         SeSrcColor[3];          //0x1800_C058: Register: SRC_COLOR
    SEREG_SRC_COLOR2        SeSrcColor2[3];         //0x1800_C064: Register: SRC_COLOR2
    SEREG_SRC_ALPHA         SeSrcAlpha[3];          //0x1800_C070: Register: SRC_ALPHA
    SEREG_DEST_ALPHA        SeDestAlpha[3];         //0x1800_C07C: Register: DEST_ALPHA
    SEREG_RSLT_ALPHA        SeResultAlpha[3];       //0x1800_C088: Register: RSLT_ALPHA
    
    SEREG_DMAINFO			SeDmaInfo[3];			//0x1800_C094 - 0x1800_C0F0
    SEREG_FADDR            	SeFelicsAddr[3][4];     //0x1800_C0F4: Register: FADDR1
    SEREG_BSTLEN            SeDmaBurstLength;       //0x1800_C124: Register: BSTLEN 
    
    SEREG_CLIP_INFO        	SeClipInfo[3];      	//0x1800_C128 - 0x1800_C184

    SEREG_CONVSCALING       SeConvScaling[3];       //0x1800_C188: Register: CONVSCALING
    SEREG_CONVCOEF1         SeConvCoef1[3];         //0x1800_C194: Register: CONVCOEF1
    SEREG_CONVCOEF2         SeConvCoef2[3];         //0x1800_C1A0: Register: CONVCOEF2
    SEREG_CONVCOEF3         SeConvCoef3[3];         //0x1800_C1AC: Register: CONVCOEF3
    SEREG_CONVCOEF4         SeConvCoef4[3];         //0x1800_C1B8: Register: CONVCOEF4
    SEREG_CONVCOEF5         SeConvCoef5[3];         //0x1800_C1C4: Register: CONVCOEF5
    SEREG_CONVCOEF6         SeConvCoef6[3];         //0x1800_C1D0: Register: CONVCOEF6

    SEREG_STRETCH           SeStretch[3];           //0x1800_C1DC: Register: STRETCH
    SEREG_HDHS              SeHdhs[3];              //0x1800_C1E8: Register: HDHS
    SEREG_VDHS              SeVdhs[3];              //0x1800_C1F4: Register: VDHS
    SEREG_COEFINFO          SeCoefInfo[3];          //0x1800_C200 - 0x1800_C43C

    SEREG_2TO4_MAP          Se2To4Map;              //0x1800_C440: Register: 2TO4_MAP
    SEREG_2TO8_MAP          Se2To8Map;              //0x1800_C444: Register: 2TO8_MAP
    
    uint32_t                Reserved;               //0x1800_C448: Reserved
    
    SEREG_FELICS_ABORT      SeFelicsAbort[3];       //0x1800_C44C: Register: FELICS_ABORT
    
    SEREG_CTRL              SeCtrl[3];              //0x1800_C458: Register: CTRL
    SEREG_IDLE              SeIdle[3];              //0x1800_C464: Register: IDLE

    SEREG_INTSEL            SeIntSel;               //0x1800_C470: Register: INTSEL
    SEREG_INTS              SeInts[3];              //0x1800_C474: Register: INTS
    SEREG_INTE              SeInte[3];              //0x1800_C480: Register: INTE
    SEREG_INSTCNT           SeInstCnt[3];           //0x1800_C48C: Register: INSTCNT

    SEREG_CLUT_RADR         SeClutReadAddress;      //0x1800_C498: Register: CLUT_RADR
    SEREG_CLUT_VALUE        SeClutValue;            //0x1800_C49C: Register: CLUT_VALUE
    SEREG_DBG               SeDebug;                //0x1800_C4A0: Register: DBG
    SEREG_SCTCH             SeSctch;                //0x1800_C4A4: Register: SCTCH  
    
    SEREG_GCRA_CTRL         SeGcraCtrl;             //0x1800_C4A8: Register: GCRA_CTRL
    SEREG_GCRA_REQ_CNT      SeGcraReqCnt;           //0x1800_C4AC: Register: GCRA_REQ_CNT
    SEREG_GCRA_TIM_CNT      SeGcraTimCnt;           //0x1800_C4B0: Register: GCRA_TIM_CNT
    SEREG_GCRA_TIM_THR      SeGcraTimThr;           //0x1800_C4B4: Register: GCRA_TIM_THR
    SEREG_GCRA_REQ_THR      SeGcraReqThr;           //0x1800_C4B8: Register: GCRA_REQ_THR
    SEREG_DC1SPACE          SeDc1Space;             //0x1800_C4BC: Register: DC1SPACE
    
    SEREG_4TO8_MAP          Se4To8Map[4];           //0x1800_C4C0: Register: 4TO8_MAP
    SEREG_SRC_ALPHA2        SeSrcAlpha2[3];         //0x1800_C4D0: Register: SRC_ALPHA2
    
} SEREG_INFO;

//=================================================================================================

#endif

//=================================================================================================
// End of File
