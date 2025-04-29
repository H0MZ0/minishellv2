/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:53:14 by hakader           #+#    #+#             */
/*   Updated: 2025/04/29 10:45:24 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	*ft_malloc(size_t size, t_alloc *alloc_list)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		perror("malloc");
	ft_lstadd_back(&alloc_list, ft_lstnew(ptr));
	return (ptr);
}

void	free_all(t_alloc *alloc_list)
{
	t_list	*tmp;
	while (alloc_list)
	{
		tmp = alloc_list->next;
		free(alloc_list->ptr);
		free(alloc_list);
		alloc_list = tmp;
	}
}
