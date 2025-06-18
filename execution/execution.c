/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:49:04 by hakader           #+#    #+#             */
/*   Updated: 2025/06/16 15:22:26 by sjoukni          ###   ########.fr       */
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
		{
			exit(shell->exit_status);
		}
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
		&& S_ISDIR(sa.st_mode) && ft_strchr(shell->cmds->args[0], '/'))
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

static void	handle_non_pipe_command(t_shell *shell, char **paths,
		t_list **alloc_list)
{
	t_cmd	*cmd;

	cmd = shell->cmds;
	if (cmd->heredocs && !read_heredoc(cmd, shell, *alloc_list))
	{
		shell->cmds = cmd->next;
		return ;
	}
	exec_command(shell, paths, alloc_list);
	close_heredoc_fd(cmd);
	shell->cmds = cmd->next;
}

int	heredoc_pipe(t_cmd *cmd, t_shell *shell, t_list *alloc_list)
{
	t_cmd	*pipe_cmd;

	pipe_cmd = cmd;
	while (pipe_cmd)
	{
		if (pipe_cmd->heredocs && !read_heredoc(pipe_cmd, shell, alloc_list))
		{
			while (shell->cmds && shell->cmds->has_pipe)
			{
				close_heredoc_fd(shell->cmds);
				shell->cmds = shell->cmds->next;
			}
			if (shell->cmds)
			{
				close_heredoc_fd(shell->cmds);
				shell->cmds = shell->cmds->next;
			}
			return (0);
		}
		if (!pipe_cmd->has_pipe)
			break ;
		pipe_cmd = pipe_cmd->next;
	}
	return (1);
}

void	execution_part(t_shell *shell, t_list **alloc_list)
{
	char	**paths;
	t_cmd	*cmd;

	paths = get_paths(&shell, (*alloc_list));
	while (shell->cmds)
	{
		cmd = shell->cmds;
		if (cmd->has_pipe)
			handle_pipes(shell, alloc_list);
		else
			handle_non_pipe_command(shell, paths, alloc_list);
	}
}
