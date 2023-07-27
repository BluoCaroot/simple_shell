#include "main.h"
void fork_cmd(info_t *info, char *path);
/**
 * print_env - prints environment
 * @info: info struct
 * Return: void
 */
void print_env(info_t *info)
{
	list_t *temp;

	temp = info->env;
	while (temp)
	{
		write(1, temp->str, _strlen(temp->str));
		write(1, "\n", 1);
		temp = temp->next;
	}
}
/**
 * isbuilt_in - checks if a command is a builtin
 * @info: info struct
 * Return: 1 or 0
 */
int isbuilt_in(info_t *info)
{
	if (!(strncmp(info->argv[0], "exit", 4)))
	{
		free_info(info, 1);
		exit(info->status);
	}
	if (!(strncmp(info->argv[0], "env", 3)))
		print_env(info);
	else
		return (0);
	return (1);

}
/**
 * iscommand - checks if given command exists
 * @path: path of command
 * Return: 1 or 0
 */
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
/**
 * find_cmd - finds command to launch
 * @info: info struct
 * Return: 1 or 0
 */
int find_cmd(info_t *info)
{
	int i, l, r = 0;
	char **paths = NULL, *temp, *token, *path;

	l = 0;
	if (info->path)
	{
		temp = _strdup(info->path);
		for (i = 0; temp[i]; ++i)
		{
			if (temp[i]  == ':')
				l++;
		}
		paths = malloc((l + 2) * sizeof(char *));
		if (!paths)
			return (0);
		token = strtok(temp, ":");
		for (i = 0; i <= l; ++i)
		{
			paths[i] = (char *) malloc(sizeof(char) * (_strlen(token) + 1));
			_strcpy(paths[i], token);
			token = strtok(NULL, ":");
		}
		paths[l + 1] = NULL;
		path = malloc(1024);
		for (i = 0; i < l + 1 && !r; ++i)
		{
			path = _strcpy(path, paths[i]);
			_strcat(path, "/");
			_strcat(path, info->argv[0]);
			if (iscommand(path))
			{
				free(info->argv[0]);
				info->argv[0] = _strdup(path);
				fork_cmd(info, path);
				r = 1;
			}
		}
		free(temp);
	}
	if (!r && iscommand(info->argv[0]))
	{
		fork_cmd(info, info->argv[0]);
		r = 1;
	}
	for (i = 0; paths && paths[i]; ++i)
	{
		free(paths[i]);
	}
	if (paths)
		free(paths);
	free(path);
	return (r);
}
/**
 * fork_cmd - forks and calls exceve
 * @info: info struct
 * @path: path of command
 * Return: void
 */
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
		val = execve(path, info->argv, list_to_str(info->env));
		if (val == -1)
		{
			if (errno == EACCES)
				exit(2);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
			info->status = WEXITSTATUS(info->status);
	}
}
