/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:49:04 by hakader           #+#    #+#             */
/*   Updated: 2025/06/14 18:33:32 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	exec_child(t_shell *shell, char *cmd)
{
	int	error;

	error = 0;
	set_child_signals();
	if (shell->cmds->heredoc_delim)
	{
		if (shell->cmds->heredoc_fd == -1)
			exit(shell->exit_status);
		dup2(shell->cmds->heredoc_fd, STDIN_FILENO);
		close(shell->cmds->heredoc_fd);
	}
	else if (shell->cmds->infiles || shell->cmds->outfiles)
	{
		if (in_out(shell))
			exit (shell->exit_status);
	}
	execve(cmd, &shell->cmds->args[0], shell->envp);
	perror("execve failed");
	exit(EXIT_FAILURE);
}

static void	exec_command(t_shell *shell, char **paths, t_list **alloc_list)
{
	pid_t		pid;
	char		*cmd;
	struct stat	sa;

	if (shell->cmds->args && stat(shell->cmds->args[0], &sa) == 0
		&& S_ISDIR(sa.st_mode)
		&& ft_strchr(shell->cmds->args[0], '/'))
		return (err_dir(shell));
	if (if_builtin(shell, (*alloc_list)))
		return ;
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

void	execution_part(t_shell *shell, t_list **alloc_list)
{
	char	**paths;
	t_cmd	*cmd;
	t_cmd	*pipe_cmd;

	paths = get_paths(&shell, (*alloc_list));
	while (shell->cmds)
	{
		cmd = shell->cmds;
		if (cmd->heredocs && !cmd->has_pipe)
		{
			if (!read_heredoc(cmd, shell, *alloc_list))
			{
				shell->cmds = cmd->next;
				continue ;
			}
		}
		if (cmd->has_pipe)
		{
			pipe_cmd = cmd;
			while (pipe_cmd && pipe_cmd->has_pipe)
			{
				if (pipe_cmd->heredocs)
				{
					if (!read_heredoc(pipe_cmd, shell, *alloc_list))
					{
						shell->cmds = pipe_cmd->next;
						break ;
					}
				}
				pipe_cmd = pipe_cmd->next;
			}
			if (pipe_cmd && pipe_cmd->heredocs)
			{
				if (!read_heredoc(pipe_cmd, shell, *alloc_list))
				{
					shell->cmds = pipe_cmd->next;
					continue ;
				}
			}
			pipex(&shell, *alloc_list);
			while (shell->cmds && shell->cmds->has_pipe)
			{
				if (shell->cmds->heredoc_fd != -1
					&& shell->cmds->heredoc_fd != STDIN_FILENO)
				{
					close(shell->cmds->heredoc_fd);
					shell->cmds->heredoc_fd = -1;
				}
				shell->cmds = shell->cmds->next;
			}
			if (shell->cmds)
			{
				if (shell->cmds->heredoc_fd != -1
					&& shell->cmds->heredoc_fd != STDIN_FILENO)
				{
					close(shell->cmds->heredoc_fd);
					shell->cmds->heredoc_fd = -1;
				}
				shell->cmds = shell->cmds->next;
			}
			continue ;
		}
		exec_command(shell, paths, alloc_list);
		if (cmd->heredoc_fd != -1 && cmd->heredoc_fd != STDIN_FILENO)
		{
			close(cmd->heredoc_fd);
			cmd->heredoc_fd = -1;
		}
		shell->cmds = cmd->next;
	}
}
