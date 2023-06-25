#include "shell.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

/**
 * handle_builtin - Function that ensures that the arguments
 * matches builtin commands
 * @args: arguments to be checked
 * @num_args: number of arguments
 * Return: false if not a bultin command
 */
bool handle_builtin(char **args, size_t num_args)
{
    if (num_args == 0 || args[0] == NULL)
    {
            return (false);
    }
    if (strcmp(args[0], "exit") == 0)
    {
             exit(0);
    }
    return (false);
}


/**
 * handle_error - A functions that handles error
 * pid: process id returned by fork
 *
 * Return: 0
 */
void handle_error(pid_t pid)
{
        if (pid == -1)
        {
                printf("Error");
                exit(EXIT_FAILURE);
        }
}
/**
 * _itoa - Converts integer value to a string
 * @str: string
 * @value: integer value converted to a string
 *
 * Return: new value
 */
int _itoa(int value, char *str)
{
    int i = 0;
    int sign = 0;

    if (value < 0) {
        sign = 1;
        value = -value;
    }

    do {
        str[i++] = value % 10 + '0';
        value /= 10;
    } while (value > 0);

    if (sign) {
        str[i++] = '-';
    }

    str[i] = '\0';

    _reverse_string(str, i);

    return (i);
}

/**
 * _reverse_string - reverse the string
 * @str: string to be reversed
 * @length: length of string to be reversed
 *
 * Return: 0
 */
void _reverse_string(char *str, int length)
{
    int start = 0;
    int end = length - 1;

    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}
