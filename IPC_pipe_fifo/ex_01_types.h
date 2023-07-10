# ifndef EX_TYPES_H_ENTRY
# define EX_TYPES_H_ENTRY

# include <stdio.h>

# define CALC_ITEM_SIZE(T) (sizeof(T))

typedef int pipe_fd[2];
typedef enum io_buffers io_buff;
typedef enum ex_codes errcodes;

# endif
