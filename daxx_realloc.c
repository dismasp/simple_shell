#include "shell.h"

/**
 * fill_memory - fills memory with a constant byte
 * @mem: the pointer to the memory area
 * @byte: the byte to fill *mem with
 * @num: the amount of bytes to be filled
 * Return: (mem) a pointer to the memory area mem
 */
char *fill_memory(char *mem, char byte, unsigned int num)
{
unsigned int i;

for (i = 0; i < num; i++)
mem[i] = byte;
return (mem);
}

/**
 * free_strings - frees a string of strings
 * @str_arr: string of strings
 */
void free_strings(char **str_arr)
{
char **tmp = str_arr;

if (!str_arr)
return;
while (*str_arr)
free(*str_arr++);
free(tmp);
}

/**
 * resize_memory - reallocates a block of memory
 * @mem_ptr: pointer to previous malloc'ated block
 * @prev_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to the updated block.
 */
void *resize_memory(void *mem_ptr,
		unsigned int prev_size, unsigned int new_size)
{
char *new_mem;

if (!mem_ptr)
return (malloc(new_size));
if (!new_size)
return (free(mem_ptr), NULL);
if (new_size == prev_size)
return (mem_ptr);

new_mem = malloc(new_size);
if (!new_mem)
return (NULL);

prev_size = prev_size < new_size ? prev_size : new_size;
while (prev_size--)
new_mem[prev_size] = ((char *)mem_ptr)[prev_size];
free(mem_ptr);
return (new_mem);
}
