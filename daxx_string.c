#include "shell.h"

/**
 * str_length - compute the length of a string
 * @str: the string whose length to calculate
 *
 * Return: integer length of string
 */
int str_length(char *str)
{
int count = 0;

if (!str)
return (0);

while (*str++)
count++;
return (count);
}

/**
 * str_compare - performs lexicographic comparison of two strings.
 * @str1: the first string
 * @str2: the second string
 *
 * Return: negative if str1 < str2, positive if
 * str1 > str2, zero if str1 == str2
 */
int str_compare(char *str1, char *str2)
{
while (*str1 && *str2)
{
if (*str1 != *str2)
return (*str1 - *str2);
str1++;
str2++;
}
if (*str1 == *str2)
return (0);
else
return (*str1 < *str2 ? -1 : 1);
}

/**
 * begin_with - verifies if given string starts with a substring
 * @main_str: string to search
 * @sub_str: the substring to find
 *
 * Return: address of next char of main_str or NULL
 */
char *begin_with(const char *main_str, const char *sub_str)
{
while (*sub_str)
if (*sub_str++ != *main_str++)
return (NULL);
return ((char *)main_str);
}

/**
 * str_concat - joins two strings together
 * @target: the destination buffer
 * @source: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *str_concat(char *target, char *source)
{
char *ret_val = target;

while (*target)
target++;
while (*source)
*target++ = *source++;
*target = *source;
return (ret_val);
}
