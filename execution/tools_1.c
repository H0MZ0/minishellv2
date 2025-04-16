/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:58:34 by hakader           #+#    #+#             */
/*   Updated: 2025/04/16 13:55:54 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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

char	**get_paths(t_cmd *f_cmd, t_env *env_list)
{
	(void)f_cmd;
	int	i;

	i = 0;
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PATH") == 0)
			return(ft_split(tmp->value, ':'));
		tmp = tmp->next;
	}
	return (NULL);
}
