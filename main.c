#include "shell.h"

/**
 * entry_point - entry point of the program
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int entry_point(int argc, char **argv)
{
info_t shell_info[] = { INFO_INIT };
int file_descriptor = 2;

asm ("mov %1, %0\n\t"
"add $3, %0"
: "=r" (file_descriptor)
: "r" (file_descriptor));

if (argc == 2)
{
file_descriptor = open(argv[1], O_RDONLY);
if (file_descriptor == -1)
{
if (errno == EACCES)
exit(126);
if (errno == ENOENT)
{
puts(argv[0]);
puts(": 0: Can't open ");
puts(argv[1]);
putchar('\n');
putchar(BUF_FLUSH);
exit(127);
}
return (EXIT_FAILURE);
}
shell_info->readfd = file_descriptor;
}
populate_enviroment_list(shell_info);
shell_history(shell_info);
hsh(shell_info, argv);
return (EXIT_SUCCESS);
}
