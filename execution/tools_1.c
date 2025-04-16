/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:58:34 by hakader           #+#    #+#             */
/*   Updated: 2025/04/16 13:10:41 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*src;
	size_t	i;
	char	*str;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (NULL);
	if (len + start > ft_strlen(s))
		len = ft_strlen(s) - start;
	src = (char *)s + start;
	i = 0;
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < len)
	{
		*str = *src;
		str++;
		src++;
		i++;
	}
	*str = '\0';
	str = str - i;
	return (str);
}

int	ft_strcmp(const char *str1, const char *str2)
{
	int i;

	i = 0;
	if (!str1 || !str2)
		return (1);
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

char	**aloc(char *cmd1, char *cmd2, char *cmd3, char *cmd4)
{
	char	**commad;

	if (!cmd1 || !cmd2 || !cmd3 || !cmd4)
		return (NULL);
	commad = malloc(sizeof(char *) * 5);
	if (!commad)
		return (NULL);
	commad[0] = ft_strdup(cmd1);
	commad[1] = ft_strdup(cmd2);
	commad[2] = ft_strdup(cmd3);
	commad[3] = ft_strdup(cmd4);
	commad[4] = NULL;
	return (commad);
}
