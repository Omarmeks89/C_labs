# ifndef SCHM_TYPES_H_ENTRY
# define SCHM_TYPES_H_ENTRY

# define DEF_F_MODE 0x000001B6
# define SHM_RDWR 0
# define SHM_ZF 0

# define T_PATHNAME "ex_03_schmem.c"

# ifndef T_INT_ARR_SIZE
#include <stdio.h>
# define T_INT_ARR_SIZE (sizeof(int) * 3)
# endif

enum retcodes {
    S_SHMKEY,
    S_SHMEXST,
    S_SHMFTCH,
    S_IPCADDR,
    S_IPCFDUMP,
} t_retcode;

enum init_flg {
    NINIT = 1,
    NOTINI = 0,
} t_init_flg;


# endif
