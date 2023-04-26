#ifndef TASK_H
#define TASK_H

#include <stdlib.h>
#include <unistd.h>

/* Data structures */

/**
 * struct info_s - Contains information to pass around between functions.
 * @argc: The number of arguments passed to the program.
 * @argv: The array of arguments passed to the program.
 * @env: The array of environment variables.
 * @status: The exit status of the last command.
 * @err_num: The error number of the last error that occurred.
 */
typedef struct info_s
{
int argc;
char **argv;
char **env;
int status;
int err_num;
} info_t;

/* Function prototypes */

/* _myexit - exits the shell */
int _myexit(info_t *info);

/* _mycd - changes the current directory of the process */
int _mycd(info_t *info);

/* _myhelp - prints help message */
int _myhelp(info_t *info);

/* Helper functions */

/* _puts - writes a string to stdout */
int _puts(char *str);

/* _eputs - writes a string to stderr */
int _eputs(char *str);

/* _putchar - writes a character to stdout */
int _putchar(char c);

/* _eputchar - writes a character to stderr */
int _eputchar(char c);

/* _strcmp - compares two strings */
int _strcmp(char *s1, char *s2);

/* _strlen - returns the length of a string */
int _strlen(char *str);

/* _strcpy - copies a string */
char *_strcpy(char *dest, char *src);

/* _getenv - gets the value of an environment variable */
char *_getenv(info_t *info, char *name);

/* _setenv - sets the value of an environment variable */
int _setenv(info_t *info, char *name, char *value);

/* _erratoi - converts a string to an integer */
int _erratoi(char *s);

/* print_error - prints an error message */
void print_error(info_t *info, char *msg);

#endif /* TASK_H */
