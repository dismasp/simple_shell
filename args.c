#include "shell.h"

/**
 * main - Entry point for the shell program
 *
 * This function starts the shell and enters a loop to read input from the
 * user, parse the input into command and argument tokens, and execute the
 * commands. It also frees allocated memory and environment variables when
 * the user exits the shell.
 *
 * Return: The exit status of the last executed command.
 */

int main(void)
{
char *line = NULL;  /* Pointer to hold input line */
size_t len = 0; /* Length of input line */
ssize_t read = 0;   /* Number of characters read from input line */
int exe_ret = 0;/* Return value of the last executed command */

/* Main loop */
while (1)
	{
	printf("$ ");   /* Print shell prompt */
	read = _getline(&line, &len, stdin);  /* Read input line */
if (read == -1)
	{   /* Handle error reading input */
	perror("read");
	continue;
	}
else if (read == 0)
	{ /* Handle end-of-file (Ctrl+D) */
	break;
	}
handle_line(&line, read);   /* Handle input line */
free(line); /* Free allocated memory for input line */
line = NULL;
len = 0;
}

free_env(); /* Free allocated environment variables */
return (exe_ret); /* Return exit status */
}
