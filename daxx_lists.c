#include "shell.h"

/**
 * insert_node - adds a node to the start of the list
 * @head_ref: address of pointer to head node
 * @input_str: str field of node
 * @index: node index used by history
 *
 * Return: new head node
 */
list_t *insert_node(list_t **head_ref, const char *input_str, int index)
{
list_t *new_head_node;

if (!head_ref)
return (NULL);
new_head_node = malloc(sizeof(list_t));
if (!new_head_node)
return (NULL);
memset((void *)new_head_node, 0, sizeof(list_t));
new_head_node->num = index;
if (input_str)
{
new_head_node->str = strdup(input_str);
if (!new_head_node->str)
{
free(new_head_node);
return (NULL);
}
}
new_head_node->next = *head_ref;
*head_ref = new_head_node;
return (new_head_node);
}

/**
 * insert_node_end - adds a node to the end of the list
 * @head_ref: address of pointer to head node
 * @input_str: str field of node
 * @index: node index used by history
 *
 * Return: new node at the end of the list
 */
list_t *insert_node_end(list_t **head_ref, const char *input_str, int index)
{
list_t *new_node, *current_node;

if (!head_ref)
return (NULL);

current_node = *head_ref;
new_node = malloc(sizeof(list_t));
if (!new_node)
return (NULL);
memset((void *)new_node, 0, sizeof(list_t));
new_node->num = index;
if (input_str)
{
new_node->str = strdup(input_str);
if (!new_node->str)
{
free(new_node);
return (NULL);
}
}
if (current_node)
{
while (current_node->next)
current_node = current_node->next;
current_node->next = new_node;
}
else
*head_ref = new_node;
return (new_node);
}

/**
 * display_list_str - prints only the str element of a list_t linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t display_list_str(const list_t *head)
{
size_t counter = 0;

while (head)
{
puts(head->str ? head->str : "(nil)");
puts("\n");
head = head->next;
counter++;
}
return (counter);
}

/**
 * remove_node_at_index - deletes node at given index
 * @head_ref: address of pointer to first node
 * @position: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int remove_node_at_index(list_t **head_ref, unsigned int position)
{
list_t *current_node, *prev_node;
unsigned int idx = 0;

if (!head_ref || !*head_ref)
return (0);

if (!position)
{
current_node = *head_ref;
*head_ref = (*head_ref)->next;
free(current_node->str);
free(current_node);
return (1);
}
current_node = *head_ref;
while (current_node)
{
if (idx == position)
{
prev_node->next = current_node->next;
free(current_node->str);
free(current_node);
return (1);
}
idx++;
prev_node = current_node;
current_node = current_node->next;
}
return (0);
}

/**
 * delete_list - frees all nodes of a list
 * @head_ref: address of pointer to head node
 *
 * Return: void
 */
void delete_list(list_t **head_ref)
{
list_t *current_node, *next_node, *head;

if (!head_ref || !*head_ref)
return;
head = *head_ref;
current_node = head;
while (current_node)
{
next_node = current_node->next;
free(current_node->str);
free(current_node);
current_node = next_node;
}
*head_ref = NULL;
}
