#include "shell.h"

/**
 * _strlen - counts the length of a string
 * @s: String to be counted
 * Description: this program counts the length of a string
 * by counting each character until the null character
 * is encounted
 *
 * Return: the number of characters in string
 */
int _strlen(char *s)
{
        int count = 0;

        while (*s != '\0')
        {
                count++;
                s++;
        }
        return (count);
}
