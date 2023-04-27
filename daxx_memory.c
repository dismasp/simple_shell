#include "shell.h"

/**
 * mem_free - frees a pointer and sets the address to NULL
 * @mem_ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int mem_free(void **mem_ptr)
{
if (mem_ptr && *mem_ptr)
{
free(*mem_ptr);
*mem_ptr = NULL;
return (1);
}
return (0);
}
