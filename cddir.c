#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(void)
{
char *line = NULL;
char *args[100];
char cwd[BUFFER_SIZE];
int should_run = 1;
size_t line_buf_size = 0;

while (should_run)
{
getcwd(cwd, sizeof(cwd));
fputs(cwd, stdout);
fputs("$ ", stdout);

getline(&line, &line_buf_size, stdin);

int num_args = 0;
args[num_args] = strtok(line, " \t\n");
while (args[num_args] != NULL)
{
num_args++;
args[num_args] = strtok(NULL, " \t\n");
}
args[num_args] = NULL;

if (strcmp(args[0], "cd") == 0)
{
char *dir = args[1];
if (dir == NULL || strcmp(dir, "~") == 0)
{
dir = getenv("HOME");
}
if (strcmp(dir, "-") == 0)
{
dir = getenv("OLDPWD");
}
if (chdir(dir) != 0)
{
perror("cd");
}
else
{
setenv("OLDPWD", cwd, 1);
getcwd(cwd, sizeof(cwd));
setenv("PWD", cwd, 1);
}
}
else if (strcmp(args[0], "exit") == 0)
{
should_run = 0;
}
else
{
pid_t pid = fork();
if (pid == 0)
{
execvp(args[0], args);
perror("execvp");
exit(1);
}
else
{
wait(NULL);
}
}
}

free(line);
return (0);
}
