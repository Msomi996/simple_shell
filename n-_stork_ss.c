#include "shell.h"
#include <stdbool.h>
#include <stdlib.h>

/**
 * split_string - Splits a string into individual words based on a delimiter
 * @str: The string to be split
 * @delimiter: The delimiter used to split the string
 * @count: Pointer to store the number of words found
 *
 * Returns: An array of strings containing the split words
 */
char **split_string(const char *str, const char *delimiter, size_t *count)
{
    if (str == NULL || delimiter == NULL)
        return (NULL);

    size_t words_count = 0;
    const char *str_ptr = str;

    /* Count the number of words */
    while (*str_ptr != '\0')
    {
        /* Skip leading delimiters */
        while (*str_ptr != '\0' && strchr(delimiter, *str_ptr) != NULL)
            str_ptr++;

        if (*str_ptr != '\0')
        {
            words_count++;
            // Skip the word
            while (*str_ptr != '\0' && strchr(delimiter, *str_ptr) == NULL)
                str_ptr++;
        }
    }

    *count = words_count;

    /* Allocate memory for the array of strings */
    char **words = malloc((words_count + 1) * sizeof(char *));
    if (words == NULL)
        return (NULL);

    words_count = 0;
    str_ptr = str;

    /* Split the string into words */
    while (*str_ptr != '\0')
    {
        /* Skip leading delimiters */
        while (*str_ptr != '\0' && strchr(delimiter, *str_ptr) != NULL)
            str_ptr++;

        if (*str_ptr != '\0')
        {
            const char *word_start = str_ptr;
            /* Find the end of the word */
            while (*str_ptr != '\0' && strchr(delimiter, *str_ptr) == NULL)
                str_ptr++;

            size_t word_length = str_ptr - word_start;

            /* Allocate memory for the word and copy it */
            words[words_count] = malloc((word_length + 1) * sizeof(char));
            if (words[words_count] == NULL)
            {
                /* Free the previously allocated memory */
                for (size_t i = 0; i < words_count; i++)
                    free(words[i]);
                free(words);
                return (NULL);
            }

            strncpy(words[words_count], word_start, word_length);
            words[words_count][word_length] = '\0';

            words_count++;
        }
    }

    words[words_count] = NULL; /* Set the last element to NULL as a marker */

    return (words);
}
