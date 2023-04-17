#include "shell.h"
#include <stdio.h>
#include <string.h>

#define MAX_COMMAND_LEN 256
#define MAX_ARGS 16

/*
 * @file interprete.c
 * @print_prompt displays prompt message $
 * @excute command excutes user command
 * @strspn remove trailling newline character
 */

/* Displays user prompt */
void print_prompt(void)
{
printf("$ ");
}

/* Read user input */
void read_command(char *command)
{
fgets(command, MAX_COMMAND_LEN, stdin);
command[strcspn(command, "\n")] = '\0';
}

/* Execute user command */
void execute_command(char *command)
{
pid_t pid;
int status;
char *args[MAX_ARGS];
int i = 0;

char *token = strtok(command, " ");
while (token != NULL && i < MAX_ARGS - 1)
{
args[i++] = token;
token = strtok(NULL, " ");
}
args[i] = NULL;
/* Set last argument to NULL for execvp()*/

pid = fork();
if (pid == 0)
{
 /*@execvp Child process*/
execvp(args[0], args);
printf("Command not found: %s\n", args[0]);
exit(1);
}
else if (pid < 0)
{

/* Error fork */
perror("fork");
}
else
{
 /*Parent process*/
waitpid(pid, &status, 0);
}
}

