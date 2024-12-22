/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmanes-e <hmanes-e@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 22:10:48 by hmanes-e          #+#    #+#             */
/*   Updated: 2024/12/22 23:14:47 by hmanes-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dst_ptr;
	const unsigned char	*src_ptr;
	size_t				i;

	if (!src && !dst)
		return (NULL);
	dst_ptr = (unsigned char *)dst;
	src_ptr = (const unsigned char *)src;
	i = 0;
	if (dst_ptr > src_ptr)
	{
		while (len--)
			dst_ptr[len] = src_ptr[len];
	}
	else
	{
		while (i < len)
		{
			dst_ptr[i] = src_ptr[i];
			i++;
		}
	}
	return (dst);
}

static void	*ft_memcpy(void	*dst, const void *src, size_t n)
{
	unsigned char	*dst_ptr;
	unsigned char	*src_ptr;

	if (src == NULL && dst == NULL)
		return (NULL);
	dst_ptr = (unsigned char *) dst;
	src_ptr = (unsigned char *) src;
	while (n > 0)
	{
		*(dst_ptr++) = *(src_ptr++);
		n--;
	}
	return (dst);
}

static char	*new_line(char **lines_stocked)
{
	char	*line;
	int		i;

	if (!*lines_stocked)
		return (NULL);
	i = 0;
	while ((*lines_stocked)[i] != '\0' && (*lines_stocked)[i] != '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, *lines_stocked, i);
	line[i] = '\0';
	if ((*lines_stocked)[i] == '\n')
	{
		ft_memmove(*lines_stocked, *lines_stocked + i + 1,
			strlen(*lines_stocked + i + 1) + 1);
	}
	else
	{
		free(*lines_stocked);
		*lines_stocked = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*lines_stocked;
	char		buffer[BUFFER_SIZE + 1];
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		lines_stocked = ft_strjoin(lines_stocked, buffer);
		if (ft_strchr(lines_stocked, '\n'))
			break ;
	}
	if (bytes_read < 0 || (bytes_read == 0 && !lines_stocked))
	{
		free(lines_stocked);
		lines_stocked = NULL;
		return (NULL);
	}
	return (new_line(&lines_stocked));
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
