#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>


#define MAXITOKEN 64
#define MAXIARGS 64
#define DELIMITERS " \t\r\n\a"

extern char **environ;

typedef struct linkedList
{
	char *str;
	struct linkedList *next;
} L_LIST;

/* cd_shell.c*/
L_LIST *the_path();
void the_node(L_LIST **ref, char *str);
void sh_freelist(L_LIST *head);
char *sh_getenv(const char *varname);
char *sh_finder(char *cmd, L_LIST *p_list);

/* env1.c*/
int sh_putenv(char *str);
char *sh_strchr(const char *str, int z);
int sh_envsize(void);

/* env2.c*/
int sh_cus_setenv(const char *varname, const char *val, int e);
int sh_cus_unsetenv(const char *varname);

/* error.c*/
void sh_setenv(char **args);
void sh_unsetenv(char **args);
void sh_exit(char **tok);
void sh_env(char **env);
int sh_cdexec(char **tok);

/* exec_line.c*/
int sh_checkempty(ssize_t len, char *b);
int sh_handleempty(char *b, char **lptr);
void sh_terminator(ssize_t len, char *b);
char *sh_buffer(size_t b_size);
char *sh_exbuffer(char *b, size_t b_size);

/* get_builtin.c*/
void sh_exec_builtin(char **tokens, char **env);

/* get_line.c*/
ssize_t sh_getline(char **lineptr, size_t *n, int fd);

/* split_shell.c*/
unsigned int sh_delim(char c, char *delim);
char *sh_strtok(char *srcString, char *delim);

/* cmd_exec.c*/
int sh_writer(int ac, char **av);

/* cmd_exec2.c*/
void sh_semicolon(char *input);
int sh_del_token(char *input, char **tok, int maxitok, char *del);

/* get_help.c*/
char *sh_reader(void);
int sh_strlen(const char *str);
void sh_printer(char *str);
void sh_stderror(char *str);
int sh_strcmp(const char *str1, const char *str2);

/*get_help2*/
char *sh_constr(char *str1, char *str2);
char *sh_strcpy(char *dest, const char *src);
char *sh_strcat(char *dest, const char *src);
int sh_strncmp(const char *s1, const char *s2, size_t n);
char *sh_strdup(const char *str);

/*get_help3*/
void *sh_memcpy(void *dest, const void *src, size_t n);
void *sh_realloc(void *ptr, size_t size);
int shell_env(void);

/*main.c*/
char *sh_checkercmd(char **tokens);
void execute(char **tokens);
int tokenize(char *input, char **tokens, int max_tokens);



#endif
