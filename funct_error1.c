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
 * call_error - request appriopriate error message
 * @cli_frame: data
 * @err_v: value of error
 * Return: correct error message
 */

int call_error(cli_data *cli_frame, int err_v)
{
	char *msg_e;

	switch (err_v)
	{
	case -1:
		msg_e = env_error(cli_frame);
		break;
	case 2:
		if (_strcmp("exit", cli_frame->arguments[0]) == 0)
			msg_e = exit_error(cli_frame);
		else if (_strcmp("cd", cli_frame->arguments[0]) == 0)
			msg_e = cd_error(cli_frame);
		break;
	case 126:
		msg_e = fail_error(cli_frame);
		break;
	case 127:
		msg_e = cmd_not_found(cli_frame);
		break;
	}

	if (msg_e)
	{
		write(STDERR_FILENO, msg_e, _strlen(msg_e));
		free(msg_e);
	}

	cli_frame->status = err_v;
	return (err_v);
}

/**
 * env_error - 'env' error message
 * @cli_frame: data
 * Return: correct error message
 */

char *env_error(cli_data *cli_frame)
{
	int count;
	char *msg_e, *num, *in;

	num = _to_string(cli_frame->count);
	in = ": Can't add or remove from environment\n";
	count = _strlen(cli_frame->arg_v[0]) + _strlen(num);
	count += _strlen(cli_frame->arguments[0]) + _strlen(in) + 4;
	msg_e = malloc(sizeof(char) * (count + 1));
	if (msg_e == 0)
	{
		free(msg_e);
		free(num);
		return (NULL);
	}

	_strcpy(msg_e, cli_frame->arg_v[0]);
	_strcat(msg_e, ": ");
	_strcat(msg_e, num);
	_strcat(msg_e, ": ");
	_strcat(msg_e, cli_frame->arguments[0]);
	_strcat(msg_e, in);
	_strcat(msg_e, "\0");
	free(num);

	return (msg_e);
}

/**
 * fail_error - no access error message for path and denied
 * @cli_frame: data
 * Return: correct error message
 */

char *fail_error(cli_data *cli_frame)
{
	int count;
	char *num, *msg_e, *in;

	in = ": Permission denied\n";

	num = _to_string(cli_frame->count);
	count = _strlen(cli_frame->arg_v[0]) + _strlen(num);
	count += 24 + _strlen(cli_frame->arguments[0]);
	msg_e = malloc((count + 1) * sizeof(char));
	if (msg_e == 0)
	{
		free(msg_e);
		free(num);
		return (NULL);
	}
	_strcpy(msg_e, cli_frame->arg_v[0]);
	_strcat(msg_e, ": ");
	_strcat(msg_e, num);
	_strcat(msg_e, ": ");
	_strcat(msg_e, cli_frame->arguments[0]);
	_strcat(msg_e, in);
	_strcat(msg_e, "\0");
	free(num);
	return (msg_e);
}
