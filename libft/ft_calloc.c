/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 10:00:17 by sjoukni           #+#    #+#             */
/*   Updated: 2025/06/16 15:05:06 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size, t_list *alloc_list)
{
	void	*ptr;

	if (size != 0 && count > __SIZE_MAX__ / size)
		return (NULL);
	ptr = ft_malloc(count * size, &alloc_list);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}
