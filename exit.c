#include "shell.h"

/**
 * main - Entry point for the simple shell program.
 *
 * This function initializes variables for storing the input line, its length,
 * and the return value of the last executed command. It then enters a main
 * loop where it repeatedly prompts the user for input, reads the input from
 * standard input, handles the input line by executing it as a command, and
 * frees the allocated memory for the input line. The loop continues until the
 * user enters the end-of-file character (Ctrl+D).
 *
 * Upon exiting the loop, this function frees the allocated environment
 * variables and returns the exit status of the last executed command.
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
