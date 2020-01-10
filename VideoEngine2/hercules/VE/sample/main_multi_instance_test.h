//------------------------------------------------------------------------------
// File: main_multi_instance_test.h
//
// Copyright (c) 2006, Chips & Media.  All rights reserved.
//------------------------------------------------------------------------------
#ifndef MAIN_MULTI_INSTANCE_TEST
#define MAIN_MULTI_INSTANCE_TEST
extern Uint32               sizeInWord;
extern Uint16*              pusBitCode;

void WaitForNextStep(
    BOOL enableSync,
    BOOL* isRunning,
    Int32   instIdx,
    Int32 curStepName
);

enum waitStatus {
    WAIT_AFTER_INIT         = 0,

    WAIT_AFTER_DEC_OPEN     = 1,
    WAIT_AFTER_SEQ_INIT     = 2,
    WAIT_AFTER_REG_BUF      = 3,
    WAIT_BEFORE_DEC_START   = 4,
    WAIT_BEFORE_DEC_CLOSE    = 5,

    WAIT_AFTER_ENC_OPEN     = 6,
    WAIT_AFTER_INIT_SEQ    = 7,
    WAIT_AFTER_REG_FRAME    = 8,
    WAIT_BEFORE_ENC_START   = 9,
    WAIT_BEFORE_ENC_CLOSE   = 10,
    WAIT_NOT_DEFINED        = 11
};
#endif /* MAIN_MULTI_INSTANCE_TEST */

