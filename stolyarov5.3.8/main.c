#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/* using for declarate wait(). */
#include <sys/wait.h>

int main() {
    int pid;

    pid = fork();
    if (pid == -1) {
        perror("Error in fork");
        /* we use exit() to flush all buffers
         * on exit (to avoid twice printing).*/
        exit(1);
    }
    if (pid == 0) {
        /* child process */
        execlp("ls", "ls", "-l", "-a", "/var", NULL);
        /* trap error in exec failed.*/
        perror("ls");
        exit(1);
    }
    /* parent process.*/
    wait(NULL);
    printf("Done\n");
    return 0;
}
