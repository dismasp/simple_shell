#include "shell.h"


/**
 * entry_point - entry point of the program
 * hsh - Execute the shell command line.
 * @shell_info: Pointer to the shell info struct.
 * @argv: Null terminated array of command-line argument strings.
 *
 * This function executes the shell command line by reading input from
 * the user, parsing it into individual commands, and executing those
 * commands. It uses the specified `shell_info` struct to maintain state
 * across multiple command invocations.
 *
 * Return: void.
 */

void hsh(info_t *shell_info, char **argv);

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
fflush(stdout);
exit(127);
}
return (EXIT_FAILURE);
}
shell_info->readfd = file_descriptor;
}
 /* populate_environment_list(shell_info); */
/* shell_history(shell_info); */
hsh(shell_info, argv);
return (EXIT_SUCCESS);
}

/**
 * hsh - Execute the shell command line.
 */

void hsh(info_t *shell_info, char **argv)
{
    /* implementation of the hsh function */
}

