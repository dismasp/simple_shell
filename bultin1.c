#include "shell.h"

/**
* display_history - displays the history list, one command per line, preceded
* with line numbers, starting at 0.
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int display_history(info_t *info)
{
print_list
(info - &gt;
history);
return (0);
}

/**
* remove_alias - removes an alias
* @info: parameter struct
* @alias_str: the alias string
*
* Return: Always 0 on success, 1 on error
*/
int remove_alias(info_t *info, char *alias_str)
{
char *alias_pos, alias_char;
int result;
alias_pos = _strchr
(alias_str, &#39;
&#39;)
;
if (!alias_pos)
return (1);
alias_char = *alias_pos;
*alias_pos = 0;
result =
delete_node_at_index
(&amp;
(info - &gt;
alias),
get_node_index(info - &gt;
alias,
node_starts_with(info - &gt; alias,
alias_str, -1)));
*alias_pos = alias_char;
return (result);
}

/**
* create_alias - creates an alias from a string
* @info: parameter struct
* @alias_str: the alias string
*
* Return: Always 0 on success, 1 on error
*/
int create_alias(info_t *info, char *alias_str)
{
char *alias_pos;
alias_pos = _strchr
(alias_str, &#39;
&#39;)
;
if (!alias_pos)
return (1);
if (!*++alias_pos)
return (remove_alias(info, alias_str));

remove_alias(info, alias_str);
return (add_node_end(&amp;
(info - &gt;
alias);
alias_str, 0) == NULL);
}

/**
* display_single_alias - displays an alias string
* @alias_node: the alias node

*
* Return: Always 0 on success, 1 on error
*/
int display_single_alias(list_t *alias_node)
{
char *alias_ptr = NULL,
*alias_iter = NULL;

if (alias_node)
{
alias_ptr =
_strchr
(alias_node - &gt; str,
&#39;
= &#39;
);
for (alias_iter = alias_node - &gt;
str; alias_iter &
lt;
alias_ptr; alias_iter++)
_putchar(*alias_iter);
_putchar(&#39;
\ &#39;
&#39;)
;
_puts(alias_ptr + 1);
_puts(&quot;
&#39 ;\n
& quot;
);
return (0);
}
return (1);
}

/**
* handle_alias - handles the alias builtin command (man alias)
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int handle_alias(info_t *info)
{
int idx = 0;
char *alias_ptr = NULL;
list_t *alias_node = NULL;

if (info - &gt; argc == 1)
{
alias_node = info - &gt;
alias;
while (alias_node)
{
display_single_alias(alias_node);
alias_node = alias_node - &gt;
next;
}
return (0);
}
for (idx = 1; info - &gt ; argv[idx]; idx++)
{
alias_ptr = _strchr(info - &gt;
argv[idx],
&#39;
&#39;
);
if (alias_ptr)
create_alias(info, info - &gt;
argv[idx]);
else
display_single_alias
(node_starts_with(info - &gt; alias,
info - &gt;
argv[idx],
&#39; =
&#39;)
);
}

return (0);
}
