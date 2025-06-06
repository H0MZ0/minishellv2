/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:58:34 by hakader           #+#    #+#             */
/*   Updated: 2025/06/02 16:45:08 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	count_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return (0);
	while (args[i])
		i++;
	return (i);
}

void	update_env(t_env **env, char *key, char *replace, t_list *alloc_list)
{
	t_env	*tmp;

	if (!key || !replace || !env)
		return ;
	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			tmp->value = ft_strdup(replace, alloc_list);
			return ;
		}
		tmp = tmp->next;
	}
	tmp = ft_calloc(1, sizeof(t_env), alloc_list);
	tmp->key = ft_strdup(key, alloc_list);
	tmp->value = ft_strdup(replace, alloc_list);
	tmp->next = *env;
	*env = tmp;
}

char	**get_paths(t_shell **shell, t_list *alloc_list)
{
	t_env	*tmp;

	tmp = (*shell)->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PATH") == 0 && tmp->value && tmp->value[0])
			return (ft_split(tmp->value, ':', alloc_list));
		tmp = tmp->next;
	}
	return (NULL);
}

char	*check_cmd(char **paths, char *cmd, t_list *alloc_list)
{
	char	*command;
	int		i;

	if (!cmd || cmd[0] == '\0')
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd, alloc_list));
		else
			return (NULL);
	}
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		command = ft_strjoin(paths[i], "/", alloc_list);
		command = ft_strjoin(command, cmd, alloc_list);
		if (access(command, X_OK) == 0)
			return (command);
		i++;
	}
	return (NULL);
}

int	check_options(t_cmd *cmd, char *msg)
{
	int		i;

	i = 0;
	while (cmd->args[i])
	{
		if (cmd->args[i][0] == '-')
		{
			if (cmd->args[i][1])
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(msg, 2);
				ft_putendl_fd(": no options allowed", 2);
				return (EXIT_FAILURE);
			}
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
