#include "shell.h"

/**
 * shellby_exit - exits the simple shell
 * @args: arguments passed to the exit command
 * @front: pointer to the beginning of the original input string
 *
 * Return: Always returns 0, to indicate that the shell should exit
 */
int shellby_exit(char **args, char **front)
{
	(void)args;
	(void)front;
	return (0);
}
