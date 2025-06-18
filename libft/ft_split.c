/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:26:10 by sjoukni           #+#    #+#             */
/*   Updated: 2025/06/16 14:41:18 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_word(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((s[i] != c) && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

int	ft_len(const char *s, char c, int *start)
{
	int	len;

	len = 0;
	while (s[*start] == c)
		(*start)++;
	while (s[*start + len] && s[*start + len] != c)
		len++;
	return (len);
}

char	**ft_split(char const *s, char c, t_list *alloc_list)
{
	t_split	split;
	int		start;
	int		index;
	int		word_len;

	if (!s)
		return (NULL);
	split.count = count_word(s, c);
	split.ptr = (char **)ft_malloc((split.count + 1) * sizeof(char *),
			&alloc_list);
	if (!split.ptr)
		return (NULL);
	start = 0;
	index = 0;
	while (index < split.count)
	{
		word_len = ft_len(s, c, &start);
		split.ptr[index] = ft_substr(s, start, word_len, alloc_list);
		if (!split.ptr[index])
			return (NULL);
		start += word_len;
		index++;
	}
	split.ptr[split.count] = NULL;
	return (split.ptr);
}
