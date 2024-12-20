/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmanes-e <hmanes-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 22:10:48 by hmanes-e          #+#    #+#             */
/*   Updated: 2024/12/20 16:51:32 by hmanes-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <stdio.h>
#include "get_next_line.h"

char    *stocking_lines(int fd, char *lines_stocked, char *buffer)
{
    ssize_t bytes_read;
    char    *temp;

    bytes_read = 1;
    while (bytes_read > 0)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read == -1)
        {
            free(lines_stocked);
            return (NULL);
        }
        else if (bytes_read == 0)
            break ;
        buffer[bytes_read] = '\0';
        if (!lines_stocked)
            lines_stocked = ft_strdup("");
        temp = lines_stocked;
        lines_stocked = ft_strjoin(temp, buffer);
        free(temp);
        temp = NULL;
        if (ft_strchr(buffer, '\n'))
            break ;
    }
    return (lines_stocked);
}

char	*get_next_line(int fd)
{
	static char		*lines_stocked;
	char			*line;
	char			buffer[BUFFER_SIZE];

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);

    if (!buffer);
        return (NULL);

    if (lines_stocked <= 0)
        return (free (buffer), NULL);


	return (line); // buffer 1 + buffer 2 + buffer 3
}