#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 1024

/**
 * execute_command - Execute a non-builtin command.
 * @args: An array of arguments.
 * Return: 0 on success, -1 on failure.
 */
int execute_command(char **args)
{
pid_t pid;

pid = fork();
if (pid == 0)
{
if (execvp(args[0], args) == -1)
perror("execvp");
exit(EXIT_FAILURE);
}
else if (pid < 0)
{
perror("fork");
}
else
{
wait(NULL);
}
return (0);
}

/**
 * exit_shell - Exit the shell.
 * @args: An array of arguments.
 */
void exit_shell(char **args)
{
int status = 0;

if (args[1] != NULL)
status = atoi(args[1]);

free(args);
exit(status);
}

/**
 * tokenize_input - Tokenize user input.
 * @line: User input.
 * Return: An array of arguments.
 */
char **tokenize_input(char *line)
{
char **args = malloc(sizeof(char *) * BUFSIZE);
char *token;
int i = 0;

if (args == NULL)
{
perror("malloc");
exit(EXIT_FAILURE);
}

token = strtok(line, " ");
while (token != NULL)
{
args[i++] = token;
token = strtok(NULL, " ");
}
args[i] = NULL;
return (args);
}

/**
 * main - Entry point for the shell program
 * Return: Always 0 (Success)
 */
int main(void)
{
char *line = NULL;
size_t len = 0;
ssize_t nread;
int status = 1;

while (status)
{
write(STDOUT_FILENO, "$ ", 2);
nread = getline(&line, &len, stdin);
if (nread == -1)
{
free(line);
exit(EXIT_SUCCESS);
}
line[nread - 1] = '\0';

char **args = tokenize_input(line);

if (args[0] != NULL)
{
if (strcmp(args[0], "exit") == 0)
exit_shell(args);
else
execute_command(args);
}
free(args);
}
return (0);
}
