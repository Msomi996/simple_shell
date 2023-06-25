#ifndef SHELL_H
#define SHELL_H

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait>

int main(int argc, char *argv[], char **env);
int _execute(char *arguments, struct stat *statbuf, char **envp);
bool check_file_status(char *pathname, struct stat *statbuf);
void handle_error(pid_t pid);
char **split_string(char *str, char *separators, int *word_count);
int _itoa(int value, char *str);
void _reverse_string(char *str, int length);
char *str_concat(char *s1, char *s2);
int _strlen(char *s);
void env_builtin(int);
extern char **environ;
void handle_en(char **env_args,size_t no_of_args);
void _print_env(void);
int main(void);


#endif
