/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:49:04 by hakader           #+#    #+#             */
/*   Updated: 2025/04/16 15:46:25 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	execution_part(t_cmd *f_cmd, t_env *env_list, char **av, char **envp)
{
	char	**paths;
	char	*cmd;

	paths = get_paths(env_list);
	cmd = check_cmd(paths, f_cmd->args[0]);
	if (cmd)
	{
		pid_t	id = fork();
		if (id == 0)
		execve(cmd, av, envp);
	}
	else
		printf("%s: command not found\n", f_cmd->args[0]);
}
