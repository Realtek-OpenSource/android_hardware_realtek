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

#ifndef _MD_CMD_H_
#define _MD_CMD_H_

//=================================================================================================
typedef struct _MDCMD_WRITE_REGISTER_SS
{
												//Command Type: Write Register
    struct
    {
        uint32_t	OpCode: 4;					//IO[3:0]: Operational Code
        uint32_t  MoveMode: 2;           //IO[5:4]: Move Mode
        uint32_t  InputSel: 1;           //IO[6]: Input Selection
        uint32_t  MoveDir: 1;           //IO[7]: Move Direction
        uint32_t	Reserved: 24;               //IO[31:8]: Reserved

    } Word1;

    struct
    {
        uint32_t	Daddr: 31;				  //IO[30:0]: Starting Dest SDRAM address
        uint32_t  Reserved: 1;           //IO[31]: Reserved

    } Word2;
#if 1
    struct
    {
        uint32_t	Saddr: 31;				  //IO[30:0]: Starting Source SDRAM address
        uint32_t  Reserved: 1;           //IO[31]: Reserved

    } Word3;

    struct
    {
        uint32_t	LengthSeq: 20;				  //IO[19:0]: The Length in Seq Mode
        uint32_t  Reserved: 11;           //IO[31:20]: Reserved

    } Word4;
#endif

} MDCMD_WRITE_REGISTER_SS;

//=================================================================================================

#endif

//=================================================================================================
// End of File
