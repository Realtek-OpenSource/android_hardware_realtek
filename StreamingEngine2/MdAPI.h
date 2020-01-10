/*
 * MdAPI.h
 *
 *  Created on: June 25, 2015
 *      Author: calvinkuo
 */

#ifndef MDAPI_H_
#define MDAPI_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "OSAL.h"
#include "hresult.h"
#include "md.h"

HRESULT
MD_Memcpy_API( unsigned int dstPAddr, unsigned int srcPAddr,
            int size,
            HANDLE hQueue);

#ifdef __cplusplus
}
#endif

#endif /* MDAPI_H_ */
