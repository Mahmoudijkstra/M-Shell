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

int execute_command (char** args) {

    pid_t pid = fork();
    if(pid == -1) {
        perror("Fork failed");
        return 1;
    }
    if (pid == 0) {
        //child process
        //char *argv[] = {"/bin/ls", "-l", NULL};  
        //execve(argv[0], argv, NULL);
        char path[200] ="/bin/";
        strcat(path, args[0]);
        args[0]=path;
        execve(args[0], args, NULL);
    }
    else {
        //parent process
        wait(NULL);
        printf("Done with execve\n");
    }
    return 1;
}

int main (void) {

    int status = 1;
    char* buffer;
    char** args;
    while (status) {
        printf("M-Shell>");
        buffer = get_input();
        args = parse_input(buffer);
        status = execute_command(args);
        free(buffer);
        free(args);
    }
    
    return 0;

}
