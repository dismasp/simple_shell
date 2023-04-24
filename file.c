#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAX_ARGS 64
#define MAX_ARG_LENGTH 64
#define MAX_LINE_LENGTH 1024

int main(int argc, char *argv[])
{
char *args[MAX_ARGS];
char line[MAX_LINE_LENGTH];
int status;
ssize_t read;
size_t len = 0;
FILE *input_file;

if (argc == 2)
{
input_file = fopen(argv[1], "r");
if (input_file == NULL)
{
perror("Error opening input file");
exit(EXIT_FAILURE);
}
}
else if (argc > 2)
{
fprintf(stderr, "Usage: simple_shell [filename]\n");
exit(EXIT_FAILURE);
}

while ((argc != 2) || ((read = getline(&line, &len, input_file)) != -1))
{
int arg_count = 0;
char *token;

if (argc != 2)
{
write(STDOUT_FILENO, "$ ", 2);
read = getline(&line, &len, stdin);
if (read == -1)
{
break;
}
}

token = strtok(line, " \n");
while (token != NULL && arg_count < MAX_ARGS)
{
args[arg_count] = token;
arg_count++;
token = strtok(NULL, " \n");
}
args[arg_count] = NULL;

if (arg_count == 0)
{
continue;
}

pid_t child_pid = fork();
if (child_pid == -1)
{
perror("Fork failed");
exit(EXIT_FAILURE);
}
else if (child_pid == 0)
{
if (execvp(args[0], args) == -1)
{
perror("Exec failed");
exit(EXIT_FAILURE);
}
}
else
{
waitpid(child_pid, &status, 0);
}
}

if (argc == 2)
{
fclose(input_file);
}

return (EXIT_SUCCESS);
}
