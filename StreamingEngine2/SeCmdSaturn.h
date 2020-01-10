//=================================================================================================
// Copyright (c) 2008 Realtek Semiconductor Corp. All Rights Reserved.
//
// Filename: SeCmd.h
// Abstract:
//   Related Command Definitions of Columbus Streaming Engine
//
// History:
//   2008-02-15         cyyang          Initial Version
//   2011-01-18         zack            Modify for Saturn
//=================================================================================================

#ifndef _SE_CMD_H_
#define _SE_CMD_H_

//=================================================================================================
typedef struct _SECMD_WRITE_REGISTER
{
												//Command Type: Write Register
    struct                                  	
    {                                       	
        uint32_t	OpCode: 4;					//IO[3:0]: Operational Code
        										//		   - 0x01: Write Register
        uint32_t	RegisterAddress: 12;		//IO[15:4]: Register Address
        uint32_t	Clut: 1;                 	//IO[16]: Select to write registers or the CLUT
												//		  - 0: register
												//		  - 1: CLUT        
        uint32_t	Reserved: 15;               //IO[31:17]: Reserved
                                            	
    } Word1;                                	
                                            	
    struct                                  	
    {                                       	
        uint32_t	RegisterValue;				//IO[31:0]: Register Value
                                            	
    } Word2;                                	
#if 1
	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word3;  

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word4; 

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word5; 

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word6; 

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word7; 

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word8; 
#endif
                                            	
} SECMD_WRITE_REGISTER;                     	
                                            	
typedef struct _SECMD_FETCH_CLUT            	
{                                           	
												//Command Type: Fetch CLUT
    struct                                  	
    {                                       	
        uint32_t	OpCode: 4;					//IO[3:0]: Operational Code
        										//		   - 0x02: Fetch Color Look Up Table Operation
        										
        uint32_t	FetchEntry: 2;				//IO[5:4]: Fetch CLUT Mode
        										//		   - 00: 4 entries ARGB=16B (Index2)
        										//		   - 01: 16 entries ARGB=64B (Index4)
        										//		   - 10: 256 entries ARGB=1KB (Index8)
        										//		   - 11: reserved
                                            	
		uint32_t	Force_load_clut: 1;			//IO[6]: Load clut table anyway

        uint32_t	Reserved: 25;               //IO[31:7]: Reserved
                                            	
    } Word1;                                	
                                            	
    struct                                  	
    {                                       	
        uint32_t	StartingAddress: 31;		//IO[30:0]: starting address (byte address); in byte alignment
        uint32_t	Reserved: 1;               	//IO[31:31]: Reserved
                                            	
    } Word2;                                	

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word3;  

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word4; 

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word5; 

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word6; 

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word7; 

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word8; 
                                            	
} SECMD_FETCH_CLUT;                         	

typedef struct _SECMD_LOCK_CLUT            	
{                                           	
												//Command Type: Lock CLUT
    struct                                  	
    {                                       	
        uint32_t	OpCode: 4;					//IO[3:0]: Operational Code
        										//		   - 0x04: Lock Color Look Up Table Operation
        										
        uint32_t	Lock_clut: 1;				//IO[4:4]: Lock CLUT
        										//		   - 1: Lock CLUT
        										//		   - 0: Unlock CLUT

        uint32_t	Reserved: 27;               //IO[31:5]: Reserved
                                            	
    } Word1;                                	
                                            	
	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word2;                                	

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word3;  

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word4; 
	
	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word5; 

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word6; 

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word7; 

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word8; 
                                            	
} SECMD_LOCK_CLUT;   

typedef struct _SECMD_WAIT_VO_VSYNC            	
{                                           	
												//Command Type: Wait VO VSync
    struct                                  	
    {                                       	
        uint32_t	OpCode: 4;					//IO[3:0]: Operational Code
        										//		   - 0x08:  Wait VO VSync Operation
        										
        uint32_t	wait_vSync_num: 5;			//IO[8:4]: Waiting for n * (vo_vsync)

        uint32_t	Reserved: 23;               //IO[31:9]: Reserved
                                            	
    } Word1;                                	
                                            	
	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word2;                                	

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word3;  

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word4; 
	
	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word5; 

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word6; 

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word7; 

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word8; 
                                            	
} SECMD_WAIT_VO_VSYNC;   

