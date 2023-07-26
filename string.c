#include "main.h"

/**
 * _strlen - returns the length of a string
 * @s: the string
 * Return: length of string
 */

int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (s[i])
		i++;
	return (i);
}

/**
 * _strncmp - compares first n characters of 2 strings
 * @s1: first string
 * @s2: second string
 * Return: s1 - s2
 */
int _strncmp(const char *s1, const char *s2, int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
		{
			return (s1[i] - s2[i]);
		}
	}
	return (0);
}

/**
 * char *_strcpy -a function that copies the string pointed to by src
 * @dest: copy to
 * @src: copy from
 * Return: string
 */
char *_strcpy(char *dest, char *src)
{
	int l = 0, x;

	while (src[l])
		l++;
	for (x = 0; x < l ; x++)
	{
		dest[x] = src[x];
	}
	dest[l] = '\0';
	return (dest);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination buffer
 */
void _strcat(char *dest, char *src)
{
	int i, j;

	i = 0, j = 0;
	while (dest[i])
		i++;
	while (src[j])
		dest[i++] = src[j++];
	dest[i] = '\0';
}

/** _strdup - duplicates a string
 * @s: string to dup
 * Return: duplicated string
 */
char *_strdup(char *s) {
    int len = _strlen(s) + 1, i;
    char *p = malloc(len);

    if (p != NULL)
    {
	for (i = 0; s[i]; ++i)
		p[i] = s[i];
	p[i] = '\0';
    }
    return (p);
}
