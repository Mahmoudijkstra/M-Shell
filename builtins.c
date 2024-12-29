#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "builtins.h"

int handle_builtin(char **args) {
    if (strcmp(args[0], "exit") == 0) {
        printf("Exiting myshell...\n");
        exit(0);
    }

    if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            fprintf(stderr, "cd: expected argument\n");
        } else {
            if (chdir(args[1]) != 0) {
                perror("cd failed");
            }
        }
        return 1;
    }

    return 0;
}
