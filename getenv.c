#include "shell.h"

/**
 * get_environment - returns the string array copy of our environment
 * @info: Structure containing potential arguments. Used to maintain
 *  constant function prototype.
 * Return: Always 0
 */
char **get_environment(info_t *info)
{
if (!info->environ || info->env_changed)
{
info->environ = list_to_string_array(info->env);
info->env_changed = 0;
}

return (info->environ);
}

/**
 * remove_env_var - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int remove_env_var(info_t *info, char *var)
{
list_t *node = info->env;
size_t idx = 0;
char *substring;

if (!node || !var)
return (0);

while (node)
{
substring = starts_with(node->str, var);
if (substring && *substring == '=')
{
info->env_changed = delete_node_at(&(info->env), idx);
idx = 0;
node = info->env;
continue;
}
node = node->next;
idx++;
}
return (info->env_changed);
}

/**
 * update_env_var - Initialize a new environment variable,
 *  or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int update_env_var(info_t *info, char *var, char *value)
{
char *temp_buf = NULL;
list_t *node;
char *substring;

if (!var || !value)
return (0);

temp_buf = malloc(strlen(var) + strlen(value) + 2);
if (!temp_buf)
return (1);
strcpy(temp_buf, var);
strcat(temp_buf, "=");
strcat(temp_buf, value);
node = info->env;
while (node)
{
substring = starts_with(node->str, var);
if (substring && *substring == '=')
{
free(node->str);
node->str = temp_buf;
info->env_changed = 1;
return (0);
}
node = node->next;
}
add_list_node_end(&(info->env), temp_buf, 0);
free(temp_buf);
info->env_changed = 1;
return (0);
}
