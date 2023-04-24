#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

/**
* read_input - reads input from stdin
* @buffer: buffer to store input
* Return: number of bytes read
*/
int read_input(char *buffer)
{
int bytes_read = 0;

bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
if (bytes_read <= 0)
{
return (-1);
}

return (bytes_read);
}

/**
* read_buffer - reads characters from buffer into line
* @line: line to store characters
* @buffer: buffer to read characters from
* @pos: position in buffer to start reading from
* @read_size: number of bytes read from stdin
* Return: number of characters read into line
*/
int read_buffer(char *line, char *buffer, int pos, int read_size)
{
int i = 0;

for (i = 0; pos < read_size; i++, pos++)
{
if (buffer[pos] == '\n')
{
line[i] = '\0';
pos++;
return (i);
}
line[i] = buffer[pos];
}

return (i);
}

/**
* my_getline - reads a line from stdin
* Return: pointer to line read or NULL on failure
*/
char *my_getline(void)
{
static char buffer[BUFFER_SIZE];
static int pos;
int bytes_read = 0, i = 0;
char *line = NULL;

/* if pos is zero, fill buffer with input */
if (pos == 0)
{
bytes_read = read_input(buffer);
if (bytes_read <= 0)
{
return (NULL);
}
}

line = malloc(BUFFER_SIZE * sizeof(char));
if (line == NULL)
{
return (NULL);
}

/* read characters from buffer into line */
i = read_buffer(line, buffer, pos, bytes_read);

/* if there's more input to read, recursively call my_getline() */
if (bytes_read == BUFFER_SIZE)
{
char *next_line = my_getline();
if (next_line == NULL)
{
free(line);
return (NULL);
}
int next_len = strlen(next_line);
line = realloc(line, (i + next_len + 1) * sizeof(char));
if (line == NULL)
{
free(next_line);
return (NULL);
}
strncpy(line + i, next_line, next_len);
free(next_line);
return (line);
}

/* if we reach the end of buffer without finding a newline character */
line[i] = '\0';
pos = 0;
return (line);
}

/**
* main - entry point for Simple shell 0.1
* Return: 0 on success
*/
int main(void)
{
char *line;

while (1)
{
/* print prompt */
write(STDOUT_FILENO, "$ ", 2);

/* read input */
line = my_getline();

/* handle input */
if (line == NULL)
{
break;
}
write(STDOUT_FILENO, line, strlen(line));
write(STDOUT_FILENO, "\n", 1);
free(line);
}

return (0);
}
