#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "executor.h"
#include "builtins.h"

#define MAX_CMD_LEN 1024
#define MAX_ARGS 64

int main()
{
    char cmd[MAX_CMD_LEN];
    char *args[MAX_ARGS];

   while (1)
    {
        printf("Ilyes-Mahmoud> ");
        fflush(stdout); 

        if (fgets(cmd, MAX_CMD_LEN, stdin) == NULL) 
        {
            perror("fgets failed");
            exit(1);
        }

        cmd[strcspn(cmd, "\n")] = '\0';

        // Parse command
        parse_command(cmd, args);
        
        // Handle built-in commands
        if (args[0] == NULL || handle_builtin(args))
            continue;

        execute_command(args);
    }

    return 0;
}
