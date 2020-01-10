#ifndef SYSTEM_MEM_H
#define SYSTEM_MEM_H
#include <system/SystemMemory.h>
#include <allocator/Allocator.h>
#include <allocator/IonAllocator.h>
#include <allocator/MallocAllocator.h>

SystemMemory *SystemMemory_Malloc(int dMallocSize);
SystemMemory *SystemMemory_ION_alloc(int dIONallocSize, int dIONHeapMask, int dIONHeapFlag);
void SystemMemory_free(SystemMemory **mem);
#endif
