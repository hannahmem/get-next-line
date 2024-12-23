/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmanes-e <hmanes-e@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 22:10:48 by hmanes-e          #+#    #+#             */
/*   Updated: 2024/12/23 15:04:53 by hmanes-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// static char	*ft_strdup(char *s1)
// {
// 	char	*copy;

// 	copy = malloc(ft_strlen(s1) + 1);
// 	if (copy == NULL)
// 		return (NULL);
// 	ft_strcpy(copy, s1);
// 	return (copy);
// }

// static void	*ft_memmove(void *dst, const void *src, size_t len)
// {
// 	unsigned char		*dst_ptr;
// 	const unsigned char	*src_ptr;
// 	size_t				i;

// 	if (!src && !dst)
// 		return (NULL);
// 	dst_ptr = (unsigned char *)dst;
// 	src_ptr = (const unsigned char *)src;
// 	i = 0;
// 	if (dst_ptr > src_ptr)
// 	{
// 		while (len--)
// 			dst_ptr[len] = src_ptr[len];
// 	}
// 	else
// 	{
// 		while (i < len)
// 		{
// 			dst_ptr[i] = src_ptr[i];
// 			i++;
// 		}
// 	}
// 	return (dst);
// }

// static void	*ft_memcpy(void	*dst, const void *src, size_t n)
// {
// 	unsigned char	*dst_ptr;
// 	unsigned char	*src_ptr;

// 	if (src == NULL && dst == NULL)
// 		return (NULL);
// 	dst_ptr = (unsigned char *) dst;
// 	src_ptr = (unsigned char *) src;
// 	while (n > 0)
// 	{
// 		*(dst_ptr++) = *(src_ptr++);
// 		n--;
// 	}
// 	return (dst);
// }

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
	static char	*lines_stocked;
	char		buffer[BUFFER_SIZE + 1];
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (handle_read_error(&lines_stocked));
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		lines_stocked = ft_strjoin(lines_stocked, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	if (!lines_stocked || *lines_stocked == '\0')
		return (handle_read_error(&lines_stocked));
	return (extract_line(&lines_stocked));
}

// #include <stdio.h>
// int main(void)
// {
//     int fd;
//     char *line;

//     fd = open("text.txt", O_RDONLY);
//     if (fd == -1)
//     {
//         perror("Error opening file");
//         return (1);
//     }
//     while ((line = get_next_line(fd)) != NULL)
//     {
//         printf("%s\n", line);
//         free(line);
//     }
//     close(fd);
//     return (0);
// }
