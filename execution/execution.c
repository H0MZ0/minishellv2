/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:49:04 by hakader           #+#    #+#             */
/*   Updated: 2025/05/08 18:46:16 by hakader          ###   ########.fr       */
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
				update_exit_status((*shell), pid);
		}
		return (1);
	}
	return (0);
}

static void	exec_child(t_shell *shell, char *cmd)
{
	if (shell->cmds->infile != NULL)
		infile(shell->cmds->infile);
	if (shell->cmds->outfile != NULL)
		outfile(shell->cmds->outfile);
	execve(cmd, &shell->cmds->args[0], shell->envp);
	perror("execve failed");
}

static void exec_command(t_shell *shell, char **paths, t_list **alloc_list)
{
	pid_t	pid;
	char	*cmd;

	if (is_builtin_name(shell->cmds->args[0]))
	{
		if (shell->cmds->has_pipe)
		{
			pid = fork();
			if (pid == 0)
			{
				if (shell->cmds->infile)
					infile(shell->cmds->infile);
				if (shell->cmds->outfile)
					outfile(shell->cmds->outfile);
				exit(exec_builtin(&shell, (*alloc_list)));
			}
			else
				update_exit_status(shell, pid);
		}
		else
		{
			exec_builtin(&shell, (*alloc_list));
		}
		return;
	}

	cmd = check_cmd(paths, shell->cmds->args[0], (*alloc_list));
	if (cmd)
	{
		pid = fork();
		if (pid == 0)
			exec_child(shell, cmd);
		else
		update_exit_status(shell, pid);
	}
	else
		set_cmd_not_found(shell, shell->cmds->args[0]);
}

void execution_part(t_shell *shell, t_list **alloc_list)
{
	char **paths;

	if (!shell->cmds)
		return;

	paths = get_paths(&shell, (*alloc_list));
	while (shell->cmds)
	{
		if (shell->cmds->has_pipe)
		{
			pipex(&shell, (*alloc_list));
			while (shell->cmds && shell->cmds->has_pipe)
				shell->cmds = shell->cmds->next;
			if (shell->cmds)
				shell->cmds = shell->cmds->next;
			continue;
		}

		exec_command(shell, paths, alloc_list);
		shell->cmds = shell->cmds->next;
	}
}
