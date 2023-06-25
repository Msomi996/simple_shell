#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

/**
 * main - Super simple shell program that runs shell commands.
 * When this program is compiled and executed, it creates a child process
 * and runs the getline system call to read the input from stdin.
 * This input should be the path to an executable.
 *
 * Returns: Always 0.
 */
int main(int argc, char *argv[], char **env)
{
    char *buff = NULL, *prompt = "$ ";
    size_t buff_size = 0;
    ssize_t bytes;
    bool from_pipe = false;
    char **args;
    size_t no_of_args;
    struct stat statbuf;

    while (1)
    {
        /* Check if data is piped into the program or entered from the terminal */
        if (isatty(STDIN_FILENO) == 0)
            from_pipe = true;

        /* Print the prompt sign '$' on the terminal */
        write(STDOUT_FILENO, prompt, 2);

        /* Read data from standard input */
        bytes = getline(&buff, &buff_size, stdin);
        if (bytes == -1)
        {
            perror("Error (getline)");
            free(buff); /* If getline fails, free memory */
            exit(EXIT_FAILURE);
        }

        /* Replace the newline character with a null terminator */
        if (buff[bytes - 1] == '\n')
            buff[bytes - 1] = '\0';

        /* Split the argument string into individual words */
        args = split_string(buff, " ", &no_of_args);

        /* Handle built-in commands that are entered */
        if (handle_builtin(args, no_of_args))
        {
            free_vector(args, no_of_args);
            continue;
        }

        /* Check if the executable exists in the PATH */
        char *fullpath = find_executable(args[0], env);
        if (fullpath == NULL)
        {
            fprintf(stderr, "Command not found: %s\n", args[0]);
            free_vector(args, no_of_args);
            continue;
        }

        /* Create a child process and use it to execute the command */
        pid_t wpid = fork();
        if (wpid == -1) /* If fork fails */
        {
            perror("Error (fork)");
            exit(EXIT_FAILURE);
        }
        if (wpid == 0) /* Child process */
            _execute(fullpath, args, env);

        /* Parent process should wait for the child process to finish */
        int wstatus;
        if (waitpid(wpid, &wstatus, 0) == -1)
        {
            perror("Error (waitpid)");
            exit(EXIT_FAILURE);
        }

        free(fullpath);
        free_vector(args, no_of_args);
    }

    free(buff);
    return (0);
}

void _execute(char *path, char **args, char **envp)
{
    execve(path, args, envp);

    /* If execve failed */
    perror("Error (execve)");
    exit(EXIT_FAILURE);
}

char *find_executable(char *command, char **envp)
{
    /* Get the value of the PATH environment variable */
    char *path = getenv("PATH");
    if (path == NULL)
        return NULL;

    char *dir;
    char *token = strtok(path, ":");

    while (token != NULL)
    {
        /* Construct the full path by concatenating the directory and the command */
        char *fullpath = str_concat(token, "/");
        fullpath = str_concat(fullpath, command);

        /* Check if the full path exists and is executable */
        struct stat statbuf;
        if (check_file_status(fullpath, &statbuf))
            return fullpath;

        free(fullpath);

        /* Get the next directory in the PATH */
        token = strtok(NULL, ":");
    }
    return (NULL);
}
