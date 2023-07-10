#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#include "ex_01_types.h"

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
} err_codes;

int main()
{
    /* func, that repr pipe creation. */
    pipe_fd fd;
    char str[] = "Hello, world!\n";
    size_t str_size = CALC_ITEM_SIZE(str), size;
    
    /* 15 bcs we have 0 term at the end of orig str. */
    char str_dest[str_size];
    
    if (pipe(fd) < 0) {
        printf("PIPE wasn`t created.\n");
        return E_ERRCREAT;
    }
    /* fd[1] == stdout. */ 
    size = write(fd[STDOUT], str, str_size);
    if (size != str_size) {
        printf("Err on write call.\n");
        return E_ERRWRITE;
    }
    /* fd[0] means stdin. */
    size = read(fd[STDIN], str_dest, str_size);
    if (size != str_size) {
        printf("Err on read call.\n");
        return E_ERREAD;
    }
    printf("Wae succ readed: %s", str_dest);
    if (close(fd[STDOUT]) < 0) {
        printf("Err on close stdout fd.\n");
        return E_ERRCLOSE;
    }
    if (close(fd[STDIN]) < 0) {
        printf("Err on close stdin fd.\n");
        return E_ERRCLOSE;
    }
    return S_DONE;
}