typedef struct _SECMD_FORMAT_CONVERSION     	
{                                           	
												//Command Type: Format Conversion
    struct                                  	
    {                                       	
        uint32_t	OpCode: 4;					//IO[3:0]: Operational Code
        										//		   - 0x03: Color Format Conversion Operation
        										
        uint32_t	Width: 12;					//IO[15:4]: Width of image in pixels; For ConversionMode[1] == 1, 
        										//			Width should be an even number. 0 means 4096.
                                            	
        uint32_t	Height: 12;					//IO[27:16]: Height of image in pixels; note if 420, 
        										//			 the height of C is only half of Y. 
        										//			 For ConversionMode[1] == 1, Height should be an even number. 0 means 4096. 
                                            	
      	uint32_t	SelectOutputAlpha: 1; 		//IO[28]: SelectOutputAlpha
      											//		  - 0: use alpha from normal operation. If this SelectOutputAlpha = 0 and 
      											//			   ConversionMode = 2, then output alpha=��hff.
												//		  - 1: use constant alpha in SE_Rslt_Alpha register
												//		  - This field is only use if color_format = 8888 or 4444 or 1555.
												//		  - If this SelectOutputAlpha = 1, then SE_Rslt_Alpha will overwrites 
												//			the alpha value of the output for both alpha and ROP operation
                                            	
		uint32_t	ColorKey: 1;				//IO[29]: ColorKey
												//		  - 0: no color key
												//		  - 1: source color key
                                            	
        uint32_t	ConversionMode: 2;         	//IO[31:30]: Conversion Mode: 
												//		  	 - 0: Index -> ARGB
												//		  	 - 1: ARGB -> ARGB
												//		  	 - 2: YCbCr -> ARGB
												//		  	 - 3: ARGB -> YCbCr
                                            	
    } Word1;                                	
                                            	
    struct                                  	
    {                                       	
        uint32_t	Reserved: 2;				//IO[2:0]: Reserved
        uint32_t	ycbcr_seq_mode: 1;
		uint32_t	directFB: 1;				//IO[3]: 0: disable directFB function
												//       1: enable directFB function
		uint32_t	FormatConversionBitblit: 1;	//IO[4]: 0: execute Format conversion only
												//       1: execute Bitblit instruction after Format 
		
        uint32_t	InputX: 12;               	//IO[16:5]: input starting X coordinate; for ConversionMode == 2��b10, 
        										//			this should be an even number
                                            	
        uint32_t	InputY: 12;               	//IO[28:17]: input starting Y coordinate; for ConversionMode == 2��b10, 
        										//			 this should be an even number
        										
		uint32_t	SourceFormat: 3;			//IO[31:29]: Source format: 
												//			 - For ConversionMode==2��b00, 
												//			   - 3��b000: index 2
												//			   - 3��b001: index 4
												//			   - 3��b002: index 8
												//			   - else: reserved
												//			 - For ConversionMode==2��b01 or 2��b11, 
												//			   - 3��b000: RGB332
												//			   - 3��b001: RGB565
												//			   - 3��b010: ARGB1555
												//			   - 3��b011: ARGB4444
												//			   - 3��b100: ARGB8888
												//			   - else: reserved
												//			 - For ConversionMode==2��b10,
												//			   - 3��b000: YCbCr420
												//			   - 3��b001: YCbCr422
												//			   - 3��b010: YCbCr444
												//			   - else: reserved
												   									                        
    } Word2;                                	
                                            	
    struct                                  	
    {                                       	
        uint32_t	Reserved: 5;				//IO[4:0]: Reserved
        uint32_t	OutputX: 12;               	//IO[16:5]: output starting X coordinate; for ConversionMode == 2��b11, 
        										//			this should be an even number
                                            	
        uint32_t	OutputY: 12;               	//IO[28:17]: output starting Y coordinate; for ConversionMode == 2��b11, 
        										//			 this should be an even number
        										
		uint32_t	DestinationFormat: 3;		//IO[31:29]: Dest format: 
												//			 - For ConversionMode==2��b00 or 2��b01 or 2��b10, 
												//			   - 3��b000: RGB332
												//			   - 3��b001: RGB565
												//			   - 3��b010: ARGB1555
												//			   - 3��b011: ARGB4444
												//			   - 3��b100: ARGB8888
												//			   - else: reserved
												//			 - For ConversionMode==2��b11,
												//			   - 3��b000: YCbCr420
												//			   - 3��b001: YCbCr422
												//			   - 3��b010: YCbCr444
												//			   - else: reserved 
												   									                        
    } Word3;                                	
                                            	
    struct                                  	
    {                                       	
        uint32_t	Reserved: 11;				//IO[10:0]: Reserved
        uint32_t	ChromaAddressIndex: 7;     	//IO[17:11]: Chroma address DCU index[6:0] if either source or 
        										//			 dest color format is YCbCr
                                            	
        uint32_t	DestAddressIndex: 7;       	//IO[24:18]: Dest address index[1:0], this will select the 
        										//			 corresponding SE_Baddr and SE_Pitch registers 
        										//			 if destination color format is not YCbCr.
												//			 Dest address DCU index[6:0] if destination color format is YCbCr. 
                                            	
        										
		uint32_t	SrcAddressIndex: 7;			//IO[31:25]: Src address index[1:0], this will select the 
												//			 corresponding SE_Baddr and SE_Pitch registers 
												//			 if source color format is not YCbCr
												//			 Src address DCU index[6:0] if source color is YCbCr.
    } Word4;                                	
                                            	
	struct										
	{											
        uint32_t	fb_sel_destclr_blend: 4;    //IO[3:0]: This field is used to select the destination color blending 
                                                //              value (without alpha) to be used in generation of the output color
        uint32_t    fb_sel_srcclr_blend: 4;     //IO[7:4]: This field is used to select the source color blending 
                                                //              value (without alpha) to be used in generation of the output color
        uint32_t    fb_demultiply: 1;           //IO[8:8]: Divide destination color by destination alpha before writing to DDR.
        uint32_t    fb_blend_alphachannel: 1;   //IO[9:9]: Modulate source alpha with constant alpha.
        uint32_t    fb_blend_coloralpha: 1;     //IO[10:10]: Replace source alpha with constant alpha
        uint32_t    fb_colorize: 1;             //IO[11:11]: Modulate source color with constant color
        uint32_t    fb_xor: 1;                  //IO[12:12]: XOR source pixel with destination pixel
        uint32_t    fb_src_premultiply: 1;      //IO[13:13]: Modulate source color with source alpha
        uint32_t    fb_src_premulcolor: 1;      //IO[14:14]: Modulate source color with constant alpha
        uint32_t    fb_dst_premultiply: 1;      //IO[15:15]: Modulate destination color with destination
        uint32_t    src_clr_transparency: 1;    //IO[16:16]: Enable/Disable transparency for source color transform
        uint32_t    src_clr_transform: 2;       //IO[18:17]: Enable/Disable source color transform
		uint32_t	rop_mode: 1;				//IO[19]: ROP Mode 
												//		  - 0: alpha blending
												//		  - 1: ROP mode
        uint32_t    bitblit_color_key: 2;       //IO[21:20]: ColorKey
                                                //           - 00: no color key
                                                //           - 01: source color key
                                                //           - 10: destination color key
                                                //           - 11: Both source color key and destination color key.
        uint32_t    sel_src_alpha: 3;           //IO[24:22]: This field is used to select the source alpha value to be 
                                                //           used in generation of the output
                                                //           - 000:  select constant SE_Src_Alpha
                                                //           - 001: select constant (1-SE_Src_Alpha)
                                                //           - 010: select dest alpha (i.e. dest(A) �V destination pixel by pixel alpha)
                                                //           - 011: select (1-dest(A) )
                                                //           - 100: select pixel by pixel src alpha (i.e. src(A))
                                                //           - 101: select (1-src(A))
                                                //           - 110 and 111:  reserved 
        uint32_t    rop_code: 2;                //IO[26:25]: ROP code for ROP operation
        uint32_t    sel_output_alpha: 1;        //IO[27]: SelectOutputAlpha
                                                //        - 0: use alpha from normal operation
                                                //        - 1: use constant alpha in SE_Rslt_Alpha register
                                                //        - This field is only use if color_format = 8888 or 4444 or 1555.
                                                //        - If this sel_output_alpha=1, then SE_Rslt_Alpha will overwrites the alpha 
                                                //          value of the output for both alpha and ROP operation
        uint32_t    sync_vo: 1;                 //IO[28]: 
                                                //          1: bitblit instruction needs to sync with VO current line number to avoid trashing
                                                //          0: bitblit is executed immediately without waiting
        uint32_t    sel_dest_alpha: 3;          //IO[31:29]: This field is used to select the destination alpha value 
                                                //           to be used in generation of the output
                                                //           - 000:  select constant SE_Dest_Alpha
                                                //           - 001: select constant (1-SE_Dest_Alpha)
                                                //           - 010: select dest alpha (i.e. dest(A) �V destination pixel by pixel alpha)
                                                //           - 011: select (1-dest(A) )
                                                //           - 100: select pixel by pixel src alpha (i.e. src(A))
                                                //           - 101: select (1-src(A))
                                                //           - 110 and 111:  reserved 
                                                //           - the "1" in 001, 011 and 101 implies unity number, 
                                                //             or 256 in 8 bit fractional number representation
	} Word5; 

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word6; 

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word7; 

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word8; 

} SECMD_FORMAT_CONVERSION;                  	
                                            	
