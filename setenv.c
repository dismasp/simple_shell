#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int setenv_builtin(char *variable, char *value)
{
int overwrite = 1; /* set to 1 to allow overwriting existing variable*/
int result = setenv(variable, value, overwrite);
if (result == -1)
{
fprintf(stderr, "Error setting environment variable: %s\n", variable);
return (1);
}
return (0);

}

int unsetenv_builtin(char *variable)
{
int result = unsetenv(variable);
if (result == -1)
{

fprintf(stderr, "Error unsetting environment variable: %s\n", variable);
return (1);
}
return (0);
}

int main(int argc, char *argv[])
{
if (argc < 2)
{
fprintf(stderr, "Usage: %s [setenv | unsetenv] [VARIABLE] [VALUE]\n", argv[0]);
return (1);
}

if (strcmp(argv[1], "setenv") == 0)
{
if (argc < 4)
{
fprintf(stderr, "Usage: %s setenv VARIABLE VALUE\n", argv[0]);
return (1);
}
return (setenv_builtin(argv[2], argv[3]));

}
else if (strcmp(argv[1], "unsetenv") == 0)
{
if (argc < 3)
{
fprintf(stderr, "Usage: %s unsetenv VARIABLE\n", argv[0]);

return (1);
}

return unsetenv_builtin(argv[2]);
}
else
{
fprintf(stderr, "Unknown command: %s\n", argv[1]);
return (1);

}
}
