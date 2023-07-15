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
 * _strcmp - compares two strings
 *
 * @s1: input value
 * @s2: input value
 *
 * Return: s1[i] - s2[i]
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
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
char *_strcat(char *dest, char *src)
{
	int i = 0, j = 0;

	while (dest[i])
		i++;
	while (src[j])
		dest[i] = src[j], i++, j++;
	dest[i] = src[j];
	return (dest);
}

/**
 * _putchar - writes the chracter c to stdout
 * @c: the character to print
 *
 * Return: on success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
