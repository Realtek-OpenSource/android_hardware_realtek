/**
 * Hardware specific defines
 *
 *
 * @author Brad Bitterman
 *
 */

#ifndef HDCP2_HAL_H
#define HDCP2_HAL_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <openssl/sha.h>

#define H2uint8  uint8_t
#define H2uint16 uint16_t
#define H2uint32 uint32_t

/* Define boolean types */
#define H2bool   bool

#ifndef TRUE
#define TRUE     true
#define FALSE    false
#endif

/* Define status codes */
typedef enum 
{
   H2_OK = 0,
   H2_ERROR

} H2status;

#define H2DBGLOG(arg)

/* Define log function */
#define ENABLE  1
#define DISABLE 0

/* Define the H2Sha256Ctx structure. */
struct H2Sha256Ctx
{
   SHA256_CTX c;
};

#endif
