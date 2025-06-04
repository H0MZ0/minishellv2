/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:06:13 by sjoukni           #+#    #+#             */
/*   Updated: 2025/06/04 11:03:41 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	return (b);
}

int	check_new_line_buffer(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

// void	free_memory(char **str)
// {
// 	if (str && *str)
// 	{
// 		free(*str);
// 		*str = NULL;
// 	}
// }

char	*process_line(char **full_buff, int new_line_index, t_list *alloc_list)
{
    char	*line;
    char	*temp;

    // Extract the line up to the newline character
    line = ft_substr(*full_buff, 0, new_line_index, alloc_list); // Exclude '\n'
    temp = ft_substr(*full_buff, new_line_index + 1,
            ft_strlen(*full_buff) - new_line_index - 1, alloc_list);
    *full_buff = temp;
    return (line);
}

char	*read_and_join(int fd, char **full_buff, t_list *alloc_list)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = (char *)ft_malloc(BUFFER_SIZE + 1, &alloc_list);
	if (!buffer)
		return (NULL);
	while (check_new_line_buffer(*full_buff) == -1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			if (bytes_read < 0)
			{
				// free(buffer);
				// free_memory(full_buff);
				return (NULL);
			}
			break ;
		}
		buffer[bytes_read] = '\0';
		*full_buff = ft_strjoin(*full_buff, buffer, alloc_list);
	}
	// free(buffer);
	return (*full_buff);
}

char	*get_next_line(int fd, t_list *alloc_list)
{
	static char	*full_buff;
	int			new_line_index;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	if (!read_and_join(fd, &full_buff, alloc_list))
		return (NULL);
	if (!full_buff || *full_buff == '\0')
	{
		// if (full_buff && *full_buff == '\0')
		// 	free_memory(&full_buff);
		return (NULL);
	}
	new_line_index = check_new_line_buffer(full_buff);
	if (new_line_index >= 0)
		return (process_line(&full_buff, new_line_index, alloc_list));
	line = ft_strdup(full_buff, alloc_list);
	// free_memory(&full_buff);
	return (line);
}

