/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:49:04 by hakader           #+#    #+#             */
/*   Updated: 2025/04/20 17:34:16 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
int	path_cmd(t_cmd *f_cmd, char **envp)
{
	if (f_cmd->args[0][0] == '/')
	{
		if (access(f_cmd->args[0], X_OK) == 0)
		{
			pid_t	pid = fork();
			if (pid == 0)
			{
				execve(f_cmd->args[0], &f_cmd->args[0], envp);
			}
			else
				waitpid(pid, NULL, 0);
		}
		return (1);
	}
	return (0);
}
void	execution_part(t_cmd *f_cmd, t_env *env_list, char **envp)
{
	char	**paths;
	char	*cmd;

	if (path_cmd(f_cmd, envp))
		return ;
	printf("cmd not work\n");
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
	free_arr(paths);
}
