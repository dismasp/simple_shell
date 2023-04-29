#include "shell.h"

/**
 * shell_cycle - main shell loop
 * @inf: the parameter & return info struct
 * @arguments: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shell_cycle(info_t *inf, char **arguments)
{
ssize_t read_bytes = 0;
int builtin_result = 0;

while (read_bytes != -1 && builtin_result != -2)
{
reset_info(inf);
if (shell_interactive(inf))
puts("$ ");
putchar(BUF_FLUSH);
read_bytes = get_user_input(inf);
if (read_bytes != -1)
{
update_info(inf, arguments);
builtin_result = search_builtin(inf);
if (builtin_result == -1)
execute_command(inf);
}
else if ( shell_interactive(inf))
putchar('\n');
release_info(inf, 0);
}
shell_history(inf);
release_info(inf, 1);
if (!shell_interactive(inf) && inf->status)
exit(inf->status);
if (builtin_result == -2)
{
if (inf->err_num == -1)
exit(inf->status);
exit(inf->err_num);
}
return (builtin_result);
}

/**
 * search_builtin - finds a builtin command
 * @inf: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int search_builtin(info_t *inf)
{
int i, builtin_status = -1;
builtin_table builtin_tbl[] = {
{
"exit", _custom_exit},
{
"env", _custom_env},
{
"help", _custom_help},
{
"history", _custom_history},
{
"setenv", _custom_setenv},
{
"unsetenv", _custom_unsetenv},
{
"cd", _custom_cd},
{
"alias", _custom_alias},
{
NULL, NULL
}
};

for (i = 0; builtin_tbl[i].type; i++)
if (strcmp(inf->argv[0], builtin_tbl[i].type) == 0)
{
inf->line_count++;
builtin_status = builtin_tbl[i].func(inf);
break;
}
return (builtin_status);
}

/**
 * locate_command - finds a command in PATH
 * @inf: the parameter & return info struct
 *
 * Return: void
 */
void locate_command(info_t *inf)
{
char *path = NULL;
int i, counter;

inf->path = inf->argv[0];
if (inf->linecount_flag == 1)
{
inf->line_count++;
inf->linecount_flag = 0;
}
for (i = 0, counter = 0; inf->arg[i]; i++)
if (!is_delim(inf->arg[i], " \t\n"))
counter++;
if (!counter)
return;

path = locate_path(inf, getenv(inf, "PATH="), inf->argv[0]);
if (path)
{
inf->path = path;
execute_command(inf);
}
else
{
if ((is_interactive(inf) || getenv(inf, "PATH=")
|| inf->argv[0][0] == '/') && is_valid_command(inf, inf->argv[0]))
execute_command(inf);
else if (*(inf->arg) != '\n')
{
inf->status = 127;
print_error(inf, "not found\n");
}
}
}

/**
 * execute_command - forks a an exec thread to run cmd
 * @inf: the parameter & return info struct
 *
 * Return: void
 */
void execute_command(info_t *inf)
{
pid_t child_pid;

child_pid = fork();
if (child_pid == -1)
{
/* TODO: PUT ERROR FUNCTION */
perror("Error:");
return;
}
if (child_pid == 0)
{
if (execve(inf->path, inf->argv, fetch_env_vars(inf)) == -1)
{
release_info(inf, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
/* TODO: PUT ERROR FUNCTION */
}
else
{
wait(&(inf->status));
if (WIFEXITED(inf->status))
{
inf->status = WEXITSTATUS(inf->status);
if (inf->status == 126)
print_error(inf, "Permission denied\n");
}
}
}
