/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:49:04 by hakader           #+#    #+#             */
/*   Updated: 2025/04/19 17:59:55 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	execution_part(t_cmd *f_cmd, t_env *env_list, char **envp)
{
	char	**paths;
	char	*cmd;

	paths = get_paths(env_list);
	if (is_builtin(f_cmd, env_list))
		return ;
	cmd = check_cmd(paths, f_cmd->args[0]);
	if (cmd)
	{
		pid_t	pid = fork();
		if (pid == 0)
			execve(cmd, &f_cmd->args[0], envp);
		else
			waitpid(pid, NULL, 0);
		free(cmd);
	}
	else
		printf("%s: command not found\n", f_cmd->args[0]);
}
