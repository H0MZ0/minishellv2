/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:37:40 by sjoukni           #+#    #+#             */
/*   Updated: 2025/04/13 18:53:04 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_start_set_find(const char *s1, const char *set)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (s1[i])
	{
		j = 0;
		while (set[j])
		{
			if (set[j] == s1[i])
			{
				count++;
				break ;
			}
			j++;
		}
		if (s1[i] != set[j])
			break ;
		i++;
	}
	return (count);
}

static int	ft_end_set_find(const char *s1, const char *set)
{
	int	j;
	int	count;
	int	len;

	len = ft_strlen(s1) - 1;
	count = 0;
	while (len >= 0)
	{
		j = 0;
		while (set[j])
		{
			if (set[j] == s1[len])
			{
				count++;
				break ;
			}
			j++;
		}
		if (s1[len] != set[j])
			break ;
		len--;
	}
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*ptr;
	int		len;

	if (!s1 || !set)
		return (NULL);
	start = ft_start_set_find(s1, set);
	end = ft_end_set_find(s1, set);
	len = ft_strlen(s1);
	ptr = ft_substr(s1, start, (len - end) - start);
	return (ptr);
}
