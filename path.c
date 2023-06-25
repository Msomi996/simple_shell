#include "shell.h"
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv, char **env)
{
        size_t sz;
        int i;

        char *path = _getenv("PATH");
        write(STDOUT_FILENO, path, _strlen(path));
        write(STDOUT_FILENO, "\n", 1);

        char **paths = split_string(path, ":", &sz);
        for (i = 0; paths[i]; i++)
        {
                char index_str[10];
                int index_len = _itoa(i, index_str);
                write(STDOUT_FILENO, index_str, index_len);
                write(STDOUT_FILENO, " - ", 3);
                write(STDOUT_FILENO, paths[i], _strlen(paths[i]));
                write(STDOUT_FILENO, "\n", 1);
        }
        free_vector(paths,sz);
        return (0);
}
