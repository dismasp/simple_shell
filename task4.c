#include "tempshell.h"

/**
 * shell_exit - exits the shell
 * @args: array of arguments (strings)
 * Return: exits with a given exit status
 * (0) if args[0] != "exit"
 */
int shell_exit(char **args)
{
int exitcheck;
if (args[1])
{
exitcheck = _erratoi(args[1]);
if (exitcheck == -1)
{
print_error("Illegal number: ");
_eputs(args[1]);
_eputchar('\n');
return (1);
}
return (-2);
}
return (-2);
}

/**
 * shell_cd - changes the current directory of the process
 * @args: array of arguments (strings)
 * Return: Always 0
 */
int shell_cd(char **args)
{
char *s, *dir, buffer[1024];
int chdir_ret;

s = getcwd(buffer, 1024);
if (!s)
_puts("TODO: >>getcwd failure emsg here<<\n");
if (!args[1])
{
dir = _getenv("HOME=");
if (!dir)
chdir_ret = chdir((dir = _getenv("PWD=")) ? dir : "/");
else
chdir_ret = chdir(dir);
}
else if (_strcmp(args[1], "-") == 0)
{
if (!_getenv("OLDPWD="))
{
_puts(s);
_putchar('\n');
return (1);
}
_puts(_getenv("OLDPWD=")), _putchar('\n');
chdir_ret = chdir((dir = _getenv("OLDPWD=")) ? dir : "/");
}
else
chdir_ret = chdir(args[1]);
if (chdir_ret == -1)
{
print_error("can't cd to ");
_eputs(args[1]), _eputchar('\n');
}
else
{
_setenv("OLDPWD", _getenv("PWD="));
_setenv("PWD", getcwd(buffer, 1024));
}
return (0);
}

/**
 * shell_help - prints help information for shell commands
 * @args: array of arguments (strings)
 * Return: Always 0
 */
int shell_help(char **args)
{
_puts("help call works. Function not yet implemented \n");
if (0)
_puts(*args); /* temp att_unused workaround */
return (0);
}
