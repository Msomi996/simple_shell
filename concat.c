#include "shell.h"
#include <stdlib.h>
#include <stdarg.h>

/**
 * *str_concat - a function that concacerates a string
 * @s1: first string
 * @s2: second string
 *
 * Return: concacerated string
 */
char *str_concat(char *s1, char *s2)
{
        int c, u = 0;
        int len1, len2;
        char *joined;

        /*
         * if string is NULL or empty, length of array should be 1
         * we must first check for NULL before any other check
         * else we would get segmentation error if string happens to be NULL
         */
        if (s1 == NULL || s1[0] == '\0')
                len1 = 1;
        else
                for (len1 = 0; s1[len1]; len1++) /* Count length of string 1 */
                        continue;
        if (s2 == NULL || s2[0] == '\0')
                len2 = 1;
        else
                for (len2 = 0; s2[len2]; len2++) /* count length of string 2 */
                        continue;
        /* Allocates memoryy for new array, including null terminator */
        joined = malloc((sizeof(char) * (len1 + len2)) + 1);

        /* If allocation fails */
        if (joined == 0)
                return (NULL);

        for (int i = 0; i < len1; i++)
                joined[i] = s1[i];
        for  (int i = 0; i < len2; i++)
                joined[i] = s2[i];

        joined[len1 + len2] = '\0';

        return (joined);
}
