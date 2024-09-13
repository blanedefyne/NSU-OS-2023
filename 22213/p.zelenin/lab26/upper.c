#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define BUF_LEN 5

int main() {

    char buf[BUF_LEN];
    ssize_t readBytes, i;

    while ((readBytes = read(STDIN_FILENO, buf, BUF_LEN)) > 0) {
        for (i = 0; i < readBytes; ++i) {
            buf[i] = toupper(buf[i]);
        }
        if (write(STDOUT_FILENO, buf, readBytes) == -1) {
            perror("write() caused an error ");
            exit(EXIT_FAILURE);
        }
        for (i = 0; i < readBytes; ++i) {
            if (buf[i] == '\n') {
                exit(EXIT_SUCCESS);
            }
        }
    }

    if (readBytes < 0) {
            perror("read() caused an error ");
            exit(EXIT_FAILURE);
        }

}