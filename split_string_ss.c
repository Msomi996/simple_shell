#include "shell.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * main - Entry point
 *
 * Return: Always 0
 */
int main(void)
{
        int s;
        int no_of_words;
        char **words;
        char *test_strings[] = {
                "Hello, my name is HL. This is our shell program,",
                "HL ",
                " Hello",
                " delimeter x ",
                "C",
                "Simple shell",
        };

        words = split_string(test_strings[5], " ,.", &no_of_words);
        for (s = 0; s < words[s]; s++)
        {
                write(STDOUT_FILENO, words[s], _strlen(words[s]));
                write(STDOUT_FILENO, "\n", 1);
        }
        free_vector(words, no_of_words);

        return (0);
}
