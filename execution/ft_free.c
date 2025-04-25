/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:50:31 by hakader           #+#    #+#             */
/*   Updated: 2025/04/25 01:42:45 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	free_arr(char **str)
{
	int	i;

	i = 0;
	if (!str || !(*str))
		return ;
	while (str[i])
	{
		free (str[i]);
		i++;
	}
	free (str);
}

t_memblock *g_alloc_list = NULL;

void *ft_malloc(size_t size)
{
	void *ptr;
	t_memblock *new_block;

	ptr = malloc(size);
	if (!ptr)
	{
		perror("ft_malloc");
		exit(EXIT_FAILURE);
	}
	new_block = (t_memblock *)malloc(sizeof(t_memblock));
	if (!new_block)
	{
		perror("ft_malloc");
		exit(EXIT_FAILURE);
	}

	new_block->ptr = ptr;
	new_block->next = g_alloc_list;
	g_alloc_list = new_block;

	return (ptr);
}

void ft_free_all(void)
{
	t_memblock	*current;
	t_memblock	*next;

	current = g_alloc_list;
	while (current)
	{
		next = current->next;
		free(current->ptr);
		free(current);
		current = next;
	}
	g_alloc_list = NULL;
}
