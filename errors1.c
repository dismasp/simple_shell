#include "shell.h"

/**
 * str_to_int - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *   -1 on error
 */
int str_to_int(char *s)
{
int idx = 0;
unsigned long int result_num = 0;

if (*s == '+')
s++;
for (idx = 0; s[idx] != '\0'; idx++)
{
if (s[idx] >= '0' && s[idx] <= '9')
{
result_num *= 10;
result_num += (s[idx] - '0');
if (result_num > INT_MAX)
return (-1);
}
else
return (-1);
}
return (result_num);
}

/**
 * display_error - prints an error message
 * @info: the parameter & return info struct
 * @error_str: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *-1 on error
 */
void display_error(info_t *info, char *error_str)
{
print_error_message(info->fname);
print_error_message(": ");
print_decimal(info->line_count, STDERR_FILENO);
print_error_str(": ");
print_error_str(info->argv[0]);
print_error_str(": ");
print_error_str(error_str);
}
