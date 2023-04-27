#include "shell.h"

/**
 * exit_shell - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int exit_shell(info_t *info)
{
int exit_status;

if (info->argv[1]) /* If there is an exit argument */
{
exit_status = error_string_to_int(info->argv[1]);
if (exit_status == -1)
{
info->status = 2;
display_error(info, "llegal number: ");
write_err(info->argv[1]);
write_char('\n');
return (1);
}
info->err_num = error_string_to_int(info->argv[1]);
return (-2);
}
info->err_num = -1;
return (-2);
}

/**
 * change_dir - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int change_dir(info_t *info)
{
char *curr_path, *dir, buffer[1024];
int chdir_result;

curr_path = getcwd(buffer, 1024);
if (!curr_path)
puts("TODO: >>getcwd failure emsg here<<\n");
if (!info->argv[1])
{
dir = get_env_value(info, "HOME=");
if (!dir)
chdir_result = /* TODO: what should this be? */
chdir((dir = get_env_value(info, "PWD=")) ? dir : "/");
else
chdir_result = chdir(dir);
}
else if (strcmp(info->argv[1], "-") == 0)
{
if (!get_env_value(info, "OLDPWD="))
{
puts(curr_path);
putchar('\n');
return (1);
}

puts(get_env_value(info, "OLDPWD=");
putchar('\n');
 chdir_result = /* TODO: what should this be? */
chdir((dir = get_env_value(info, "OLDPWD=")) ? dir : "/");
}
else
chdir_result = chdir(info->argv[1]);
if (chdir_result == -1)
{
display_error(info, "can't cd to ");
write_err(info->argv[1]), write_char('\n');
}
else
{
set_env_value(info, "OLDPWD", get_env_value(info, "PWD="));
set_env_value(info, "PWD", getcwd(buffer, 1024));
}
return (0);
}

/**
 * display_help - displays help for shell commands
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int display_help(info_t *info)
{
char **arg_list;

arg_list = info->argv;
puts("help call works. Function not yet implemented \n");
if (0)
puts(*arg_list); /* temp att_unused workaround */
return (0);
}
