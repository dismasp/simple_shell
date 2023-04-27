#include "shell.h"

/**
 * is_operator - checks if current char in buffer is an operator
 * @params: the parameter struct
 * @buffer: the char buffer
 * @pos: address of current position in buffer
 *
 * Return: 1 if operator, 0 otherwise
 */
int is_operator(param_t *params, char *buffer, size_t *pos)
{
size_t index = *pos;

if (buffer[index] == '|' && buffer[index + 1] == '|')
{
buffer[index] = 0;
index++;
params->command_buffer_type = CMD_OR;
}
else if (buffer[index] == '&' && buffer[index + 1] == '&')
{
buffer[index] = 0;
index++;
params->command_buffer_type = CMD_AND;
}
else if (buffer[index] == ';')
{
buffer[index] = 0;
params->command_buffer_type = CMD_CHAIN;
}
else
return (0);
*pos = index;
return (1);
}

/**
 * validate_operator - checks if we should continue based on last status
 * @params: the parameter struct
 * @buffer: the char buffer
 * @pos: address of current position in buffer
 * @initial: starting position in buffer
 * @length: length of buffer
 *
 * Return: Void
 */
void validate_operator(param_t *params, char *buffer,
		size_t *pos, size_t initial, size_t length)
{
size_t index = *pos;

if (params->command_buffer_type == CMD_AND)
{
if (params->status)
{
buffer[initial] = 0;
index = length;
}
}
if (params->command_buffer_type == CMD_OR)
{
if (!params->status)
{
buffer[initial] = 0;
index = length;
}
}

*pos = index;
}

/**
 * substitute_alias - substitutes an alias in the tokenized string
 * @params: the parameter struct
 *
 * Return: 1 if substituted, 0 otherwise
 */
int substitute_alias(param_t *params)
{
int i;
list_t *listNode;
char *ptr;

for (i = 0; i < 10; i++)
{
listNode = node_starts_with(params->alias, params->argsv[0], '=');
if (!listNode)
return (0);
free(params->argsv[0]);
ptr = _strchr(listNode->str, '=');
if (!ptr)
return (0);
ptr = _strdup(ptr + 1);
if (!ptr)
return (0);
params->argsv[0] = ptr;
}
return (1);
}

/**
 * substitute_vars - substitutes vars in the tokenized string
 * @params: the parameter struct
 *
 * Return: 1 if substituted, 0 otherwise
 */
int substitute_vars(param_t *params)
{
int i = 0;
list_t *listNode;

for (i = 0; params->argsv[i]; i++)
{
if (params->argsv[i][0] != '$' || !params->argsv[i][1])
continue;

if (!_strcmp(params->argsv[i], "$?"))
{
substitute_string(&(params->argsv[i]),
_strdup(convert_number(params->status, 10, 0)));
continue;
}
if (!_strcmp(params->argsv[i], "$$"))
{
substitute_string(&(params->args[i]),
_strdup(convert_number(getpid(), 10, 0)));
continue;
}
listNode = node_starts_with(params->env, &params->argsv[i][1], '=');
if (listNode)
{
substitute_string(&(params->argsv[i]),
_strdup(_strchr(listNode->str, '=') + 1));
continue;
}
substitute_string(&params->argsv[i], _strdup(""));

}
return (0);
}

/**
 * substitute_string - substitutes string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if substituted, 0 otherwise
 */
int substitute_string(char **old, char *new)
{
free(*old);
*old = new;
return (1);
}
