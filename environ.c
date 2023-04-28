#include "shell.h"

/**
 * show_env - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *  constant function prototype.
 * Return: Always 0
 */

/*display_list_str(info->env)*/

int show_env(info_t *info)
{
display_list_str(info->env);
return (0);
}

/**
 * get_env_value - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *get_env_value(info_t *info, const char *name)
{
list_t *node = info->env;
char *start;

while (node)
{
start = starts_with(node->str, name);
if (start && *start)
return (start);
node = node->next;
}
return (NULL);
}

/**
 * set_env_var - Initialize a new environment variable,
 *   or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *constant function prototype.
 *  Return: Always 0
 */
int set_env_var(info_t *info)
{
if (info->argc != 3)
{
puts("Incorrect number of arguements\n");
return (1);
}
if (modify_env(info, info->argv[1], info->argv[2]))
return (0);
return (1);
}

/**
 * unset_env_var - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *constant function prototype.
 * Return: Always 0
 */
int unset_env_var(info_t *info)
{
int idx;

if (info->argc == 1)
{
puts("Too few arguements.\n");
return (1);
}
for (idx = 1; idx <= info->argc; idx++)
remove_env(info, info->argv[idx]);

return (0);
}

/**
 * fill_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *  constant function prototype.
 * Return: Always 0
 */
int fill_env_list(info_t *info)
{
list_t *node = NULL;
size_t i;

for (i = 0; environ[i]; i++)
add_list_node_end(&node, environ[i], 0);
info->env = node;
return (0);
}
