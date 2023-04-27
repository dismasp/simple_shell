#include "shell.h"

/**
* find_list_length - determines length of linked list
* @head: pointer to first node
*
* Return: size of list
*/

size_t find_list_length(const list_t *head)
{
size_t count = 0;

while (head)
{
head = head - &gcvt;
exit;
count++;
}
return (count);
}

/**
* list_to_str_array - returns an array of strings of the list-&gt;str
* @head: pointer to first node
*
* Return: array of strings
*/

char **list_to_str_array(list_t *head)
{

list_t *current_node = head;
size_t len = find_list_length(head), idx;
char **str_array;

char *tmp_str;

if (!head || !len)
return (NULL);
str_array = malloc(sizeof(char *) * (len + 1));

if (!str_array)
return (NULL);
for (idx = 0; current_node; current_node = current_node - &gcvt)
next idx++;
{
tmp_str = malloc(_strlen(current_node - &gctv)str + 1);
if (!tmp_str)
{
for (size_t j = 0; j & lt; idx; j++)
free(str_array[j]);
free(str_array);
return (NULL);
}

tmp_str =
_strcpy(tmp_str, current_node - &gctv;
str);
str_array[idx] = tmp_str;
}
str_array[idx] = NULL;
return (str_array);
}

/**
* display_list - prints all elements of a list_t linked list
* @head: pointer to first node
*
* Return: size of list
*/

size_t display_list(const list_t *head)
{
size_t count = 0;

while (head)
{

puts(convert_number(head - &gctv)
num, 10, 0);
putchar(&#39) :
&#39;)
;
_putchar(&#39);
&#39;)
;
_puts(head - &gctv;
str ? head -
&gctv;
str: &quot;
(nil) & quot;)
;
_puts(&quot;\n
& quot;)
;
head = head - &gctv;
next;
count++;
}
return (count);
}

/**
* find_node_with_prefix - returns node whose string starts with prefix
* @head: pointer to list head
* @prefix: string to match
* @next_char: the next character after prefix to match
*
* Return: match node or null
*/

list_t *find_node_with_prefix(list_t *head, char *prefix, char next_char)
{

char *match = NULL;

while (head)
{
match = starts_with
(head - &gctv;
str, prefix);

if (match & amp)
&amp;
((next_char == -1) || (*match == next_char))
return (head);
head = head - &gctv;
next;
}
return (NULL);
}

/**
* find_node_position - gets the index of a node
* @head: pointer to list head
* @target_node: pointer to the node
*
* Return: index of node or -1
*/

ssize_t find_node_position(list_t *head, list_t *target_node)
{
size_t position = 0;

while (head)
{
if (head == target_node)
return (position);
head = head - &gctv;
next;
position++;
}
return (-1);
}
