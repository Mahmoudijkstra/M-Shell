#include "../Headers/functions.h"

int main (void) {

    char* buffer;
    char** args;

    while (1) {
        printf("IM-Shell>");
        fflush(stdout);
        buffer = get_input();
        save_to_history(buffer);
        args = parse_input(buffer);
        if (handle_builtin(args)) continue;
        execute_command(args);
        free_input(buffer, args);
    }
    return 0;

};
