#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

/**
 * check_env_v - evaluates for env variables
 * @var_e: env var name
 * @str: name to evaluate
 * Return: len if equal, 0 if fail
 */

int check_env_v(const char *var_e, const char *str)
{
	int idx;

	for (idx = 0; var_e[idx] != '='; idx++)
	{
		if (var_e[idx] != str[idx])
		{
			return (0);
		}
	}
	return (idx + 1);
}

/**
 * _env - returns env var
 * @cli_frame: data
 * Return: 1 on success
 */

int _env(cli_data *cli_frame)
{
	int idx, idy;

	for (idx = 0; cli_frame->_environ[idx]; idx++)
	{
		idy = 0;
		while (cli_frame->_environ[idx][idy])
			idy++;

		write(STDOUT_FILENO, cli_frame->_environ[idx], idy);
		write(STDOUT_FILENO, "\n", 1);
	}
	cli_frame->status = 0;

	return (1);
}

/**
 * _getenv - gethers correct env variable
 * @cmd_name: name to evaluate
 * @_environ: env variable
 * Return: env var if found, NULL on fail
 */

char *_getenv(const char *cmd_name, char **_environ)
{
	char *str;
	int idx, count;

	str = NULL;
	count = 0;

	for (idx = 0; _environ[idx]; idx++)
	{
		count = check_env_v(_environ[idx], cmd_name);
		if (count)
		{
			str = _environ[idx];
			break;
		}
	}
	return (str + count);
}
