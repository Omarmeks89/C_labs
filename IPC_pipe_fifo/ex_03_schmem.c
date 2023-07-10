#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <errno.h>

#include "ex_03_schm_types.h"


int main()
{
    int *shmarr, arrini;
    int shmid; /* descriptor from shmget() */
    char pathname[] = "a.out";
    /* file with pathname shoutd be exists */
    key_t shm_key; /* IPC key */
    
    arrini = NINIT;
    /* create IPC key by a prog name. */
    shm_key = ftok(pathname, 0);
    if(shm_key < 0) {
	/* prefer use errno.h */
        printf("Can`t generate key\n");
        return S_SHMKEY;
    }
    /* try to create excl sharedmem. */
    shmid = shmget(shm_key, sizeof(int) * 3, DEF_F_MODE | IPC_CREAT | IPC_EXCL);
    /* here would be an error if file by a pathname exists. */
    if(shmid < 0) {
        if(errno != EEXIST) {
            /* if file was prev created */
            printf("SHMEM was created previously.\n");
            return S_SHMEXST;
        }
        else {
            /* try to fetch exact shmem */
            shmid = shmget(shm_key, sizeof(int) * 3, SHM_ZF);
            if(shmid < 0) {
                printf("Can`t fetch memory.\n");
                return S_SHMFTCH;
            }
            arrini = NOTINI;
        }
    }
    /* try to map it into proc IPC space */
    shmarr = (int*)shmat(shmid, NULL, SHM_RDWR);
    if(shmarr == (int*)(-1)) {
        /* can`t alloc mem on IPC segm. */
        printf("Can`t alloc mem into IPC segm.\n");
        return S_IPCADDR;
    }
    /* init arr or increm counters */
    if(arrini == NINIT) {
        shmarr[0] = 1;
        shmarr[1] = 0;
        shmarr[2] = 1;
    }
    else {
        shmarr[0]++;
        shmarr[2]++;
    }
    printf("Prog 1 was spawn %d times\n", shmarr[0]);
    printf("Prog 2  = %d times, total - %d tms.\n", shmarr[1], shmarr[2]);
    if(shmdt(shmarr) < 0) {
        printf("Can`t detach shmem.\n");
        return S_IPCFDUMP;
    }
    return S_DONE;
}
