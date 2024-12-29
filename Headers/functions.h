#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

char* get_input();
void save_to_history(char* command);
void show_history();
char** parse_input(char* buffer);
int handle_builtin(char** args);
void execute_command (char** args);
void free_input(char* buffer, char** args);

#endif // FUNCTIONS_H_INCLUDED
