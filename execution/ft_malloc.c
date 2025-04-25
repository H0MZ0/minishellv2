/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:53:14 by hakader           #+#    #+#             */
/*   Updated: 2025/04/25 17:45:55 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static t_list *alloc_list;

void *ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		perror("malloc");
	ft_lstadd_back(&alloc_list, ft_lstnew(ptr));
	return (ptr);
}

void	free_all(void)
{
	t_list	*tmp;
	while (alloc_list)
	{
		tmp = alloc_list->next;
		free(alloc_list->content);
		free(alloc_list);
		alloc_list = tmp;
	}
}