#ifndef __RTK_SECURE_HANDLE_H_
#define __RTK_SECURE_HANDLE_H_

#include <inc/rtk_secure_handle.h>

secure_handle_t * secure_handle_create (int fd, unsigned int allocSize, unsigned int phyAddr);
void secure_handle_delete (secure_handle_t * handle);

#endif /* End of __RTK_SECURE_HANDLE_H_ */
