/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:58:09 by hakader           #+#    #+#             */
/*   Updated: 2025/05/01 18:30:45 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_env *ft_new_env(char *key, char *value)
{
	t_env *new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

void ft_envadd_back(t_env **env, char *key, char *value)
{
	t_env *new = ft_new_env(key, value);
	t_env *last;

	if (!env || !new)
		return ;
	if (*env == NULL)
	{
		*env = new;
		return;
	}
	last = *env;
	while (last->next)
		last = last->next;
	last->next = new;
}

int	check_exp(t_cmd *cmd, t_env **env)
{
	int	i;

	i = 0;
	if (!cmd->args[1])
	{
		print_list_env(env);
		return (1);
	}
	return (0);
}

int execute_export(t_cmd *cmd, t_env **env)
{
	int		i = 1;
	char	**exp;
	t_env	*tmp;

	if (check_exp(cmd, env))
		return (1);
	while (cmd->args[i])
	{
		exp = ft_split(cmd->args[i], '=');
		tmp = *env;
		while (tmp)
		{
			if (ft_strcmp(tmp->key, exp[0]) == 0)
			{
				if (exp[1])
				{
					free(tmp->value);
					tmp->value = ft_strdup(exp[1]);
				}
				free_array(exp);
				break;
			}
			tmp = tmp->next;
		}
		if (!tmp)
			ft_envadd_back(env, exp[0], exp[1]);
		free_array(exp);
		i++;
	}
	return (1);
}

