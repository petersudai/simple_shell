#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * _strlen - Calculates the length of a string.
 * @s: The input string.
 * Return: The length of the string.
 */
int _strlen(char *s) {
    int len = 0;
    while (s[len] != '\0') {
        len++;
    }
    return len;
}

/**
 * _strcmp - Compares two strings.
 * @s1: The first string.
 * @s2: The second string.
 * Return: 0 if the strings are equal, positive if s1 > s2, negative if s1 < s2.
 */
int _strcmp(char *s1, char *s2) {
    while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

/**
 * _strcat - Concatenates two strings.
 * @dest: The destination string.
 * @src: The source string.
 * Return: The concatenated string.
 */
char *_strcat(char *dest, char *src) {
    int dest_len = _strlen(dest);
    int i;

    for (i = 0; src[i] != '\0'; i++) {
        dest[dest_len + i] = src[i];
    }

    dest[dest_len + i] = '\0';
    return dest;
}

