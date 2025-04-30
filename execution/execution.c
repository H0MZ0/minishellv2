/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:49:04 by hakader           #+#    #+#             */
/*   Updated: 2025/04/30 16:06:41 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	path_cmd(t_cmd *f_cmd, char **envp)
{
	pid_t	pid;

	if (f_cmd->args[0][0] == '/')
	{
		if (access(f_cmd->args[0], X_OK) == 0)
		{
			pid = fork();
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

static void	exec_child(t_cmd *f_cmd, char *cmd, char **envp)
{
	if (f_cmd->infile != NULL)
		infile(f_cmd->infile);
	if (f_cmd->outfile != NULL)
		outfile(f_cmd->outfile);
	execve(cmd, &f_cmd->args[0], envp);
}

static void	exec_command(t_cmd *f_cmd, char **paths, char **envp)
{
	pid_t	pid;
	char	*cmd;

	cmd = check_cmd(paths, f_cmd->args[0]);
	if (cmd)
	{
		pid = fork();
		if (pid == 0)
			exec_child(f_cmd, cmd, envp);
		else
			waitpid(pid, NULL, 0);
		free(cmd);
	}
	else
		printf("%s: command not found\n", f_cmd->args[0]);
}

void execution_part(t_cmd *f_cmd, t_env *env_list, char **envp)
{
	char **paths;
	t_cmd *tmp;

	if (path_cmd(f_cmd, envp))
		return ;
	paths = get_paths(env_list);
	while (f_cmd)
	{
		tmp = f_cmd;
		if (is_builtin(f_cmd, env_list))
			return ;
		exec_command(f_cmd, paths, envp);
		if (f_cmd->next)
			f_cmd = f_cmd->next->next;
		else
			f_cmd = f_cmd->next;
		free(tmp);
	}
}

