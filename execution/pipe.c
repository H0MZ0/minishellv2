/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:00:37 by sjoukni           #+#    #+#             */
/*   Updated: 2025/06/04 14:35:38 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	exec_pipeline_cmd(t_exec_data *data, int in_fd, int out_fd, t_shell *shell)
{
	char	*cmd_path;

	set_child_signals();
	dup2(in_fd, STDIN_FILENO);
	dup2(out_fd, STDOUT_FILENO);
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	if (out_fd != STDOUT_FILENO)
		close(out_fd);
	if (handle_redirections(data->cmd, data->alloc_list, shell))
		exit(EXIT_FAILURE);
	if (!data->cmd->args || !data->cmd->args[0])
		exit(EXIT_SUCCESS);
	if (is_builtin_name(data->cmd->args[0]))
		exit(exec_builtin(&data->shell, data->cmd, data->alloc_list));
	cmd_path = check_cmd(data->paths, data->cmd->args[0], data->alloc_list);
	if (!cmd_path)
	{
		ft_putstr_fd(data->cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	execve(cmd_path, data->cmd->args, data->shell->envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

static void	exec_middle_cmd(t_cmd *cmd, t_pipex_info *pinfo, t_shell *shell)
{
	int			pipe_fd[2];
	t_exec_data	data;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pinfo->last_pid = fork();
	if (pinfo->last_pid == 0)
	{
		close(pipe_fd[0]);
		data.shell = pinfo->shell;
		data.cmd = cmd;
		data.paths = pinfo->paths;
		data.alloc_list = pinfo->alloc_list;
		exec_pipeline_cmd(&data, pinfo->prev_fd, pipe_fd[1], shell);
	}
	// Parent process: close write end and heredoc fd if needed
	close(pipe_fd[1]);
	if (pinfo->prev_fd != STDIN_FILENO)
		close(pinfo->prev_fd);
	if (cmd->heredoc_fd != -1) {
		close(cmd->heredoc_fd);
		cmd->heredoc_fd = -1;
	}
	pinfo->prev_fd = pipe_fd[0];
}

static void	exec_last_cmd(t_cmd *cmd, t_pipex_info *pinfo, t_shell *shell)
{
	t_exec_data	data;

	pinfo->last_pid = fork();
	if (pinfo->last_pid == 0)
	{
		data.shell = pinfo->shell;
		data.cmd = cmd;
		data.paths = pinfo->paths;
		data.alloc_list = pinfo->alloc_list;
		exec_pipeline_cmd(&data, pinfo->prev_fd, STDOUT_FILENO, shell);
	}
	if (pinfo->prev_fd != STDIN_FILENO)
		close(pinfo->prev_fd);
	if (cmd->heredoc_fd != -1) {
		close(cmd->heredoc_fd);
		cmd->heredoc_fd = -1;
	}
}

static void	wait_for_children(t_shell **shell, pid_t last_pid)
{
	int		status;
	pid_t	wpid;

	wpid = waitpid(-1, &status, 0);
	while (wpid > 0)
	{
		if (wpid == last_pid)
		{
			if (WIFEXITED(status))
				(*shell)->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				(*shell)->exit_status = 128 + WTERMSIG(status);
			else
				(*shell)->exit_status = 1;
		}
		wpid = waitpid(-1, &status, 0);
	}
}

void	pipex(t_shell **shell, t_list *alloc_list)
{
	t_cmd			*cmd;
	t_pipex_info	pinfo;

	cmd = (*shell)->cmds;
	pinfo.shell = *shell;
	pinfo.alloc_list = alloc_list;
	pinfo.paths = get_paths(shell, alloc_list);
	pinfo.prev_fd = dup(STDIN_FILENO);
	pinfo.last_pid = 0;

	while (cmd && cmd->has_pipe)
	{
		exec_middle_cmd(cmd, &pinfo, (*shell));
		cmd = cmd->next;
	}
	if (cmd)
		exec_last_cmd(cmd, &pinfo, (*shell));
	wait_for_children(shell, pinfo.last_pid);
}

