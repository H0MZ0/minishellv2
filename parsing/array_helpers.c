/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:56:41 by sjoukni           #+#    #+#             */
/*   Updated: 2025/05/31 16:49:23 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**append_str_array(char **arr, char *new_str, t_list *alloc_list)
{
	char	**new_arr;

	int (i), (j);
	i = 0;
	while (arr && arr[i])
		i++;
	new_arr = ft_malloc(sizeof(char *) * (i + 2), &alloc_list);
	if (!new_arr)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new_arr[j] = arr[j];
		j++;
	}
	new_arr[i] = new_str;
	new_arr[i + 1] = NULL;
	return (new_arr);
}

int	get_int_array_length(int *arr)
{
	int	i = 0;

	if (!arr)
		return (0);
	while (arr[i] != -1)
		i++;
	return (i);
}


int	*append_int_array(int *arr, int value, t_list *alloc_list)
{
	int	*new_arr;
	int	i = get_int_array_length(arr);
	int	j = 0;

	new_arr = ft_malloc(sizeof(int) * (i + 2), &alloc_list);
	if (!new_arr)
		return (NULL);
	while (j < i)
	{
		new_arr[j] = arr[j];
		j++;
	}
	new_arr[i] = value;
	new_arr[i + 1] = -1;
	return (new_arr);
}


t_heredoc_tmp	*alloc_array(t_heredoc_tmp *old, int new_count,
	t_list *alloc_list)
{
	t_heredoc_tmp	*new_array;
	int				i;

	new_array = ft_malloc(sizeof(t_heredoc_tmp) * new_count, &alloc_list);
	i = 0;
	if (!old)
		return (new_array);
	while (i < new_count - 1)
	{
		new_array[i] = old[i];
		i++;
	}
	return (new_array);
}
