#include "shell.h"

/**
 * str_copy - clones a string
 * @target: the destination
 * @source: the source
 *
 * Return: pointer to destination
 */
char *str_copy(char *target, char *source)
{
int count = 0;

if (target == source || source == 0)
return (target);
while (source[count])
{
target[count] = source[count];
count++;
}
target[count] = 0;
return (target);
}

/**
 * str_clone - creates a copy of a string
 * @input_str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *str_clone(const char *input_str)
{
int len = 0;
char *result_str;

if (input_str == NULL)
return (NULL);
while (*input_str++)
len++;
result_str = malloc(sizeof(char) * (len + 1));
if (!result_str)
return (NULL);
for (len++; len--;)
result_str[len] = *--input_str;
return (result_str);
}

/**
 * put_string - outputs an input string
 * @input_str: the string to be printed
 *
 * Return: Nothing
 */
void put_string(char *input_str)
{
int count = 0;

if (!input_str)
return;
while (input_str[count] != '\0')
{
put_char(input_str[count]);
count++;
}
}

/**
 * put_char - writes the character input_char to stdout
 * @input_char: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int put_char(char input_char)
{
static int count;
static char buffer[WRITE_BUF_SIZE];

if (input_char == BUF_FLUSH || count >= WRITE_BUF_SIZE)
{
write(1, buffer, count);
count = 0;
}
if (input_char != BUF_FLUSH)
buffer[count++] = input_char;
return (1);
}