typedef struct _SECMD_BITBLT    	
{                                           	
												//Command Type: Bitblit
    struct                                  	
    {                                       	
        uint32_t	OpCode: 4;					//IO[3:0]: Operational Code
        										//		   - 0x05: Bitblit Operation
        										//		   - 0x0D: Bitblit Operation With Source Color Transformation or DFB

        										
        uint32_t	Width: 12;					//IO[15:4]: Width of image in pixels. 0 means 4096.
                                            	
        uint32_t	Height: 12;					//IO[27:16]: Height of image in pixels. 0 means 4096.
                                            	
      	uint32_t	InputSelect: 1; 			//IO[28]: InputSelect
      											//		  - 0: select constant input (SE_Src_Color and SE_Src_Alpha); 
      											//		  - 1: set input vector 
      											//		  - If this field is 1, then the optional 
      											//			input address word of the command is presented

		uint32_t	SelectDestAlpha: 3;			//IO[31:29]: This field is used to select the destination alpha value 
												//			 to be used in generation of the output
												//			 - 000:  select constant SE_Dest_Alpha
												//			 - 001: select constant (1-SE_Dest_Alpha)
												//			 - 010: select dest alpha (i.e. dest(A) �V destination pixel by pixel alpha)
												//			 - 011: select (1-dest(A) )
												//			 - 100: select pixel by pixel src alpha (i.e. src(A))
												//			 - 101: select (1-src(A))
												//			 - 110 and 111:  reserved 
												//			 - the "1" in 001, 011 and 101 implies unity number, 
												//			   or 256 in 8 bit fractional number representation
                                            	
    } Word1;                                	
                                            	
    struct                                  	
    {                                       	
        uint32_t	OutputX: 12;               	//IO[11:0]: output starting X coordinate 
                                            	
        uint32_t	OutputY: 12;               	//IO[23:12]: output starting Y coordinate
        										
		uint32_t	StartingCorner: 2;		    //IO[25:24]: GradientDirection
												//			 - If InputSelect == 1, Starting_corner: 
												//			   - This field is used to allow Bitblit from a source that 
												//				 overlaps with the destination.
												//			   - SW should program the correct starting corner from 4 corners 
												//				 of a rectangular to prevent data overwrite.
												//			   - 00: start at top-left corner
												//			   - 01: start at top-right corner
												//			   - 10: start at bottom-left corner
												//			   - 11: start at bottom-right corner
																			   					
		uint32_t	RopCode: 2;					//IO[27:26]: ROP code for ROP operation
		uint32_t	SelectOutputAlpha: 1;		//IO[28]: SelectOutputAlpha
												//		  - 0: use alpha from normal operation
												//		  - 1: use constant alpha in SE_Rslt_Alpha register
												//		  - This field is only use if color_format = 8888 or 4444 or 1555.
												//		  - If this sel_output_alpha=1, then SE_Rslt_Alpha will overwrites the alpha 
												//			value of the output for both alpha and ROP operation
		
		uint32_t	sync_vo: 1;			        //IO[29]: 
		                                        //          1: bitblit instruction needs to sync with VO current line number to avoid trashing
                                                //          0: bitblit is executed immediately without waiting
			
		uint32_t	DestAddressIndex: 2;		//IO[31:30]: Dest address index, this will select the corresponding 
												//			 SE_Baddr and SE_Pitch registers 
			
    } Word2;                                	
                                            	
    struct                                  	
    {                                       	
        uint32_t	InputX: 12;               	//IO[11:0]: input starting X coordinate 
                                            	
        uint32_t	InputY: 12;               	//IO[23:12]: input starting Y coordinate
        										
		uint32_t	RopMode: 1;					//IO[24]: ROP Mode 
												//		  - 0: alpha blending
												//		  - 1: ROP mode

		uint32_t	ColorKey: 2;				//IO[26:25]: ColorKey
												//			 - 00: no color key
												//			 - 01: source color key
												//			 - 10: destination color key
												//			 - 11: Both source color key and destination color key.

		uint32_t	SelectSrcAlpha: 3;			//IO[29:27]: This field is used to select the source alpha value to be 
												//			 used in generation of the output
												//			 - 000:  select constant SE_Src_Alpha
												//			 - 001: select constant (1-SE_Src_Alpha)
												//			 - 010: select dest alpha (i.e. dest(A) �V destination pixel by pixel alpha)
												//			 - 011: select (1-dest(A) )
												//			 - 100: select pixel by pixel src alpha (i.e. src(A))
												//			 - 101: select (1-src(A))
												//			 - 110 and 111:  reserved 

		uint32_t	SrcAddressIndex: 2;			//IO[31:30]: src address index, this will select the corresponding 
												//			 SE_Baddr and SE_Pitch registers (input address is optional, 
												//			 and only used if input_select = 1)
												   									                        
    } Word3;                                	
                                            	
    struct                                  	
    {                                       	
        uint32_t	Reserved: 12;               //IO[11:0]: Reserved
        uint32_t	fb_sel_destclr_blend: 4;    //IO[15:12]: This field is used to select the destination color blending 
                                                //              value (without alpha) to be used in generation of the output color
        uint32_t    fb_sel_srcclr_blend: 4;     //IO[19:16]: This field is used to select the source color blending 
                                                //              value (without alpha) to be used in generation of the output color
        uint32_t    fb_demultiply: 1;           //IO[20:20]: Divide destination color by destination alpha before writing to DDR.
        uint32_t    fb_blend_alphachannel: 1;   //IO[21:21]: Modulate source alpha with constant alpha.
        uint32_t    fb_blend_coloralpha: 1;     //IO[22:22]: Replace source alpha with constant alpha
        uint32_t    fb_colorize: 1;             //IO[23:23]: Modulate source color with constant color
        uint32_t    fb_xor: 1;                  //IO[24:24]: XOR source pixel with destination pixel
        uint32_t    fb_src_premultiply: 1;      //IO[25:25]: Modulate source color with source alpha
        uint32_t    fb_src_premulcolor: 1;      //IO[26:26]: Modulate source color with constant alpha
        uint32_t    fb_dst_premultiply: 1;      //IO[27:27]: Modulate destination color with destination
        uint32_t    directFB: 1;                //IO[28:28]: Enable/Disable directFB function
        uint32_t    src_clr_transparency: 1;    //IO[29:29]: Enable/Disable transparency for source color transform
        uint32_t    src_clr_transform: 2;       //IO[31:30]: Enable/Disable source color transform
    } Word4;                                	

    struct                                  	
    {                                       	
        uint32_t	Reserved;					//IO[31:0]: The value of 1/abs(End_X �V X). This division operatoin is performed by CPU. 
        										//			In (1,31) format. For rectangle width of 1 pixel, the value should be set as 0
									   										                        
    } Word5;

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word6; 

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word7; 

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word8; 

                                          	
} SECMD_BITBLT;                                            	
                                            	
