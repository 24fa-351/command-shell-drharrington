#include "env.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VARS 100

typedef struct {
    char *name;
    char *value;
} EnvVar;

static EnvVar env_vars[MAX_VARS];
static int env_var_count = 0;

char *find_env_var(const char *name) {
    for (int i = 0; i < env_var_count; ++i) {
        if (strcmp(env_vars[i].name, name) == 0) {
            return env_vars[i].value;
        }
    }
    return NULL;
}

void set_env_var(const char *name, const char *value) {
    char *existing_value = find_env_var(name);
    if (existing_value) {
        free(existing_value);
    } else {
        env_vars[env_var_count].name = strdup(name);
        env_var_count++;
    }
    env_vars[env_var_count - 1].value = strdup(value);
}

void unset_env_var(const char *name) {
    for (int i = 0; i < env_var_count; ++i) {
        if (strcmp(env_vars[i].name, name) == 0) {
            free(env_vars[i].name);
            free(env_vars[i].value);
            env_vars[i] = env_vars[--env_var_count];
            return;
        }
    }
}

char *replace_vars(char *input) {
    static char buffer[1024];
    char *output = buffer;
    while (*input) {
        if (*input == '$' && *(input + 1)) {
            char var_name[1024];
            input++;
            int i = 0;
            while (*input && (isalnum(*input) || *input == '_') && i < 1023) {
                var_name[i++] = *input++;
            }
            var_name[i] = '\0';
            char *value = find_env_var(var_name);
            if (value) {
                strcpy(output, value);
                output += strlen(value);
            }
        } else {
            *output++ = *input++;
        }
    }
    *output = '\0';
    return buffer;
}
