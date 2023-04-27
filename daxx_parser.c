#include "shell.h"

/**
 * is_executable - determines if a file is an executable command
 * @info: the info struct
 * @filepath: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_executable(info_t *info, char *filepath)
{
struct stat st;

(void)info;
if (!filepath || stat(filepath, &st))
return (0);

if (st.st_mode & S_IFREG)
{
return (1);
}
return (0);
}

/**
 * copy_chars - copies characters
 * @path_str: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *copy_chars(char *path_str, int start, int stop)
{
static char buffer[1024];
int i = 0, k = 0;

for (k = 0, i = start; i < stop; i++)
if (path_str[i] != ':')
buffer[k++] = path_str[i];
buffer[k] = 0;
return (buffer);
}

/**
 * locate_path - locates the cmd in the PATH string
 * @info: the info struct
 * @path_str: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *locate_path(info_t *info, char *path_str, char *cmd)
{
int i = 0, curr_position = 0;
char *path;

if (!path_str)
return (NULL);
if ((strlen(cmd) > 2) && starts_with(cmd, "./"))
{
if (is_executable(info, cmd))
return (cmd);
}
while (1)
{
if (!path_str[i] || path_str[i] == ':')
{
path = copy_chars(path_str, curr_position, i);
if (!*path)
strcat(path, cmd);
else
{
strcat(path, "/");
strcat(path, cmd);
}
if (is_executable(info, path))
return (path);
if (!path_str[i])
break;
curr_position = i;
}
i++;
}
return (NULL);
}
