<<<<<<< HEAD
#include "shell.h"

/**
*is_interactive - returns true if shell is in interactive mode
*@info: struct address
*
*Return: 1 if interactive mode, 0 otherwise
*/

int is_interactive(info_t *info)

{
return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
*check_delimiter - checks if character is a delimiter
*@ch: the character to check
*@delimiter: the delimiter string
*Return: 1 if true, 0 if false
*/

int check_delimiter(char ch, char *delimiter)
{
while (*delimiter)
if (*delimiter++ == ch)
return (1);
return (0);
}

/**
*check_alpha - checks for alphabetic character
*@ch: The character to input
*Return: 1 if ch is alphabetic, 0 otherwise
*/

int check_alpha(int ch)
{
if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
return (1);
else
return (0);
}

/**
*str_to_int - converts a string to an integer
*@str: the string to be converted
*Return: 0 if no numbers in string, converted number otherwise
*/

int str_to_int(char *str)
{
int idx, sign_multiplier = 1, check_flag = 0, final_output;
unsigned int num_result = 0;

for (idx = 0; str[idx] != '\0' && check_flag != 2; idx++)
{
if (str[idx] == '-')
sign_multiplier *= -1;

if (str[idx] >= '0' && str[idx] <= '9')
{
check_flag = 1;
num_result *= 10;
num_result += (str[idx] - '0');
}
else if (check_flag == 1)
check_flag = 2;
}

if (sign_multiplier == -1)
final_output = -num_result;
else
final_output = num_result;

return (final_output);
}
=======
>>>>>>> 6c626c65ac3bc153361f8263251830c1a10a152e
