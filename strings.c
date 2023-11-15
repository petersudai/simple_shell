#include "shell.h"

/**
 * strLength - Calculates the length of a string.
 * @s: The input string.
 * Return: The length of the string.
 */
int strLength(char *s)
{
	int len = 0;

	while (s[len] != '\0')
	{
		len++;
	}
	return (len);
}

/**
 * strCompare - Compares two strings
 * @s1: first string
 * @s2: second string
 * Return: 0 strings are equal, positive s1 > s2, negative if s1 < s2
 */
int strCompare(char *s1, char *s2)
{
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

/**
 * strConcat - Concatenates two strings.
 * @dest: The destination string
 * @src: The source string
 * Return: The concatenated string
 */
char *strConcat(char *dest, char *src)
{
	int dest_len = strLength(dest);
	int i;

	for (i = 0; src[i] != '\0'; i++)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';
	return (dest);
}

/**
 * strFree - Frees memory allocated for string
 * @str: string to free
 */
void strFree(char *str)
{
	free(str);
}

/**
 * strDuplicate - Duplicates a string.
 * @str: The string to duplicate.
 *
 * Return: The duplicated string.
 */
char *strDuplicate(const char *str)
{
	size_t len;
	char *duplicate;

	len = strlen(str) + 1;
	duplicate = malloc(len);
	if (duplicate == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	strcpy(duplicate, str);
	return (duplicate);
}
