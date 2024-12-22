#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

char* get_input() {
    
    size_t buffer_size = 0;
    char* buffer = NULL;
    getline(&buffer, &buffer_size, stdin);
    return buffer;

}

int main (void) {

    char* buffer;
    printf("M-Shell>");
    buffer = get_input();
    free(buffer);
    return 0;

}