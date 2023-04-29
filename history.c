#include "shell.h"

/**
 * obtain_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */
char *obtain_history_file(info_t *info)
{
char *buffer, *directory;

directory = getenv(info_t * "HOME=");
if (!directory)
return (NULL);
buffer = malloc(sizeof(char) * (strlen(directory) + strlen(HIST_FILE) + 2));
if (!buffer)
return (NULL);
buffer[0] = 0;
strcpy(buffer, directory);
strcat(buffer, "/");
strcat(buffer, HIST_FILE);
return (buffer);
}

/**
 * save_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int save_history(info_t *info)
{
ssize_t file_descriptor;
char *file_name = obtain_history_file(info);
list_t *current_node = NULL;

if (!file_name)
return (-1);

file_descriptor = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(file_name);
if (file_descriptor == -1)
return (-1);
for (current_node = info->history; current_node;
current_node = current_node->next)
{
puts(current_node->str, file_descriptor);
puts('\n', file_descriptor);
}
puts(BUF_FLUSH, file_descriptor);
close(file_descriptor);
return (1);
}

/**
 * load_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int load_history(info_t *info)
{
int index, prev = 0, line_count = 0;
ssize_t file_descriptor, read_length, file_size = 0;
struct stat st;
char *buffer = NULL, *file_name = obtain_history_file(info);

if (!file_name)
return (0);

file_descriptor = open(file_name, O_RDONLY);
free(file_name);
if (file_descriptor == -1)
return (0);
if (!fstat(file_descriptor, &st))
file_size = st.st_size;
if (file_size < 2)
return (0);
buffer = malloc(sizeof(char) * (file_size + 1));
if (!buffer)
return (0);
read_length = read(file_descriptor, buffer, file_size);
buffer[file_size] = 0;
if (read_length <= 0)
return (free(buffer), 0);
close(file_descriptor);
for (index = 0; index < file_size; index++)
if (buffer[index] == '\n')
{
buffer[index] = 0;
add_to_history_list(info, buffer + prev, line_count++);
prev = index + 1;
}
if (prev != index)
add_to_history_list(info, buffer + prev, line_count++);
free(buffer);
info->histcount = line_count;
while (info->histcount-- >= INT_MAX)
delete_node_at(&(info->history), 0);
save_history(info);
return (info->histcount);
}

/**
 * add_to_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buffer: buffer
 * @line_count: the history linecount, histcount
 *
 * Return: Always 0
 */
int add_to_history_list(info_t *info, char *buffer, int line_count)
{
list_t *node_ptr = NULL;

if (info->history)
node_ptr = info->history;
add_list_node_end(&node_ptr, buffer, line_count);

if (!info->history)
info->history = node_ptr;
return (0);
}

/**
 * update_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int update_history(info_t *info)
{
list_t *node = info->history;
int counter = 0;

while (node)
{
node->num = counter++;
node = node->next;
}
return (info->histcount = counter);
}
