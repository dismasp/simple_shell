#include "shell.h"
/**
 **split_string - divides a string into words. Repeat delimiters are ignored
 *@input: the input string
 *@delim: the delimiter string
 *@c : char argument
 *Return: a pointer to an array of strings, or NULL on failure
 */

int is_delim(char c, char *delim);

char **split_string(char *input, char *delim)
{
int a, b, c, d, word_count = 0;
char **result;

if (input == NULL || input[0] == 0)
return (NULL);
if (!delim)
delim = " ";
for (a = 0; input[a] != '\0'; a++)
if (!is_delim(input[a], delim)
&& (is_delim(input[a + 1],
delim) || !input[a + 1]))
word_count++;

if (word_count == 0)
return (NULL);
result = malloc((1 + word_count) *sizeof(char *));
if (!result)
return (NULL);
for (a = 0, b = 0; b < word_count; b++)
{
while (is_delim(input[a], delim))
a++;
c = 0;
while (!is_delim(input[a + c], delim) && input[a + c])
c++;
result[b] = malloc((c + 1) * sizeof(char));
if (!result[b])
{
for (c = 0; c < b; c++)
free(result[c]);
free(result);
return (NULL);
}
for (d = 0; d < c; d++)
result[b][d] = input[a++];
result[b][d] = 0;
}
result[b] = NULL;
return (result);
}

/**
 * **split_string2 - divides a string into words
 * @input: the input string
 * @delim_char: the delimiter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **split_string2(char *input, char delim_char)
{
int a, b, c, d, word_count = 0;
char **result;

if (input == NULL || input[0] == 0)
return (NULL);
for (a = 0; input[a] != '\0'; a++)
if ((input[a] != delim_char && input[a + 1] == delim_char) ||
		(input[a] != delim_char && !input[a + 1]) || input[a + 1] == delim_char)
word_count++;
if (word_count == 0)
return (NULL);
result = malloc((1 + word_count) *sizeof(char *));
if (!result)
return (NULL);
for (a = 0, b = 0; b < word_count; b++)
{
while (input[a] == delim_char && input[a] != delim_char)
a++;
c = 0;
while (input[a + c] != delim_char &&
		input[a + c] && input[a + c] != delim_char)
c++;
result[b] = malloc((c + 1) * sizeof(char));
if (!result[b])
{
for (c = 0; c < b; c++)
free(result[c]);
free(result);
return (NULL);
}
for (d = 0; d < c; d++)
result[b][d] = input[a++];
result[b][d] = 0;
}
result[b] = NULL;
return (result);
}