typedef struct _SECMD_STRETCH    	
{                                           	
												//Command Type: Stretch
    struct                                  	
    {                                       	
        uint32_t	OpCode: 4;					//IO[3:0]: Operational Code
        										//		   - 0x06: Stretch Operation
        										
		uint32_t	OutputX: 12;				//IO[15:4]: output starting X coordinate; 
												//			when 422/420, this value should be an even number. 
        
        uint32_t	OutputY: 12;				//IO[27:16]: output starting Y coordinate; 
        										//			 when 420, this value should be an even number.

		uint32_t	ColorKey: 1;				//IO[28]: Color Key
												//  	  - 0: no color key
												//  	  - 1: source color key

		uint32_t	HScalingEnable: 1;			//IO[29]: Enable of H-scaling; if disable, only bypass
		uint32_t	VScalingEnable: 1;			//IO[30]: Enable of V-scaling; if disable, only bypass
		uint32_t	SrcInterleaving: 1;			//IO[31]: interleaving mode for source image
                                           	
    } Word1;                                	
                                            	
    struct                                  	
    {                                       	
		uint32_t	OutputWidth: 12;			//IO[11:0]: Output number of pixels in Width. 0 means 4096. 
												//			Due to HW implementation, the number should be not 
												//			bigger than (Input_Width  * 8 / (H_scaling_delta_phase) + 16); 
												//			when 422/420, this value should be an even number.
												
		uint32_t	OutputHeight: 12;			//IO[23:12]: Output number of pixels in Height. 0 means 4096; when 420, 
												//			 this value should be an even number.
		
		uint32_t	StretchBitblit: 1;			//IO[24]: 0: execute Stretch instruction only
												//        1: execute Bitblit instruction after Stretch
		uint32_t	directFB: 1;				//IO[25]: 0: disable directFB function
												//        1: enable directFB function

		uint32_t	Reserved: 3;				//IO[28:26]: Reserved

		uint32_t    YCbCrSeqMode: 1;            //IO[29]: Set sequential mode for 422/420
		                                        //        0: block mode
		                                        //        1: sequential mode
			
		uint32_t	ScalingAlgorithm: 2;		//IO[31:30]: Selection of scaling algorithm: 
												//			 - 00: reserved
												//			 - 01: FIR
												//			 - 10: repeat/drop (nearest neighbor)
												//			 - 11: directional scaling (DS)
											
    } Word2;                                	
                                            	
    struct                                  	
    {                                       	
		uint32_t	InputX: 12;					//IO[11:0]: input starting X coordinate; 
												//			when 422/420, this value should be an even number. 
	
		uint32_t	InputY: 12;					//IO[23:12]: input starting Y coordinate; 
												//			 when 420, this value should be an even number.
	
		uint32_t	DestInterleaving: 1;		//IO[24]: interleaving mode for dest. image 
		
		uint32_t	SrcAddressIndex: 7;			//IO[31:25]: SrcAddressIndex
												//			 - Src address index[1:0], this will select the 
												//			   corresponding SE_Baddr and SE_Pitch registers 
												//			   if source color format is not YCbCr
												//			 - Src address DCU index[6:0] if source color is YCbCr.

												   									                        
    } Word3;                                	
                                            	
    struct                                  	
    {                                       	
		uint32_t	InputWidth: 13;					//IO[12:0]: Input number of pixels in Width. 0 means 8192; 
												//			when 422/420, this value should be an even number. 
		
		uint32_t	InputHeight: 12;				//IO[24:13]: Input number of pixels in Height. 0 means 4096; 
												//			 when 420, this value should be an even number. 
		
		uint32_t	DestAddressIndex: 7;			//IO[31:25]: DestAddressIndex
												//			 - Dest address index[1:0], this will select the 
												//			   corresponding SE_Baddr and SE_Pitch registers 
												//			   if destination color format is not YCbCr.
												//			 - Dest address DCU index[6:0] if destination color format is YCbCr.
									                        
    } Word4;                                	
                                          	
	struct										
	{											
        uint32_t	fb_sel_destclr_blend: 4;    //IO[3:0]: This field is used to select the destination color blending 
                                                //              value (without alpha) to be used in generation of the output color
        uint32_t    fb_sel_srcclr_blend: 4;     //IO[7:4]: This field is used to select the source color blending 
                                                //              value (without alpha) to be used in generation of the output color
        uint32_t    fb_demultiply: 1;           //IO[8:8]: Divide destination color by destination alpha before writing to DDR.
        uint32_t    fb_blend_alphachannel: 1;   //IO[9:9]: Modulate source alpha with constant alpha.
        uint32_t    fb_blend_coloralpha: 1;     //IO[10:10]: Replace source alpha with constant alpha
        uint32_t    fb_colorize: 1;             //IO[11:11]: Modulate source color with constant color
        uint32_t    fb_xor: 1;                  //IO[12:12]: XOR source pixel with destination pixel
        uint32_t    fb_src_premultiply: 1;      //IO[13:13]: Modulate source color with source alpha
        uint32_t    fb_src_premulcolor: 1;      //IO[14:14]: Modulate source color with constant alpha
        uint32_t    fb_dst_premultiply: 1;      //IO[15:15]: Modulate destination color with destination
        uint32_t    src_clr_transparency: 1;    //IO[16:16]: Enable/Disable transparency for source color transform
        uint32_t    src_clr_transform: 2;       //IO[18:17]: Enable/Disable source color transform
		uint32_t	rop_mode: 1;				//IO[19]: ROP Mode 
												//		  - 0: alpha blending
												//		  - 1: ROP mode
        uint32_t    bitblit_color_key: 2;       //IO[21:20]: ColorKey
                                                //           - 00: no color key
                                                //           - 01: source color key
                                                //           - 10: destination color key
                                                //           - 11: Both source color key and destination color key.
        uint32_t    sel_src_alpha: 3;           //IO[24:22]: This field is used to select the source alpha value to be 
                                                //           used in generation of the output
                                                //           - 000:  select constant SE_Src_Alpha
                                                //           - 001: select constant (1-SE_Src_Alpha)
                                                //           - 010: select dest alpha (i.e. dest(A) �V destination pixel by pixel alpha)
                                                //           - 011: select (1-dest(A) )
                                                //           - 100: select pixel by pixel src alpha (i.e. src(A))
                                                //           - 101: select (1-src(A))
                                                //           - 110 and 111:  reserved 
        uint32_t    rop_code: 2;                //IO[26:25]: ROP code for ROP operation
        uint32_t    sel_output_alpha: 1;        //IO[27]: SelectOutputAlpha
                                                //        - 0: use alpha from normal operation
                                                //        - 1: use constant alpha in SE_Rslt_Alpha register
                                                //        - This field is only use if color_format = 8888 or 4444 or 1555.
                                                //        - If this sel_output_alpha=1, then SE_Rslt_Alpha will overwrites the alpha 
                                                //          value of the output for both alpha and ROP operation
        uint32_t    sync_vo: 1;                 //IO[28]: 
                                                //          1: bitblit instruction needs to sync with VO current line number to avoid trashing
                                                //          0: bitblit is executed immediately without waiting
        uint32_t    sel_dest_alpha: 3;          //IO[31:29]: This field is used to select the destination alpha value 
                                                //           to be used in generation of the output
                                                //           - 000:  select constant SE_Dest_Alpha
                                                //           - 001: select constant (1-SE_Dest_Alpha)
                                                //           - 010: select dest alpha (i.e. dest(A) �V destination pixel by pixel alpha)
                                                //           - 011: select (1-dest(A) )
                                                //           - 100: select pixel by pixel src alpha (i.e. src(A))
                                                //           - 101: select (1-src(A))
                                                //           - 110 and 111:  reserved 
                                                //           - the "1" in 001, 011 and 101 implies unity number, 
                                                //             or 256 in 8 bit fractional number representation
	} Word5; 

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word6; 

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word7; 

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word8; 

} SECMD_STRETCH;                                                   	

