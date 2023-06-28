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
 * bltn_env_help - built-in env help
 * Return: 0 - null
 */

void bltn_env_help(void)
{
	char *text = "env: env [OPTION] [-]";

	write(STDOUT_FILENO, text, _strlen(text));
	text = "[NAME=VALUE] [COMMAND [ARG]]\n\t";
	write(STDOUT_FILENO, text, _strlen(text));
	text = "Print the enviroment of the shell.\n";
	write(STDOUT_FILENO, text, _strlen(text));

}

/**
 * cmp_env_help - etting env help info
 * Return: 0 - null
 */

void cmp_env_help(void)
{

	char *text = "setenv: usage setenv (const char *name, ";

	write(STDOUT_FILENO, text, _strlen(text));
	text = "const char *value, int overwrite)\n";
	write(STDOUT_FILENO, text, _strlen(text));
}

/**
 * rm_env_help - non-set env help info
 * Return: 0 - null
 */

void rm_env_help(void)
{
	char *text = "unsetenv: usage unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, text, _strlen(text));
	text = "Removes an entire entry from environment\n";
	write(STDOUT_FILENO, text, _strlen(text));
}


/**
 * builtin_help - first request for 'help' builtin
 * Return: 0 null
 */

void builtin_help(void)
{
	char *text = ": ) bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, text, _strlen(text));
	text = "The commands are internally defined.";
	write(STDOUT_FILENO, text, _strlen(text));
	text = "Enter 'help' to see command list";
	write(STDOUT_FILENO, text, _strlen(text));
	text = "Enter 'input name' to see more";
	write(STDOUT_FILENO, text, _strlen(text));
	text = " about function 'name'.\n\n ";
	write(STDOUT_FILENO, text, _strlen(text));
	text = " alias: alias [name[='value'] ...]\n";
	write(STDOUT_FILENO, text, _strlen(text));
	text = " cd: usage cd [-L|[-P [-e]] [-@]] [dir]";
	write(STDOUT_FILENO, text, _strlen(text));
	text = "[dir]\n";
	write(STDOUT_FILENO, text, _strlen(text));
	text = "exit: usage exit [n]\n  ";
	write(STDOUT_FILENO, text, _strlen(text));
	text = "env: usage env [OPTION] [-][NAME=VALUE] [COMMAND [ARG]]\n";
	write(STDOUT_FILENO, text, _strlen(text));
	text = "  setenv: usage setenv [var name] [value]\n";
	write(STDOUT_FILENO, text, _strlen(text));
	text = "  unsetenv: usage unsetenv [var name]\n";
	write(STDOUT_FILENO, text, _strlen(text));
}

/**
 * bltn_exit_help - the built-in exit help info
 * Return: 0 - null
 */
void bltn_exit_help(void)
{
	char *text = "exit: usage exit [n]\n";

	write(STDOUT_FILENO, text, _strlen(text));
	text = " Exits\n";
	write(STDOUT_FILENO, text, _strlen(text));
	text = "Exits the shell script with the sxit status specified by n.";
	write(STDOUT_FILENO, text, _strlen(text));
	text = " If you omit n, the exit status";
	write(STDOUT_FILENO, text, _strlen(text));
	text = "is the status of the last command executed\n";
	write(STDOUT_FILENO, text, _strlen(text));
}
