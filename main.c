#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

const int MAX_ARGS = 128;

// Read input from the user
char* get_input() {
    size_t buffer_size = 0;
    char* buffer = NULL;
    getline(&buffer, &buffer_size, stdin);

    // Remove trailing newline if it exists
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    return buffer;
}

// Parse the input into arguments
char** parse_input(char* buffer) {
    int i = 0;
    char** tokens = (char**) malloc(sizeof(char*) * MAX_ARGS);
    char* delim = " ";
    char* token = strtok(buffer, delim);
    while (token != NULL) {
        tokens[i] = token;
        token = strtok(NULL, delim);
        i++;
    }
    tokens[i] = NULL;
    return tokens;
}

// Execute the command
int execute_command(char** args) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("Fork failed");
        return 1;
    }
    if (pid == 0) {
        // Child process
        char path[200] = "/bin/";
        strcat(path, args[0]);

        execve(path, args, NULL);
        perror("execve failed"); // If execve fails
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        //waitpid(pid, &status, 0);
        wait(NULL);
        printf("Done with execve\n");
    }
    return 1;
}

// Main shell loop
int main(void) {
    int status = 1;
    char* buffer;
    char** args;

    while (status) {
        printf("M-Shell> ");
        buffer = get_input();
        args = parse_input(buffer);
        if (args[0] != NULL) { // Ensure command is not empty
            status = execute_command(args);
        }
        free(buffer);
        free(args);
    }
    return 0;
}