typedef struct _SECMD_MIRROR    	
{                                           	
												//Command Type: Mirror
    struct                                  	
    {                                       	
        uint32_t	OpCode: 4;					//IO[3:0]: Operational Code
        										//		   - 0x07: Mirror Operation
        										
        uint32_t	OutputX: 12;				//IO[15:4]: output starting X coordinate 
        uint32_t	OutputY: 12;				//IO[27:16]: output starting Y coordinate
		uint32_t	MirrorDirection: 2;			//IO[29:28]: Mirror direction
												//			 - 00: reserved
												//			 - 01: mirror at X coordinate
												//			 - 10: mirror at Y coordinate
												//			 - 11: mirror at X & Y coordinate

		uint32_t	DestAddressIndex: 2;		//IO[31:30]: Dest address index, this will select the 
												//			 corresponding SE_Baddr and SE_Pitch registers
                                            	
    } Word1;                                	
                                            	
    struct                                  	
    {                                       	
        uint32_t	Width: 12;					//IO[11:0]: Width of image in pixels. 0 means 4096.
        uint32_t	Height: 12;					//IO[23:12]: Height of image in pixels. 0 means 4096.
		uint32_t	Reserved: 8;				//IO[31:24]: Reserved
			
    } Word2;                                	
                                            	
    struct                                  	
    {                                       	
        uint32_t	Reserved1: 4;				//IO[3:0]: Reserved
        uint32_t    InputX: 12;               	//IO[15:4]: input starting X coordinate                                             	
        uint32_t    InputY: 12;               	//IO[27:16]: input starting Y coordinate
		uint32_t	Reserved2: 2;				//IO[29:28]: Reserved
		uint32_t	SrcAddressIndex: 2;			//IO[31:30]: Src address index, this will select the 
												//			 corresponding SE_Baddr and SE_Pitch registers
												   									                        
    } Word3;                                	

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word4; 

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word5; 

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word6; 

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word7; 

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word8; 

                                          	
} SECMD_MIRROR;                                       	

