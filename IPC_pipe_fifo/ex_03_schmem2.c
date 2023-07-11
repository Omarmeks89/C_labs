
#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "ex_03_schm_types.h"
#include "ex_01_types.h"


int main()
{
	int *shmarr, arrini, shmid;
	char pathname[] = T_PATHNAME;
	key_t schm_key;

	arrini = NINIT;
	schm_key = ftok(pathname, 0);
	if (schm_key < 0) {
		printf("KEY_ERR: %s\n", strerror(errno));
		return S_SHMKEY;
	}
	shmid = shmget(schm_key, T_INT_ARR_SIZE, DEF_F_MODE | IPC_CREAT | IPC_EXCL);
	if (shmid < 0) {
		/* shmem exists */
		if (errno != EEXIST) {
			printf("SHMEM EXISTS. ERR: %s\n", strerror(errno));
			return S_SHMEXST;
		}
		else {
			shmid = shmget(schm_key, T_INT_ARR_SIZE, SHM_ZF);
			if (shmid < 0) {
				printf("MEMERROR: %s\n", strerror(errno));
				return S_SHMFTCH;
			}
			arrini = NOTINI;
		}
	}
	shmarr = (int*)shmat(shmid, NULL, SHM_RDWR);
	if (shmarr == (int*)(-1)) {
		printf("IPC ALLOC ERR: %s\n", strerror(errno));
		return S_IPCADDR;
	}
	if (arrini == NINIT) {
		shmarr[0] = 1;
		shmarr[1] = 0;
		shmarr[2] = 1;
	}
	else {
		shmarr[1]++;
		shmarr[2]++;
	}
        printf("Prog 1 was spawn %d times\n", shmarr[0]);
        printf("Prog 2  = %d times, total - %d tms.\n", shmarr[1], shmarr[2]);
        if(shmdt(shmarr) < 0) {
    		printf("Can`t detach shmem. %s\n", strerror(errno));
        	return S_IPCFDUMP;
        }
        return S_DONE;
}
