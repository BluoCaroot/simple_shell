#include "main.h"

void eputs(char *str)
{
	int i;

	for (i = 0; str[i]; ++i)
		eputchar(str[i]);
}

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