typedef struct _SECMD_ROTATE    	
{                                           	
												//Command Type: Rotate
    struct                                  	
    {                                       	
        uint32_t	OpCode: 4;					//IO[3:0]: Operational Code
        										//		   - 0x0A: Rotate Operation
        uint32_t	Reserved1: 26;				//IO[29:4]: Reserved
        uint32_t	RotateMode: 2;				//IO[31:30]: Rotate mode
    } Word1;                                	

    struct                                  	
    {    
        uint32_t    InputX: 12;                 //IO[11:0]: Input starting X coordinate 
        uint32_t    InputY: 12;                 //IO[23:12]: Input starting Y coordinate 
        uint32_t    Reserved: 1;                //IO[24]: Reserved
        uint32_t    SrcAddressIndex: 7;         //IO[31:25]: Source address index, this will select 
                                                //           the corresponding SE_Baddr and SE_Pitch registers			
    } Word2;                            	
                                            	
    struct                                  	
    {                                       										
        uint32_t	OutputX: 12;				//IO[11:0]: Output starting X coordinate 
        uint32_t	OutputY: 12;				//IO[23:12]: Output starting Y coordinate 
		uint32_t	Reserved: 1;				//IO[24]: Reserved
		uint32_t	DestAddressIndex: 7;		//IO[31:25]: Dest address index, this will select the 
												//			 corresponding SE_Baddr and SE_Pitch registers
    } Word3;                                	

    struct                                  	
    {    
		uint32_t	InputWidth: 12;				//IO[11:0]: Width of input image in pixels. 0 means 4096.
    	uint32_t	Reserved1: 4;				//IO[15:12]: Reserved	                                   	
		uint32_t	InputHeight: 12;			//IO[27:16]: Height of input image in pixels. 0 means 4096.
		uint32_t	Reserved2: 4;				//IO[31:28]: Reserved	
    } Word4;

    struct                                  	
    {                                       	
    	uint32_t	Reserved;					//IO[31:0]: Reserved

    } Word5; 

    struct                                  	
    {                                       	
    	uint32_t	Reserved;					//IO[31:0]: Reserved

    } Word6; 

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word7;  

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word8; 
	
} SECMD_ROTATE; 

