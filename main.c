#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"
#include "env.h"

#define MAX_INPUT 1024

int main() {
    char input[MAX_INPUT];
    while (1) {
        printf("xsh# ");
        if (!fgets(input, sizeof(input), stdin)) {
            break;
        }
        input[strcspn(input, "\n")] = 0;
        if (strcmp(input, "exit") == 0 || strcmp(input, "quit") == 0) {
            break;
        }
        execute_command(input);
    }
    return 0;
}
