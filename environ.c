#include "main.h"

/**
 * _getenv - gets environments
 * @name: environment variable to get
 * Return: pointer to the variable if found NULL if not
 */

char *_getenv(const char *name)
{
	size_t namelen = _strlen(name);
	char **envp = environ;

	while (*envp != NULL)
	{
		if (strncmp(name, *envp, namelen) == 0 && (*envp)[namelen] == '=')
		{
			return (&((*envp)[namelen + 1]));
		}
		envp++;
	}
	return (NULL);
}
