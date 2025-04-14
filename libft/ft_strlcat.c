/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:10:21 by sjoukni           #+#    #+#             */
/*   Updated: 2025/04/13 18:53:04 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	lens;
	size_t	lend;
	size_t	i;

	lens = ft_strlen(src);
	if (dstsize == 0)
		return (lens);
	lend = ft_strlen(dst);
	if (lend >= dstsize || dstsize == 0)
		return (lens + dstsize);
	i = 0;
	while (src[i] && lend + i < dstsize - 1)
	{
		dst[lend + i] = src[i];
		i++;
	}
	dst[lend + i] = 0;
	return (lend + lens);
}
