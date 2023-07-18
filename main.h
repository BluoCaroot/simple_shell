#ifndef MAIN_H
#define MAIN_H

/* libraries */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>

/* string functions*/

int _strlen(char *s);
int _strncmp(const char *s1, const char *s2, int n);
char *_strdup(const char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _putchar(char c);

/* error functions */

void eputs(char *str);
void eputchar(char c);

/* structs */

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

typedef struct passedinfo
{
        char *arg;
        char **argv;
        char *path;
        int argc;
        list_t *env;
        int err;
        int status;
        int fd;
        int linecnt;
} info_t;
#define INFO_INIT {NULL, NULL, NULL, 0, NULL, 0, 0, 0, 0}

/* global variables and macros */

extern char **environ;
#define BUF_MAX 1024
#define BUF_FLUSH -1

/* shell commands */

int isbuilt_in(info_t *info);
int iscommand(char *path);
int interactive(info_t *info);
char *path(list_t *head);


#endif
