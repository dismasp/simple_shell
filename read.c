#include "shell.h"

/**
 * shell_getline - read input from user
 * Return: input string from user
 */
char *shell_getline(void)
{
char *line = NULL;
ssize_t bufsize = 0;
getline(&line, &bufsize, stdin);
return (line);
}

/**
 * main - start of shell program
 * Return: always 0
 */
int main(void)
{
char *line = NULL;

while (1)
{
printf("$ ");
line = shell_getline();

if (_strcmp(line, "exit\n") == 0)
{
free(line);
exit(EXIT_SUCCESS);
}

/* Execute other commands here */

free(line);
}

return (0);
}
