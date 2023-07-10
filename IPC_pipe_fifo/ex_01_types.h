# ifndef EX_TYPES_H_ENTRY
# define EX_TYPES_H_ENTRY

# include <stdio.h>

# define CALC_ITEM_SIZE(T) (sizeof(T))

typedef int pipe_fd[2];

enum io_buffers {
	STDIN = 0,
	STDOUT = 1,
	STDERR = 2,
} t_io_buffers;

enum ex_codes {
	S_DONE = 0,
	E_ERROPEN = 1,
	E_ERRCLOSE = 2,
	E_ERREAD = 3,
	E_ERRWRITE = 4,
	E_ERRCREAT = 5,
	E_ERRFORK = 6,
} err_codes;

# endif
