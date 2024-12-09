#ifndef ENV_H
#define ENV_H

char *find_env_var(const char *name);
void set_env_var(const char *name, const char *value);
void unset_env_var(const char *name);
char *replace_vars(char *input);

#endif  // ENV_H
