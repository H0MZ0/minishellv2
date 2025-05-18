/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:16:08 by hakader           #+#    #+#             */
/*   Updated: 2025/05/18 17:22:04 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

// int	execute_cd(t_cmd *cmd, t_env **env, t_list *alloc_list)
void	execute_cd(t_shell *shell, t_list *alloc_list)
{
	char	*old_pwd;
	char	*new_pwd;

	if (count_args(shell->cmds->args) > 2)
		return (cd_error(shell, "too many arguments", 1));
	if (!shell->cmds->args[1])
		return (cd_error(shell, "please type relative or absolute path", 2));
	old_pwd = getcwd(NULL, 0);
	if (chdir(shell->cmds->args[1]) == -1)
	{
		perror("cd");
		shell->exit_status = EXIT_FAILURE;
		return ;
	}
	update_env(&shell->env, "OLDPWD", old_pwd, alloc_list);
	new_pwd = getcwd(NULL, 0);
	update_env(&shell->env, "PWD", new_pwd, alloc_list);
	shell->exit_status = EXIT_SUCCESS;
}
