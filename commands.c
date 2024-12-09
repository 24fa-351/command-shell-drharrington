#include "commands.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "env.h"

#define MAX_ARGS 100

void execute_command(char *command) {
    char *args[MAX_ARGS];
    int argc = 0;
    char *token = strtok(command, " ");
    while (token && argc < MAX_ARGS - 1) {
        args[argc++] = token;
        token = strtok(NULL, " ");
    }
    args[argc] = NULL;

    if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL || chdir(args[1]) != 0) {
            perror("cd");
        }
    } else if (strcmp(args[0], "pwd") == 0) {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd))) {
            printf("%s\n", cwd);
        } else {
            perror("pwd");
        }
    } else if (strcmp(args[0], "set") == 0) {
        if (args[1] && args[2]) {
            set_env_var(args[1], args[2]);
        } else {
            fprintf(stderr, "Usage: set <name> <value>\n");
        }
    } else if (strcmp(args[0], "unset") == 0) {
        if (args[1]) {
            unset_env_var(args[1]);
        } else {
            fprintf(stderr, "Usage: unset <name>\n");
        }
    } else if (strcmp(args[0], "echo") == 0) {
        for (int i = 1; i < argc; ++i) {
            char *expanded = replace_vars(args[i]);
            printf("%s ", expanded);
        }
        printf("\n");
    } else {
        pid_t pid = fork();
        if (pid == 0) {
            execvp(args[0], args);
            perror("execvp");
            exit(1);
        } else if (pid > 0) {
            wait(NULL);
        } else {
            perror("fork");
        }
    }
}
