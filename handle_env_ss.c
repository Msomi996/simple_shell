#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

extern char **environ;

/**
 * env_builtin - Prints the current working environment
 *
 * Return: 0
 */
void env_builtin(int)
{
    int i = 0;
    while (environ[i] != NULL)
    {
        write(STDOUT_FILENO, environ[i], strlen(environ[i]));
        write(STDOUT_FILENO, "\n", 1);
        i++;
    }
}

/**
 * main - Super simple shell program that runs shell commands
 * when this program is compiled and executedc reates a  child process
 * and runs the getline system call and reads the imput from stdin.
 * This imput should be the path to an executable
 *
 * Returns: Always 0
 */
int main(int argc, char *argv[], char **env)
{
    char *buff = NULL, *prompt = "$ ";
    size_t buff_size = 0;
    ssize_t bytes;
    pid_t wpid;
    int wstatus;
    bool from_pipe = false;
    char **args;
    char *fullpath;
    size_t no_of_args;
    struct stat statbuf;
 while (1 && !from_pipe)
    {
        /* check if data is piped into program or entered from terminal */
        if (isatty(STDIN_FILENO) == 0)
            from_pipe = true;

        /* print the prompt sign '$ ' on the terminal */
        write(STDOUT_FILENO, prompt, 2);

        /* Read data from standard input */
        bytes = getline(&buff, &buff_size, stdin);
        if (bytes == -1)
        {
            perror("Error (getline)");
            free(buff); /* If getline fails, free memory */
            exit(EXIT_FAILURE);
        }
        /* Replace the character with a null terminatorl */
        if (buff[bytes - 1] == '\n')
            buff[bytes - 1] = '\0';

        /* Split the argument string into individual words */
        args = split_string(buff, " ", &no_of_args);

        /* Handle built-in commands */
        if (strcmp(args[0], "env") == 0)
        {
            env_builtin();
            free_vector(args, no_of_args);
            continue;
        }
        else if (handle_builtin(args, no_of_args))
        {
            free_vector(args, no_of_args);
            continue;
        }

        /* Check if executable exists */
        if (!check_file_status(args[0], &statbuf))
        {
            /* Look for executables in paths */
            fullpath = check_file_in_path(args[0], &statbuf);
            if (!fullpath)
            {
		    perror("Error (file status)");
		    free_vector(args, no_of_args);
		    continue;
            }
            else
            {
                /* Replace the first argument with the full path if exist */
                free(args[0]);
                args[0] = fullpath;
            }
        }

        /* Create a child process and use it to execute the command */
        wpid = fork();
        if (wpid == -1) /* If fork fails*/
        {
            perror("Error (fork)");
            exit(EXIT_FAILURE);
        }
        if (wpid == 0) /* child process */
            _execute(buff, &statbuf, env);

        /* Parent process should wait for the child process to finish */
        if (waitpid(wpid, &wstatus, 0) == -1)
        {
            perror("Error (waitpid)");
            exit(EXIT_FAILURE);
        }
        free_vector(args, no_of_args);
    }

    free(buff);
    return (0);
}

/**executable file that exists
 * _execute - Executable that needs to be checked if it exists
 * @struct: structure
 * @statbuf: vatiable
 * @envp: environment
 *
 * Return:
 */
int _execute(char *arguments, struct stat *statbuf, char **envp)
{
    int argc;
    char **argv;

    argv = split_string(arguments, " ", &argc);

    /* Check if executable file exists */
    if (!check_file_status(argv[0], statbuf))
    {
        perror("Error (file status)");
        exit(EXIT_FAILURE);
    }

    execve(argv[0], argv, envp);

    /* Free the dynamically allocated argv array */
    free_vector(argv, argc);

    /* If execve failed */
    perror("Error (execve)");
    exit(EXIT_FAILURE);
}
/**
 * check_file_status - a function that checks the status of path
 * @pathname: path to be checked
 * @statbuf: structure
 *
 * Return: check if path exists, if it does print true,
 * if it doesnt, false
 */
bool check_file_status(char *pathname, struct stat *statbuf)
{
    int stat_return;

    stat_return = stat(pathname, statbuf);
    if (stat_return == 0)
        return (true);

    return (false);
}
