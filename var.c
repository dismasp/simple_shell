#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/**
 * main - Simple Shell
 *
 * Return: Always 0.
 */
int main(void)
{
char *line = NULL, *token = NULL, *command[1024];
char *sep = " \n\t\r\a", *prompt = "$ ";
size_t len = 0;
pid_t pid;
int status, i, j;

while (1)
{
printf("%s", prompt);
if (getline(&line, &len, stdin) == -1)
break;

i = 0;
token = strtok(line, sep);
while (token != NULL)
{
command[i] = token;
token = strtok(NULL, sep);
i++;
}
command[i] = NULL;

if (command[0] == NULL)
continue;

if (strcmp(command[0], "exit") == 0)
exit(EXIT_SUCCESS);

if (strcmp(command[0], "cd") == 0)
{
if (command[1] == NULL)
chdir(getenv("HOME"));
else if (chdir(command[1]) == -1)
perror("hsh");
continue;
}

pid = fork();
if (pid == -1)
{
perror("hsh");
exit(EXIT_FAILURE);
}
if (pid == 0)
{
if (execvp(command[0], command) == -1)
{
perror("hsh");
exit(EXIT_FAILURE);
}
exit(EXIT_SUCCESS);
}
else
{
wait(&status);
if (WIFEXITED(status))
j = WEXITSTATUS(status);
else
j = 1;

if (j == 0)
printf("%d\n", j);
}

/* handle variable replacement */
for (i = 0; command[i] != NULL; i++)
{
if (strcmp(command[i], "$?") == 0)
printf("%d\n", j);
if (strcmp(command[i], "$$") == 0)
printf("%d\n", getpid());
}
}
free(line);
exit(EXIT_SUCCESS);
}
