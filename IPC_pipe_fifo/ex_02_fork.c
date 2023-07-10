#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

#include "ex_01_types.h"
#include "ex_02_fork_types.h"

void makepipe(int *fd, int *res)
{
    if (pipe(fd) < 0) {
        *res = -1;
        printf("Error: %s\n", strerror(errno));
        exit(E_ERROPEN);
    }
}

int main()
{
    /* we will try separate par from child. */
# if defined(MSG_SIZE) && defined(RESP_MSG_SIZE)
    char str_dest[MSG_SIZE], resp_dest[RESP_MSG_SIZE];
# else
# error message size & responce size not defined.
# endif
    /* size_t = long unsigned int. */
    size_t size;
    pipe_fd fd, ch_fd;
    int res = 0, res_ch = 0;
    pid_t pid;
    
    makepipe(fd, &res);
    makepipe(ch_fd, &res_ch);
    if ((res < 0) || (res_ch < 0)) 
        return E_ERROPEN;
        
    pid = fork();
    if (pid < 0)
        exit(E_ERRFORK);
        
    else if (pid == 0) {
        /* child. we`ll read data. */
        (void)close(fd[STDOUT]);
        size = read(fd[STDIN], str_dest, MSG_SIZE);
        if (size != MSG_SIZE) 
            exit(E_ERREAD);

        printf("Child read data: %s", str_dest);
        if (close(fd[STDIN]) < 0) {
            perror("child cl_fail");
            close(ch_fd[STDOUT]);
            exit(E_ERRCLOSE);
        }
        (void)close(ch_fd[STDIN]);
        size = write(ch_fd[STDOUT], "CH_DONE\n", RESP_MSG_SIZE);
        close(ch_fd[STDOUT]);
        exit(S_DONE);
    }
    
    /* parent proc, we`ll write data. */
    (void)close(fd[STDIN]);
    size = write(fd[STDOUT], "Hello, world!\n", MSG_SIZE);
    if (size != MSG_SIZE) 
        exit(E_ERRWRITE);
        
    (void)close(ch_fd[STDOUT]);
    size = read(ch_fd[STDIN], resp_dest, RESP_MSG_SIZE);
    if (size != RESP_MSG_SIZE) {
        perror("parent fail");
        exit(E_ERREAD);
    }
    printf("Received from child: %s", resp_dest);
    close(fd[STDOUT]);
    close(ch_fd[STDIN]);
    return S_DONE;
}
