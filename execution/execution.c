/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:49:04 by hakader           #+#    #+#             */
/*   Updated: 2025/05/05 20:25:48 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	path_cmd(t_shell **shell)
{
	pid_t	pid;

	if ((*shell)->cmds->args[0][0] == '/')
	{
		if (access((*shell)->cmds->args[0], X_OK) == 0)
		{
			pid = fork();
			if (pid == 0)
			{
				execve((*shell)->cmds->args[0],
					&(*shell)->cmds->args[0], (*shell)->envp);
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

static void	exec_command(t_cmd *f_cmd, char **paths,
						char **envp, t_list *alloc_list)
{
	pid_t	pid;
	char	*cmd;

	cmd = check_cmd(paths, f_cmd->args[0], alloc_list);
	if (cmd)
	{
		pid = fork();
		if (pid == 0)
			exec_child(f_cmd, cmd, envp);
		else
			waitpid(pid, NULL, 0);
	}
	else
		printf("%s: command not found\n", f_cmd->args[0]);
}

void	execution_part(t_shell **shell, t_list *alloc_list)
{
	char	**paths;
	// t_cmd	*tmp;

	paths = get_paths(shell, alloc_list);
	while ((*shell)->cmds)
	{
		// tmp = (*shell)->cmds;
		if (path_cmd(shell))
			(*shell)->cmds = (*shell)->cmds->next;
		else if (is_builtin(shell, alloc_list))
			(*shell)->cmds = (*shell)->cmds->next;
		else
		{
			exec_command((*shell)->cmds, paths, (*shell)->envp, alloc_list);
			if ((*shell)->env->next)
				(*shell)->cmds = (*shell)->cmds->next;
			else
				(*shell)->cmds = (*shell)->cmds->next;
		}
	}
}
