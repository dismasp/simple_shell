#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_NUM_ARGS 64
/*
 * @main:entry point
 * @prompt display shell
 * @getline gets user input
 * @size_t allocates memory
 * @nchar will check if the return value is -1 and exit the shell if it isi
 * @lineptr to store the address of the buffer holding whatever was typed.
 * @*delim represents characters separating the string
 */
int fputs(const char *s, FILE *stream);

int main(int argc, char **argv)
{

char *prompt = "(shell)$";
char *lineptr = NULL;
size_t n = 0;
ssize_t nchar_read;
ssize_t i;
/*declare void variables*/
(void)argc;
(void)argv;

/*create infite loop to show prompt after exec */
while (1)
{
fputs(prompt, stdout);
nchar_read = getline(&lineptr, &n, stdin);

/*if getline functions fail or user enters condition (Ctrl+D)*/
if (nchar_read == -1)
{
putchar('E');
putchar('x');
putchar('i');
putchar('t');
putchar('i');
putchar('n');
putchar('g');
putchar(' ');
putchar('s');
putchar('h');
putchar('e');
putchar('l');
putchar('l');
putchar('.');
putchar('.');
putchar('.');
putchar(' ');
putchar('\n');
return (-1);
}
 /* Use putchar to print characters in lineptr */
for (i = 0; i < nchar_read; i++)
{
putchar(lineptr[i]);
}

free(lineptr);
lineptr = NULL;
}
return (0);

}
