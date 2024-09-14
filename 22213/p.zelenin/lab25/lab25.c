#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define BUF_LEN 10

int main() {
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1) {
        perror("pipe() caused an error ");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    switch(pid) 
    {
    case -1:
        close(fd[0]);
        close(fd[1]);
        perror("fork() caused an error ");
        exit(EXIT_FAILURE);
    case 0:
        close(fd[0]);
        char bufTemp[BUF_LEN];
        ssize_t bytesTemp, j;
        while ((bytesTemp = read(STDIN_FILENO, bufTemp, BUF_LEN)) > 0) {
            if (write(fd[1], bufTemp, bytesTemp) == -1) {
                perror("writing from child caused an error ");
                exit(EXIT_FAILURE);
            }
            for (j = 0; j < bytesTemp; ++j) {
                if (bufTemp[j] == '\n') {
                    close(fd[1]);
                    exit(EXIT_SUCCESS);
                }
            }
        }
        if (bytesTemp < 0) {
            close(fd[1]);
            perror("child's read() caused an error ");
            exit(EXIT_FAILURE);
        }
        
        exit(EXIT_SUCCESS);

    default:
        close(fd[1]);
        ssize_t bytesRead, i;
        char buf[BUF_LEN];
        while ((bytesRead = read(fd[0], buf, BUF_LEN)) > 0) {
            for (i = 0; i < bytesRead; ++i) {
                buf[i] = toupper(buf[i]);
            }
            if (write(STDOUT_FILENO, buf, bytesRead) == -1) {
                perror("writing from parent caused an error ");
                exit(EXIT_FAILURE);
            }
        }
        close(fd[0]);
        if (bytesRead < 0) {
            perror("parent's read() caused an error ");
            exit(EXIT_FAILURE);
        }

        exit(EXIT_SUCCESS);
    }    

}