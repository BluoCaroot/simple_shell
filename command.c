#include "main.h"
int isbuilt_in(info_t *info)
{
	if (info->argv[0] == "exit")
		exit(0);
	if (info->argv[0] == "env")
		env(info);
	else
		return (0);
	return (1);

}

int iscommand(char *path)
{
	struct stat fileStat;

	if (stat(path, &fileStat) == 0)
	{
        if (fileStat.st_mode & S_IXUSR || 
            fileStat.st_mode & S_IXGRP || 
            fileStat.st_mode & S_IXOTH) 
		return (1);
	else
	       	return (0);
	}
	else
		return (0);
}

