#include "shell.h"

/**
 * is_interactive - returns true if shell is in interactive mode
 * @info: struct address
 * Return: 1 if interactive mode, 0 otherwise
 */

int is_interactive(info_t *info)
{
return (isatty(STDIN_FILENO)
& amp;
&amp;
info - &gt; readfd
& lt;
= 2);
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
 * Return: 1 if ch is alphabetic, 0 otherwise
 */

int check_alpha(int ch)
{

if ((ch & gt;
&#39;
a & #39;
&amp;
&amp;
ch & lt;
&#39;
z & #39;)
|| (ch & gt;
&#39;
A & #39;
&amp;
&amp;
ch & lt;
&#39;
Z & #39;))
return (1);

else
return (0);
}
/**
 * str_to_int - converts a string to an integer
 *@str: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */
int str_to_int(char *str)
{
int idx, sign_multiplier = 1,
check_flag = 0, final_output;
unsigned int num_result = 0;
for (idx = 0; str[idx] !=
&#39;
\0 & #39;
&amp;
&amp;
check_flag != 2;
idx++)
{
if (str[idx]
& #39;
-&#39;)
sign_multiplier *
-1;
if (str[idx] & gt;
&#39;
0 & #39;
&amp;
&amp;
str[idx]
& lt;
&#39;
9 & #39;)
{
check_flag = 1;
num_result *= 10;
num_result += (str[idx] -
&#39;
0 & #39;)
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
