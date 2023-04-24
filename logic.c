#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFSIZE 1024

/* Function declarations */
char **parse_input(char *input);
int execute_commands(char **commands);

/**
 * main - Program entry
 * return: Return 0
 */

int main(void)
{
char input[BUFSIZE];
char **commands;
int status;

while (1)
{
printf("$ ");
if (fgets(input, BUFSIZE, stdin) == NULL)
{
break;
}

input[strcspn(input, "\n")] = '\0'; /* Remove newline */

/* Split input into separate commands */
commands = parse_input(input);

/* Execute commands and get exit status */
status = execute_commands(commands);

/* Free memory */
free(commands);

/* Exit loop if status is nonzero */
if (status != 0)
{
break;
}
}

return (0);
}

/**
 * parse_input - Parse input into separate commands
 * @input:	Input entry
 * return: Return entry
 */

char **parse_input(char *input)
{
char **commands = malloc(BUFSIZE * sizeof(char *));
char *token;
int i = 0;

if (commands == NULL)
{
perror("malloc");
exit(EXIT_FAILURE);
}

token = strtok(input, " ");

while (token != NULL)
{
commands[i] = token;
i++;
token = strtok(NULL, " ");
}

commands[i] = NULL;

return (commands);
}

/* Execute commands and return exit status */

/**
 * execute_commands - Execute commands and return exit status
 * @commands: Command paramenter
 * return: return some value
 */

int execute_commands(char **commands)
{
int i, status, result = 0;
pid_t pid;

/* Execute commands separated by "&&" */
for (i = 0; commands[i] != NULL; i++)
{
if (strcmp(commands[i], "&&") == 0)
{
/* Execute previous command and check exit status */
if (result == 0)
{
continue;
}
else
{
return (result);
}
}
else if (strcmp(commands[i], "||") == 0)
{
/* Execute previous command and check exit status */
if (result != 0)
{
continue;
}
else
{
return (result);
}
}

pid = fork();
if (pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
/* Child process */
if (execvp(commands[i], commands) == -1)
{
perror("execvp");
exit(EXIT_FAILURE);
}
}
else
{
/* Parent process */
if (waitpid(pid, &status, 0) == -1)
{
perror("waitpid");
exit(EXIT_FAILURE);
}
if (WIFEXITED(status))
{
result = WEXITSTATUS(status);
}
}
}

return (result);
}
