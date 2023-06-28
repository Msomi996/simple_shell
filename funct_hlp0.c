#include "shell.h"

/**
 * help_info - 'help' help information
 * Return: 0 - null
 */

void help_info(void)
{
	char *text = "help: help [-dms] [pattern ...]\n\t";

	write(STDOUT_FILENO, text, _strlen(text));
	text = "You can view information for built-ins commands.\n ";
	write(STDOUT_FILENO, text, _strlen(text));
	text = "You can view brief summaries of bash built-ins.\n";
	write(STDOUT_FILENO, text, _strlen(text));
}

/**
 * alias_help_info - 'alias' help information
 * Return: 0 - null
 */

void alias_help_info(void)
{
	char *text = "alias: alias [name[='value'] ...]\n\t";

	write(STDOUT_FILENO, text, _strlen(text));
	text = "You can either define or display aliases.\n ";
	write(STDOUT_FILENO, text, _strlen(text));
}

/**
 * cd_help_info - 'cd' help information
 * Return: 0 - null
 */

void cd_help_info(void)
{
	char *text = "cd: usage cd [-L|[-P [-e]] [-@]] [dir]\n\t";

	write(STDOUT_FILENO, text, _strlen(text));
	text = "Change current working directory to specified location\n ";
	write(STDOUT_FILENO, text, _strlen(text));
}
