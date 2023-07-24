#include "main.h"
void fork_cmd(info_t *info, char *path);
void print_env(info_t *info)
{
	list_t *temp;
	temp = info->env;
	while(temp)
	{
	write(1, temp->str, _strlen(temp->str));
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
	struct stat fileStat;

	if (stat(path, &fileStat) == 0)
	{
		if (fileStat.st_mode & S_IXUSR || fileStat.st_mode & S_IXGRP || fileStat.st_mode & S_IXOTH) 
			return (1);
	return (0);
	}
		return (0);
}

int find_cmd(info_t *info)
{
	int i, cnt = 0;
        char * temp = strtok(info->path, ":"), **paths;

        for (i = 0; info->path[i]; ++i)
                if (info->path[i] == ':')
                        cnt++;
        paths = malloc(sizeof(char *) * (cnt + 2));
        i = 0;
        while (temp)
        {
                paths[i] = temp;
                temp = strtok(NULL, ":");
                i++;
        }
      	paths[i] = NULL;
        
	for (i = 0; i < cnt + 2; ++i)
	{
		temp = _strcat(paths[i], info->argv[0]);
		if (iscommand(temp))
		{
			fork_cmd(info, temp);
			return (1);
		}
	}
        return (0);
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
	return;
}
