#include "main.h"
/**
 * eputs - puts string to stderr
 * @str: string to put
 * Return: void
 */
void eputs(char *str)
{
	int i;

	for (i = 0; str[i]; ++i)
		eputchar(str[i]);
}
/**
 * eputchar - puts char to stderr
 * @c: char to put
 * Return: void
 */
void eputchar(char c)
{
	static int i;
	static char BUFF[BUF_MAX];

	if (c == BUF_FLUSH || i == BUF_MAX)
	{
		write(2, BUFF, i);
		i = 0;
		return;
	}
	BUFF[i++] = c;
}