typedef struct _SECMD_ALPHA // Saturn Spec, page 60, Command: Alpha
{                                           	
    struct                                  	
    {                                       	
        uint32_t	OpCode: 4;
        uint32_t	Width: 12;
        uint32_t	Height: 12;
        uint32_t	SelAlpha: 1;
        uint32_t	StreamType: 2;
        uint32_t	DfbSrcColorKey: 1;
    } Word1;                                	

    struct                                  	
    {    
        uint32_t    InputSX: 12;
        uint32_t    InputSY: 12;
        uint32_t    DfbSrcMaskAlpha: 1;
        uint32_t    SAddrIndex: 7;
    } Word2;                            	
                                            	
    struct                                  	
    {                                       										
        uint32_t	InputDX: 12;
        uint32_t	InputDY: 12;
		uint32_t	DfbSrcMaskColor: 1;
		uint32_t	DAddrIndex: 7;
    } Word3;                                	

    struct                                  	
    {    
		uint32_t	OutputX: 12;
    	uint32_t	OutputY: 12;
		uint32_t	Reserved: 1;
		uint32_t	RAddrIndex: 7;
    } Word4;

    struct                                  	
    {                                       	
		uint32_t	InputAX: 12;
    	uint32_t	InputAY: 12;
		uint32_t	AaddrIndex: 2;
		uint32_t	Reserved: 4;
		uint32_t	StreamAlphaLocation: 1;
		uint32_t	StreamBigEndian: 1;
    } Word5; 

    struct                                  	
    {                                       	
		uint32_t	RCAddrIndex: 7;
		uint32_t	Reserved1: 1;
		uint32_t	DCAddrIndex: 7;
		uint32_t	Reserved2: 1;
		uint32_t	SCAddrIndex: 7;
		uint32_t	Reserved3: 9;
    } Word6; 

	struct										
	{											
		uint32_t	Reserved;						
	} Word7;  

	struct										
	{											
		uint32_t	Reserved;
	} Word8; 
	
} SECMD_ALPHA; 

