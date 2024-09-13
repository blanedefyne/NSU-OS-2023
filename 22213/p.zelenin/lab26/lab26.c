#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    FILE* fin = popen("make run", "w");
    if (fin == NULL) {
        perror("popen() caused an error ");
        exit(EXIT_FAILURE);
    }

    char* text = "Ranetki";
    fprintf(fin, "%s\n", text);

    if (pclose(fin) == -1) {
        perror("pclose() caused an error ");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);

}