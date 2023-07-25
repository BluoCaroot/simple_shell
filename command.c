#include "main.h"
void fork_cmd(info_t *info, char *path);
void print_env(info_t *info)
{
	list_t *temp;
	
	temp = info->env;
	while(temp)
	{
		write(1, temp->str, _strlen(temp->str));
		write(1, "\n", 1);
		temp = temp->next;
	}
}
int isbuilt_in(info_t *info)
{
	if (!(strncmp(info->argv[0], "exit", 4)))
		exit(0);
	if (!(strncmp(info->argv[0], "env", 3)))
		print_env(info);
	else
		return (0);
	return (1);

}

int iscommand(char *path)
{
	int x;
	struct stat fileStat;
	
	x = stat(path, &fileStat);
	if (!x)
	{
		if (fileStat.st_mode & S_IFREG) 
			return (1);
		return (0);
	}
		return (0);
}

int find_cmd(info_t *info)
{
	int i, l, r = 0;
	char **paths, *temp, *token, *path;

	l = 0, temp = _strdup(info->path);
	for (i = 0; temp[i]; ++i)
	{
		if (temp[i]  == ':')
			l++;
	}
	paths = malloc((l + 2) * sizeof(char *));
	if (!paths)
		return (-1);
	token = strtok(temp, ":");
	for (i = 0; i <= l; ++i)
	{
		paths[i] = (char *) malloc(sizeof(char) * (_strlen(token) + 1));
		_strcpy(paths[i], token);
		token = strtok(NULL, ":");
	}
	paths[l + 1] = NULL;
	free(temp);
	path = malloc(1024);
	for (i = 0; i < l + 1 && !r; ++i)
	{
		path = _strcpy(path, paths[i]);
		_strcat(path, "/");
		_strcat(path, info->argv[0]);

		if (iscommand(path))
		{
			info->argv[0] = path;
			fork_cmd(info, path);
			r = 1;
		}
	}
	for (i = 0; paths[i]; ++i)
	{
		free(paths[i]);
	}
	free(paths);
        return (r);
}

void fork_cmd(info_t *info, char *path)
{
	int pid, val;

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
	}
	else if (!pid)
	{
		val = execve(path, info->argv, NULL);
		if (val == -1)
			perror("Error");
	}
	else
		wait(NULL);
}
