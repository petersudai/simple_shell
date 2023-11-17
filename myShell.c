#include "shell.h"

#define MAX_COMMAND_LENGTH 100
#define MAX_PATH_LENGTH 1024

void hsh(void);
char *find_command(char *command);
int myBuiltin(char *command);
void fork_command(char *path);

/**
 * hsh - main shell loop
 *
 * Return: void
 */

void hsh(void)
{
	char command[MAX_COMMAND_LENGTH];
	int i, argCount;
	char *args[MAX_COMMAND_LENGTH];
	char **tokens;
	char *command_path;
	char prompt[] = "$ ";

	while (1)
	{
		printf("%s", prompt);
		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			if (feof(stdin))
			{
			printf("\n");
			break;
			}
		}

		command[strcspn(command, "\n")] = '\0';

		args[0] = strtok(command, " ");

		argCount = 1;

		while (argCount < MAX_COMMAND_LENGTH &&
				(args[argCount] = strtok(NULL, " ")) != NULL)
		{
			argCount++;
		}

		tokens = parse_command(command);

		if (tokens[0] != NULL)
		{
			if (strcmp(tokens[0], "exit") == 0)
				exit_shell();
			command_path = find_command(tokens[0]);
			if (command_path != NULL)
			{
				fork_command(command_path);
				free(command_path);
			}
			else if (myBuiltin(tokens[0]) == 0)
			{
			/* executed successfully */
			}
			else
				printf("Command not found: %s\n", tokens[0]);
		}
		/* free the memory allocate for tokens */
		for (i = 0; tokens[i] != NULL; i++)
			free(tokens[i]);
		free(tokens);
	}
}

/**
 * fork_command - this is used to fork
 * @path: forked path
 *
 * Return: 0
 */

void fork_command(char *path)
{
	char **argv;

	argv = (char **)malloc(2 * sizeof(char *));

	if (argv == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	argv[0] = path;
	argv[1] = NULL;

	if (execve(path, argv, environ) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
	free(argv);
}

/**
 * myBuiltin - Finds a built-in command
 * @command: The command to check
 * Return: 1 if it's a built-in, 0 otherwise
 */

int myBuiltin(char *command)
{
	/* Check if the command is a built-in command */
	if (strcmp(command, "exit") == 0)
	{
		exit_shell();
		return (1);
	}
	else if (strcmp(command, "cd") == 0)
	{
		return (1);
	}
	else if (strcmp(command, "env") == 0)
	{
		print_environment();
		return (1);
	}
	return (0);
}

/**
 * find_command - Finds a command in PATH
 * @command: The command to find
 * Return: The full path of the command if found, NULL otherwise
 */

char *find_command(char *command)
{
	char *path = NULL;
	char *env_path = getenv("PATH");
	char *token = strtok(env_path, ":");
	size_t full_path_len;
	char *full_path;

	while (token != NULL)
	{
		full_path_len = strlen(token) + strlen(command) + 2;
		full_path = (char *)malloc(full_path_len);

		if (full_path == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}

		snprintf(full_path, full_path_len, "%s/%s", token, command);

		if (access(full_path, X_OK) == 0)
		{
			path = strdup(full_path);
			free(full_path);
			break;
		}
		free(full_path);
		token = strtok(NULL, ":");
	}
	return (path);
}
