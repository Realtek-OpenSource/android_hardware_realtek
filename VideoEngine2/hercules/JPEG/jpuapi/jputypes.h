#ifndef _JPU_TYPES_H_
#define _JPU_TYPES_H_

#if defined(__LP64__)
#include <stdint.h>
typedef uint32_t	Uint32;
typedef unsigned char	Uint8;
typedef unsigned short	Uint16;
#ifndef RVSD_USE_JPU_API
typedef char	        Int8;
#endif
typedef int            Int32;
typedef short	        Int16;
typedef uint64_t Uint64;
typedef int64_t Int64;
#else
typedef unsigned char	Uint8;
typedef unsigned char   uint8_t;
typedef unsigned int	Uint32;
typedef unsigned int    uint32_t;
typedef unsigned short	Uint16;
#ifndef RVSD_USE_JPU_API
typedef char	        Int8;
#endif
typedef int	            Int32;
typedef short	        Int16;
#if defined(_MSC_VER)
typedef unsigned _int64 Uint64;
typedef _int64 Int64;
#else
typedef unsigned long long Uint64;
typedef unsigned long long uint64_t;
typedef long long Int64;
#endif

#endif	//end if __LP64__

#ifndef PhysicalAddress
typedef Uint32 PhysicalAddress;
#endif
#ifndef BYTE
typedef unsigned char   BYTE;
#endif
#ifndef BOOL
typedef int BOOL;
#endif

#ifndef FALSE
#define FALSE           0
#endif /* FALSE */
#ifndef TRUE
#define TRUE            1
#endif /* TRUE */
#ifndef NULL
#define NULL	0
#endif


#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(P) { (P) = (P); }
#endif

#endif	/* _JPU_TYPES_H_ */
