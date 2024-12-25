/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmanes-e <hmanes-e@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 18:09:32 by hmanes-e          #+#    #+#             */
/*   Updated: 2024/12/25 18:32:37 by hmanes-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_strdup(char *s1)
{
	char	*copy;

	copy = malloc(ft_strlen(s1) + 1);
	if (copy == NULL)
		return (NULL);
	ft_strcpy(copy, s1);
	return (copy);
}

static char	*line_content(char *lines_stocked, int i)
{
	char	*line;
	int		j;

	line = malloc(i + 2);
	if (!line)
		return (NULL);
	j = 0;
	while (j <= i)
	{
		line[j] = lines_stocked[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*extract_line(char **lines_stocked)
{
	char	*line;
	char	*temp;
	int		i;

	if (!*lines_stocked || **lines_stocked == 0)
		return (NULL);
	i = 0;
	while ((*lines_stocked)[i] && (*lines_stocked)[i] != '\n')
		i++;
	if ((*lines_stocked)[i] == '\n')
	{
		line = line_content(*lines_stocked, i);
		temp = *lines_stocked;
		*lines_stocked = ft_strjoin(NULL, *lines_stocked + i + 1);
		free(temp);
	}
	else
	{
		line = ft_strjoin(NULL, *lines_stocked);
		free(*lines_stocked);
		*lines_stocked = NULL;
	}
	return (line);
}

static char	*handle_read_error(char **lines_stocked)
{
	free(*lines_stocked);
	*lines_stocked = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*lines_stocked[FD_MAX];
	char		buffer[BUFFER_SIZE + 1];
	int			bytes_read;

	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (handle_read_error(&lines_stocked[fd]));
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!lines_stocked[fd])
			lines_stocked[fd] = ft_strdup(buffer);
		else
			lines_stocked[fd] = ft_strjoin(lines_stocked[fd], buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	if (!lines_stocked[fd] || *lines_stocked[fd] == '\0')
		return (handle_read_error(&lines_stocked[fd]));
	return (extract_line(&lines_stocked[fd]));
}

// #include <stdio.h>
// int main(void)
// {
// 	int fd1, fd2, fd3;
// 	char *line;
// 	int i = 0;

// 	fd1 = open("text.txt", O_RDONLY);
// 	fd2 = open("text2.txt", O_RDONLY);
// 	fd3 = open("text3.txt", O_RDONLY);
// 	if (fd1 == -1 || fd2 == -1 || fd3 == -1)
// 	{
// 		perror("Error opening file");
// 		if (fd1 != -1) close(fd1);
// 		if (fd2 != -1) close(fd2);
// 		if (fd3 != -1) close(fd3);
// 		return (1);
// 	}
// 	while (i < 10) {
// 		if ((line = get_next_line(fd1)) != NULL)
// 		{
// 			printf("FD1: %s\n", line);
// 			free(line);
// 		}
// 		if ((line = get_next_line(fd2)) != NULL)
// 		{
// 			printf("FD2: %s\n", line);
// 			free(line);
// 		}
// 		if ((line = get_next_line(fd3)) != NULL)
// 		{
// 			printf("FD3: %s\n", line);
// 			free(line);
// 		}
// 		i++;
// 	}
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// 	return (0);
// }
