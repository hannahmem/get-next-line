#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <stddef.h>
#include <fcntl.h>
#include <unistd.h>

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
# endif

size_t ft_strlen(const char *s);
char *ft_strchr(const char *s, int c);
char *ft_strdup(const char *s1);
char *ft_strjoin(char *s1, const char *s2);
char *ft_substr(const char *s, unsigned int start, size_t len);

#endif