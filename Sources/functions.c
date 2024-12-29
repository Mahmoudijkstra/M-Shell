#include "../Headers/functions.h"
const int MAX_ARGS = 128;
#define HISTORY_FILE "history.txt"

char* get_input() {
    
    size_t buffer_size = 0;
    char* buffer = NULL;
    getline(&buffer, &buffer_size, stdin);
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    return buffer;

}

void save_to_history(char* command) {
    
    FILE* file = fopen(HISTORY_FILE, "a");
    if (!file) {
        perror("Failed to open history file");
        return;
    }
    fprintf(file, "%s\n", command);
    fclose(file);

}

void show_history() {

    FILE* file = fopen(HISTORY_FILE, "r");
    if (!file) {
        perror("Failed to open history file");
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);

}

char** parse_input(char* buffer) {

    int i = 0;
    char** tokens = (char**) malloc(sizeof(char*) * MAX_ARGS);
    char* delim=" ";
    char* token = strtok(buffer, delim);
    while(token != NULL) {
        tokens[i++] = token;
        token = strtok(NULL, delim);
    }
    tokens[i]=NULL;
    return tokens;

}

int handle_builtin(char** args) {
    
    // exit
    if (strcmp(args[0], "exit") == 0) {
        printf("Exiting IM-Shell...\n");
        exit(0);
    } 
    // cd
    else if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            fprintf(stderr, "cd: missing argument\n");
        } else if (chdir(args[1]) != 0) {
            perror("cd failed");
        }
        return 1;
    } 
    // history
    else if (strcmp(args[0], "history") == 0) {
        show_history();
        return 1;
    }
    // clear
    else if (strcmp(args[0], "clear") == 0) {
        system("clear");
        return 1;
    }

    return 0;

}

void execute_command (char** args) {

    pid_t pid = fork();
    if(pid == -1) {
        perror("Fork failed");
        return;
    }
    if (pid == 0) {
        //child process
        char path[200] ="/bin/";
        strcat(path, args[0]);
        args[0]=path;
        execve(args[0], args, NULL);
    }
    else {
        //parent process
        wait(NULL);
        //printf("Done with execve\n");
    }

}
void free_input(char* buffer, char** args) {

    free(buffer);
    free(args);

}