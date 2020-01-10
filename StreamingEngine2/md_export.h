#ifndef MD_EXPORT_H
#define MD_EXPORT_H

#include <linux/types.h>

/*
 * Ioctl definitions
 */

/* Use 'k' as magic number */
#define MD_IOC_MAGIC  'k'
/* Please use a different 8-bit number in your code */

#define MD_IOCRESET    _IO(SE_IOC_MAGIC, 0)

/*
 * S means "Set" through a ptr,
 * T means "Tell" directly with the argument value
 * G means "Get": reply by setting through a pointer
 * Q means "Query": response is on the return value
 * X means "eXchange": switch G and S atomically
 * H means "sHift": switch T and Q atomically
 */
#define MD_IOCSQUANTUM _IOW(MD_IOC_MAGIC,  1, int)
#define MD_IOCSQSET    _IOW(MD_IOC_MAGIC,  2, int)
#define MD_IOCTQUANTUM _IO(MD_IOC_MAGIC,   3)
#define MD_IOCTQSET    _IO(MD_IOC_MAGIC,   4)
#define MD_IOCGQUANTUM _IOR(MD_IOC_MAGIC,  5, int)
#define MD_IOCGQSET    _IOR(MD_IOC_MAGIC,  6, int)
#define MD_IOCQQUANTUM _IO(MD_IOC_MAGIC,   7)
#define MD_IOCQQSET    _IO(MD_IOC_MAGIC,   8)
#define MD_IOCXQUANTUM _IOWR(MD_IOC_MAGIC, 9, int)
#define MD_IOCXQSET    _IOWR(MD_IOC_MAGIC,10, int)
#define MD_IOCHQUANTUM _IO(MD_IOC_MAGIC,  11)
#define MD_IOCHQSET    _IO(MD_IOC_MAGIC,  12)

/*
 * The other entities only have "Tell" and "Query", because they're
 * not printed in the book, and there's no need to have all six.
 * (The previous stuff was only there to show different ways to do it.
 */
#define MD_P_IOCTSIZE _IO(MD_IOC_MAGIC,   13)
#define MD_P_IOCQSIZE _IO(MD_IOC_MAGIC,   14)
/* ... more to come */

#define MD_IOC_READ_INST_COUNT _IOR(MD_IOC_MAGIC, 15, int)
#define MD_IOC_WRITE_ISSUE_CMD _IOR(MD_IOC_MAGIC, 16, int)

#define MD_IOC_READ_ISSUED_INST_COUNT _IOR(MD_IOC_MAGIC, 17, int)

#define MD_IOC_COPY_PAGES _IO(MD_IOC_MAGIC, 18)

#define MD_IOC_MAXNR 21

#endif
