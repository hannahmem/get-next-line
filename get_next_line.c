#include <stdio.h>

char	*get_next_line(int fd)
{
	static char		stash;
	size_t			arr_size;
	char			*arr;
	char			line;
	unsigned int	i;
	char			*buffer;

	buffer = malloc(BUFFER_SIZE + 1) * sizeof(char);
	i = 0;
	arr_size = ft_strlen(arr_size);
	while (arr_size < buffer)
	{
		stash = read(0, arr, 1);
		i++;
		if (stash < 1) 
		{
			if (i < 1)
				return (0);
			else
				return buffer;
		}
		else if (i > (BUFFER_SIZE - 2))
			return buffer;
		if (arr[i] == "\n")
			line += stash;
	}
	return (line);
}