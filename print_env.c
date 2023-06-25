#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

extern char **environ;

/**
 * handle_env - handles the env built in command
 * @env_args: arguments fr the environment command
 * @no_of_args: Number of arguments passed
 * Return: Nothing
 */
void handle_en(char **env_args,size_t no_of_args)
{
        if (!env_args[1])
                _print_env();

        free_vector(env_args, no_of_args);
}
/**
 * print_env - prints the environment variable
 * Return: Nothing
 */
void _print_env(void)
{
        char **env = environ;

        while (*env != NULL)
        {
        size_t len = strlen(*env);
        write(STDOUT_FILENO, *env, len);
        write(STDOUT_FILENO, "\n", 1);
        env++;
        }
}