typedef struct _SECMD_COPY    	
{                                           	
    //Command Type: Copy
    struct
    {
        uint32_t	OpCode: 4;			//IO[3:0]: Operational Code
        uint32_t	Width: 12;			//IO[15:4]: Width of image in pixels. 0 means 4096.
        uint32_t	Height: 12;			//IO[27:16]: Height of image in pixels. 0 means 4096.
	uint32_t	Reserved: 4;			//IO[31:28]: Reserved
    } Word1;                                	
                                            	
    struct                                  	
    {                                       	
        uint32_t	OutputX: 12;               	//IO[11:0]: output starting X coordinate 
        uint32_t	OutputY: 12;               	//IO[23:12]: output starting Y coordinate
	uint32_t	Reserved: 6;			//IO[29:24]: Reserved
	uint32_t	DestAddressIndex: 2;		//IO[31:30]: Dest address index, this will select the corresponding 
							//	     SE_Baddr and SE_Pitch registers 
    } Word2;

    struct                                  	
    {                                       	
        uint32_t	InputX: 12;               	//IO[11:0]: input starting X coordinate 
        uint32_t	InputY: 12;               	//IO[23:12]: input starting Y coordinate
	uint32_t	Reserved: 6;			//IO[29:24]: Reserved
	uint32_t	SrcAddressIndex: 2;		//IO[31:30]: Src address index, this will select the corresponding 
							//	     SE_Baddr and SE_Pitch registers 
							//          (input address is optional, and only used if input_select = 1)
    } Word3;

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word4; 

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word5; 

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word6; 

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word7; 

	struct										
	{											
		uint32_t	Reserved;					//IO[31:0]: Reserved
												
	} Word8; 

                                          	
} SECMD_COPY;                                       	

typedef struct _SECMD_NOP                   	
{                                           	//Command Type: NOP
    struct                                  	
    {                                       	
        uint32_t	OpCode: 4;					//IO[3:0]: Operational Code
        										//		   - 0x0F: NOP
                                            	
        uint32_t  Reserved: 28;               	//IO[31:4]: Reserved
                 
    } Word1;
    
} SECMD_NOP; 

//=================================================================================================

#endif

//=================================================================================================
// End of File
