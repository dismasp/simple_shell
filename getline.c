#include "shell.h"

/**
 * buffered_input - buffers chained commands
 * @info: parameter struct
 * @buf_ptr: address of buffer
 * @buf_len: address of len var
 *
 * Return: bytes read
 */
ssize_t buffered_input(info_t *info, char **buf_ptr, size_t *buf_len)
{
ssize_t read_bytes = 0;
size_t len_p = 0;

if (!*buf_len) /* if nothing left in the buffer, fill it */
{
free(*buf_ptr);
*buf_ptr = NULL;
signal(SIGINT, ctrl_c_handler);
#if USE_GETLINE
read_bytes = getline(buf_ptr, &len_p, stdin);
#else
read_bytes = custom_getline(info, buf_ptr, &len_p);
#endif
if (read_bytes > 0)
{
if ((*buf_ptr)[read_bytes - 1] == '\n')
{
(*buf_ptr)[read_bytes - 1] = '\0'; /* remove trailing newline */
read_bytes--;
}
info->linecount_flag = 1;
strip_comments(*buf_ptr);
build_history_list(info, *buf_ptr, info->histcount++);
{
*buf_len = read_bytes;
info->cmd_buf = buf_ptr;
}
}
}
return (read_bytes);
}

/**
 * fetch_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t fetch_input(info_t *info)
{
static char *chain_buf; /* the ';' command chain buffer */
static size_t i, j, buf_length;
ssize_t read_bytes = 0;
char **buf_ptr_p = &(info->arg), *p;

_putchar(BUF_FLUSH);
read_bytes = buffered_input(info, &chain_buf, &buf_length);
if (read_bytes == -1) /* EOF */
return (-1);
if (buf_length) /* we have commands left in the chain buffer */
{
j = i; /* init new iterator to current buf position */
p = chain_buf + i; /* get pointer for return */

inspect_chain(info, chain_buf, &j, i, buf_length);
while (j < buf_length) /* iterate to semicolon or end */
{
if (is_chain(info, chain_buf, &j))
break;
j++;
}

i = j + 1; /* increment past nulled ';'' */
if (i >= buf_length) /* reached end of buffer? */
{
i = buf_length = 0; /* reset position and length */
info->cmd_buf_type = CMD_NORM;
}

*buf_ptr_p = p; /* pass back pointer to current command position */
return (_strlen(p)); /* return length of current command */
}
 /* else not a chain, pass back buffer from custom_getline() */
*buf_ptr_p = chain_buf;
return (read_bytes); /* return length of buffer from custom_getline() */
}

/**
 * read_buffer - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buffer(info_t *info, char *buf, size_t *i)
{
ssize_t read_bytes = 0;

if (*i)
return (0);
read_bytes = read(info->readfd, buf, READ_BUF_SIZE);
if (read_bytes >= 0)
*i = read_bytes;
return (read_bytes);
}

/**
 * custom_getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int custom_getline(info_t *info, char **ptr, size_t *length)
{
static char buf[READ_BUF_SIZE];
static size_t i, len;
size_t k;
ssize_t r = 0, s = 0;
char *p = NULL, *new_p = NULL, *c;

p = *ptr;
if (p && length)
s = *length;
if (i == len)
i = len = 0;

r = read_buffer(info, buf, &len);
if (r == -1 || (r == 0 && len == 0))
return (-1);

c = _strchr(buf + i, '\n');
k = c ? 1 + (unsigned int)(c - buf) : len;
new_p = _realloc(p, s, s ? s + k : k + 1);
if (!new_p) /* MALLOC FAILURE! */
return (p ? free(p), -1 : -1);

if (s)
_strncat(new_p, buf + i, k - i);
else
_strncpy(new_p, buf + i, k - i + 1);

s += k - i;
i = k;
p = new_p;

if (length)
*length = s;
*ptr = p;
return (s);
}

/**
 * ctrl_c_handler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void ctrl_c_handler(__attribute__((unused))int sig_num)
{
_puts("\n");
_puts("$ ");
_putchar(BUF_FLUSH);
}

