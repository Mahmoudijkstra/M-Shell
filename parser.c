#include <string.h>
#include "parser.h"

#define MAX_ARGS 64

void parse_command(char *cmd, char **args)
{
    char *token;
    int i = 0;

    token = strtok(cmd, " \n");
    while (token != NULL && i < MAX_ARGS - 1)
    {
        args[i++] = token;
        token = strtok(NULL, " \n");
    }
    args[i] = NULL;
}
