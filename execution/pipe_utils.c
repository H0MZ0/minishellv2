/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:56:42 by sjoukni           #+#    #+#             */
/*   Updated: 2025/06/15 21:24:50 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	wait_all_processes(pid_t last_pid, t_shell **shell)
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
	}
}

int	setup_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	return (0);
}

void	exec_pipeline_cmd(t_exec_data *data)
{
	char	*cmd_path;

	set_child_signals();
	dup2(data->in_fd, STDIN_FILENO);
	dup2(data->out_fd, STDOUT_FILENO);
	if (handle_redirections(data->cmd, data->alloc_list))
		exit(EXIT_FAILURE);
	if (!data->cmd->args || !data->cmd->args[0])
		exit(EXIT_SUCCESS);
	if (is_builtin_name(data->cmd->args[0]))
		exit(exec_builtin(&data->shell, data->cmd, data->alloc_list));
	cmd_path = check_cmd(data->paths, data->cmd->args[0], data->alloc_list);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(data->cmd->args[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		exit(127);
	}
	execve(cmd_path, data->cmd->args, data->shell->envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	child_exec(t_exec_state *s, int out_fd)
{
	t_exec_data	data;

	data.shell = s->shell;
	data.cmd = s->current;
	data.paths = s->paths;
	data.in_fd = s->prev_fd;
	data.out_fd = out_fd;
	data.alloc_list = s->alloc_list;
	exec_pipeline_cmd(&data);
}
