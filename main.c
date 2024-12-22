#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

const int MAX_ARGS = 128;


char* get_input() {
    
    size_t buffer_size = 0;
    char* buffer = NULL;
    getline(&buffer, &buffer_size, stdin);
    return buffer;

}

char** parse_input(char* buffer) {

    int i = 0;
    char** tokens = (char**) malloc(sizeof(char*) * MAX_ARGS);
    char* delim=" ";
    char* token = strtok(buffer, delim);
    while(token != NULL) {
        tokens[i] = token;
        token = strtok(NULL, delim);
        i++;
    }
    tokens[i]=NULL;
    return tokens;

}


int main (void) {

    char* buffer;
    char** args;
    printf("M-Shell>");
    buffer = get_input();
    args = parse_input(buffer);
    free(buffer);
    free(args);
    return 0;

}