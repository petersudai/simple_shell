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
	int i;
	char **tokens;
	char *command_path;

	while (1)
	{
		printf("$ ");
		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			printf("\n");
			break;
		}

		command[strcspn(command, "\n")] = '\0';

		printf("Before parse_command\n");
		tokens = parse_command(command);
		printf("After parse_command\n");

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
 * execute_command - execute an external command
 * @tokens: array of strings repping the command and its arguements
 * Return: 0 success, -1 fail
 */

int execute_command(char **tokens)
{
	pid_t pid, wpid;
	int status;

	if (myBuiltin(tokens[0]) == 0)
		return (0);

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		char *path = find_command(tokens[0]);

		if (path != NULL)
		{
			if (execve(path, tokens, NULL) == -1)
			{
				perror("execve");
				fprintf(stderr, "Error executing command: %s\n", tokens[0]);
				free(path);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			fprintf(stderr, "Command not found: %s\n", tokens[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		while ((wpid = waitpid(pid, &status, WUNTRACED)) > 0)
		{
			if (WIFEXITED(status) || WIFSIGNALED(status))
				break;
		}
		if (wpid == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
	}
	return (0);
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

	if (execve(path, argv, NULL) == -1)
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
		exit(0);
	}
	else if (strcmp(command, "cd") == 0)
	{
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
