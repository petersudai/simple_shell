#include "shell.h"

/**
 * print_environment - prints current environment variables
 */

void print_environment(void)
{
	char **env = environ;

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
