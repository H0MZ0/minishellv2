/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:16:08 by hakader           #+#    #+#             */
/*   Updated: 2025/05/30 21:10:00 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	err_cd(char *err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(err, 2);
	ft_putendl_fd(": No such file or directory", 2);
}

void	err_cdd(void)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("cd: ", 2);
	ft_putendl_fd("please type relative or absolute path", 2);
}

int	err_cddd(void)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("cd: ", 2);
	ft_putendl_fd("too many arguments", 2);
	return (EXIT_FAILURE);
}

int	execute_cd(t_shell *shell, t_cmd *cmd, t_env **env, t_list *alloc_list)
{
	char	*old_pwd;
	char	*new_pwd;

	if (count_args(shell->cmds->args) > 2)
		return (err_cddd());
	if (!cmd->args[1])
		return (err_cdd(), EXIT_FAILURE);
	old_pwd = getcwd(NULL, 0);
	if (chdir(cmd->args[1]) == -1)
	{
		free (old_pwd);
		return (err_cd(cmd->args[1]), EXIT_FAILURE);
	}
	update_env(env, "OLDPWD", old_pwd, alloc_list);
	free (old_pwd);
	new_pwd = getcwd(NULL, 0);
	update_env(env, "PWD", new_pwd, alloc_list);
	free (new_pwd);
	return (EXIT_SUCCESS);
}
