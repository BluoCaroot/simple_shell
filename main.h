#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
int _strlen(char *s);
int _strncmp(const char *s1, const char *s2, int n);
char *_strdup(const char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _putchar(char c);
extern char **environ;
/**
 * struct environlst - enviroment list
 * @str: variable value
 * @next: next element
 */
typedef struct environlst
{
	char *str;
	struct environlst *next;
} list_t;
list_t *create_list(void);
#endif
