#ifndef __RTK_POWER_HAL_UTILS_H__
#define __RTK_POWER_HAL_UTILS_H__

ssize_t sysfs_write(const char *path, char *s);
ssize_t sysfs_read(const char *path, char *s, int num_bytes);

int RegWrite(unsigned long phyOffset, unsigned int mask, unsigned data);

#endif /* End of __RTK_POWER_HAL_UTILS_H__ */
