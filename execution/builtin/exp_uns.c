/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_uns.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 02:53:42 by hakader           #+#    #+#             */
/*   Updated: 2025/04/25 02:53:44 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	execute_export(t_cmd *cmd, t_env **envp)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		if (!is_valid_key(cmd->args[i]))
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
		}
		else if (ft_strchr(cmd->args[i], '='))
			add_or_update_env(envp, cmd->args[i]);
		i++;
	}
	return (0);
}

int	execute_unset(t_cmd *cmd, t_env **envp)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		if (is_valid_key(cmd->args[i]))
			remove_env_var(envp, cmd->args[i]);
		else
		{
			ft_putstr_fd("unset: `", 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
		}
		i++;
	}
	return (0);
}
