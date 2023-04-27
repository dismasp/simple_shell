#include "shell.h"

/**
 * str_copy_n - copies a string
 * @dest_str: the destination string to be copied to
 * @src_str: the source string
 * @n_chars: the amount of characters to be copied
 * Return: the concatenated string
 */
char *str_copy_n(char *dest_str, char *src_str, int n_chars)
{
int i, j;
char *s = dest_str;

i = 0;
while (src_str[i] != '\0' && i < n_chars - 1)
{
dest_str[i] = src_str[i];
i++;
}
if (i < n_chars)
{
j = i;
while (j < n_chars)
{
dest_str[j] = '\0';
j++;
}
}
return (s);
}

/**
 * str_concat_n - concatenates two strings
 * @first_str: the first string
 * @second_str: the second string
 * @max_bytes: the amount of bytes to be maximally used
 * Return: the concatenated string
 */
char *str_concat_n(char *first_str, char *second_str, int max_bytes)
{
int i, j;
char *s = first_str;

i = 0;
j = 0;
while (first_str[i] != '\0')
i++;
while (second_str[j] != '\0' && j < max_bytes)
{
first_str[i] = second_str[j];
i++;
j++;
}
if (j < max_bytes)
first_str[i] = '\0';
return (s);
}

/**
 * find_char - locates a character in a string
 * @str: the string to be parsed
 * @ch: the character to look for
 * Return: (str) a pointer to the memory area str
 */
char *find_char(char *str, char ch)
{
do {
if (*str == ch)
return (str);
} while (*str++ != '\0');

return (NULL);
}

