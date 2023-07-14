include "main.h"
int main()
{
	char *buff, *argv[];
	size_t n,r;
	n = 0;
	while(1)
	{
		write(1, "$ ", 2);
		r = getline(&buff, &n, 0);
		if (r == -1)
		{
			write(1, "\n", 1);
			break;
		}
		argv

	}
}
