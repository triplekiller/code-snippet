// https://blog.csdn.net/21cnbao/article/details/103470878

// System V API(ftok/shmget/shmat/shmdt/shmctl)
// POSIX API(shm_open/shm_unlink/mmap)
// memfd_create(memfd_create/ftruncate)
// dma_buf


#include <stdio.h>
#include <unistd.h>
#include <string.h>

// for System V SHM API
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>

void sys_v_shm(int rw_flag)
{


}
