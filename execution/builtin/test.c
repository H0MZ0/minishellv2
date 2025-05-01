/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:42:18 by hakader           #+#    #+#             */
/*   Updated: 2025/05/01 18:42:42 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	is_valid_key(char *s)
{
	int	i = 0;

	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	while (s[i])
	{
		if (s[i] == '=')
			break;
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	*get_key(char *arg)
{
	int		i = 0;

	while (arg[i] && arg[i] != '=')
		i++;
	return (ft_substr(arg, 0, i));
}

char	*get_value(char *arg)
{
	char	*equal = ft_strchr(arg, '=');
	if (!equal)
		return (NULL);
	return (ft_strdup(equal + 1));
}

void	update_or_add(t_env **env, char *key, char *value)
{
	t_env *tmp = *env;

	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (value)
			{
				free(tmp->value);
				tmp->value = ft_strdup(value);
			}
			return;
		}
		tmp = tmp->next;
	}
	ft_envadd_back(env, key, value);
}

int	execute_export(t_cmd *cmd, t_env **env)
{
	int		i = 1;
	char	*key;
	char	*value;

	if (check_exp(cmd, env))
		return (1);
	while (cmd->args[i])
	{
		if (!is_valid_key(cmd->args[i]))
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			i++;
			continue;
		}
		key = get_key(cmd->args[i]);
		value = get_value(cmd->args[i]); // NULL if no '='
		update_or_add(env, key, value);
		free(key);
		if (value)
			free(value);
		i++;
	}
	return (1);
}
