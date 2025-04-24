/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:16:14 by hakader           #+#    #+#             */
/*   Updated: 2025/04/24 22:56:36 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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
