/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:00:37 by sjoukni           #+#    #+#             */
/*   Updated: 2025/06/03 14:31:41 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// void	exec_pipeline_cmd(t_exec_data *data, int in_fd, int out_fd)
// {
// 	char	*cmd_path;

// 	set_child_signals();
// 	dup2(in_fd, STDIN_FILENO);
// 	dup2(out_fd, STDOUT_FILENO);
// 	if (handle_redirections(data->cmd, data->alloc_list))
// 		exit(EXIT_FAILURE);
// 	if (!data->cmd->args || !data->cmd->args[0])
// 		exit(EXIT_SUCCESS);
// 	if (is_builtin_name(data->cmd->args[0]))
// 		exit(exec_builtin(&data->shell, data->cmd, data->alloc_list));
// 	cmd_path = check_cmd(data->paths, data->cmd->args[0], data->alloc_list);
// 	if (!cmd_path)
// 	{
// 		ft_putstr_fd(data->cmd->args[0], 2);
// 		ft_putstr_fd(": command not found\n", 2);
// 		exit(127);
// 	}
// 	execve(cmd_path, data->cmd->args, data->shell->envp);
// 	perror("execve");
// 	exit(EXIT_FAILURE);
// }

// static void	exec_middle_cmd(t_cmd *cmd, t_pipex_info *pinfo)
// {
// 	int			pipe_fd[2];
// 	t_exec_data	data;

// 	if (pipe(pipe_fd) == -1)
// 	{
// 		perror("pipe");
// 		exit(EXIT_FAILURE);
// 	}
// 	pinfo->last_pid = fork();
// 	if (pinfo->last_pid == 0)
// 	{
// 		close(pipe_fd[0]);
// 		data.shell = pinfo->shell;
// 		data.cmd = cmd;
// 		data.paths = pinfo->paths;
// 		data.alloc_list = pinfo->alloc_list;
// 		exec_pipeline_cmd(&data, pinfo->prev_fd, pipe_fd[1]);
// 	}
// 	close(pipe_fd[1]);
// 	if (pinfo->prev_fd != STDIN_FILENO)
// 		close(pinfo->prev_fd);
// 	pinfo->prev_fd = pipe_fd[0];
// }

// static void	exec_last_cmd(t_cmd *cmd, t_pipex_info *pinfo)
// {
// 	t_exec_data	data;

// 	pinfo->last_pid = fork();
// 	if (pinfo->last_pid == 0)
// 	{
// 		data.shell = pinfo->shell;
// 		data.cmd = cmd;
// 		data.paths = pinfo->paths;
// 		data.alloc_list = pinfo->alloc_list;
// 		exec_pipeline_cmd(&data, pinfo->prev_fd, STDOUT_FILENO);
// 	}
// 	if (pinfo->prev_fd != STDIN_FILENO)
// 		close(pinfo->prev_fd);
// }

// static void	wait_for_children(t_shell **shell, pid_t last_pid)
// {
// 	int		status;
// 	pid_t	wpid;

// 	wpid = waitpid(-1, &status, 0);
// 	while (wpid > 0)
// 	{
// 		if (wpid == last_pid)
// 		{
// 			if (WIFEXITED(status))
// 				(*shell)->exit_status = WEXITSTATUS(status);
// 			else if (WIFSIGNALED(status))
// 				(*shell)->exit_status = 128 + WTERMSIG(status);
// 			else
// 				(*shell)->exit_status = 1;
// 		}
// 		wpid = waitpid(-1, &status, 0);
// 	}
// }

// void	pipex(t_shell **shell, t_list *alloc_list)
// {
// 	t_cmd			*cmd;
// 	t_pipex_info	pinfo;

// 	cmd = (*shell)->cmds;
// 	pinfo.shell = *shell;
// 	pinfo.alloc_list = alloc_list;
// 	pinfo.paths = get_paths(shell, alloc_list);
// 	pinfo.prev_fd = dup(STDIN_FILENO);
// 	pinfo.last_pid = 0;
// 	while (cmd && cmd->has_pipe)
// 	{
// 		exec_middle_cmd(cmd, &pinfo);
// 		cmd = cmd->next;
// 	}
// 	if (cmd)
// 		exec_last_cmd(cmd, &pinfo);
// 	wait_for_children(shell, pinfo.last_pid);
// }

#include "execution.h"

int handle_redirections(t_cmd *cmd, t_shell *shell, t_list *alloc_list)
{
	int i = 0;
	int in_fd = -1;
	int out_fd = -1;
	int tmp_fd;

	if (!cmd->rediriction)
		return 0;

	while (cmd->rediriction[i])
	{
		char *file = cmd->rediriction[i];
		if (!file || file[0] == '\0')
		{
			fprintf(stderr, "Invalid redirection file\n");
			return 1;
		}

		int type = cmd->rediriction_ag[i];

		if (type == 0) // infile
		{
			tmp_fd = open(file, O_RDONLY);
			if (tmp_fd < 0)
			{
				perror(file);
				return 1;
			}
			if (in_fd != -1)
				close(in_fd);
			in_fd = tmp_fd;
		}
		else if (type == 1) // outfile overwrite
		{
			tmp_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (tmp_fd < 0)
			{
				perror(file);
				return 1;
			}
			if (out_fd != -1)
				close(out_fd);
			out_fd = tmp_fd;
		}
		else if (type == 2) // outfile append
		{
			tmp_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (tmp_fd < 0)
			{
				perror(file);
				return 1;
			}
			if (out_fd != -1)
				close(out_fd);
			out_fd = tmp_fd;
		}
		else if (type == 3) // heredoc
		{
			if (!read_heredoc(cmd, shell, alloc_list))
				return 1;
			if (in_fd != -1)
				close(in_fd);
			in_fd = cmd->heredoc_fd;
		}
		i++;
	}

	if (in_fd != -1)
	{
		dup2(in_fd, STDIN_FILENO);
		if (in_fd != cmd->heredoc_fd)
			close(in_fd);
	}
	if (out_fd != -1)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	return 0;
}




void exec_pipeline_cmd(t_shell *shell, t_cmd *cmd, char **paths, int in_fd,
						int out_fd, t_list *alloc_list)
{
	char *cmd_path;
	set_child_signals();

	// Step 1: apply redirections first (may include heredoc)
	int redir_failed = handle_redirections(cmd, shell, alloc_list);
	if (redir_failed)
		exit(EXIT_FAILURE);

	// Step 2: only dup input if heredoc didn't override it
	if (cmd->heredoc_fd == -1 && in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
	}

	if (cmd->heredoc_fd != -1)
		close(cmd->heredoc_fd);
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	if (out_fd != STDOUT_FILENO)
		close(out_fd);

	// Step 3: no command
	if (!cmd->args || !cmd->args[0])
		exit(EXIT_SUCCESS);

	// Step 4: builtin
	if (is_builtin_name(cmd->args[0]))
	{
		int ex = exec_builtin(&shell, cmd, alloc_list);
		exit(ex);
	}

	// Step 5: external command
	cmd_path = check_cmd(paths, cmd->args[0], alloc_list);
	if (!cmd_path)
	{
		fprintf(stderr, "%s: command not found\n", cmd->args[0]);
		exit(127);
	}
	execve(cmd_path, cmd->args, shell->envp);
	perror("execve");
	exit(EXIT_FAILURE);
}


void pipex(t_shell **shell, t_list *alloc_list)
{
	int		pipe_fd[2];
	int		in_fd = dup(STDIN_FILENO);
	int		prev_fd = in_fd;
	pid_t	pid;
	char	**paths = get_paths(shell, alloc_list);
	t_cmd	*current = (*shell)->cmds;

	while (current && current->has_pipe)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == 0)
		{
			close(pipe_fd[0]);
			exec_pipeline_cmd(*shell, current, paths, prev_fd, pipe_fd[1], alloc_list);
		}
		close(pipe_fd[1]);
		if (prev_fd != STDIN_FILENO)
			close(prev_fd);
		prev_fd = pipe_fd[0];
		current = current->next;
	}

	if (current)
	{
		pid = fork();
		if (pid == 0)
			exec_pipeline_cmd(*shell, current, paths, prev_fd, STDOUT_FILENO, alloc_list);
		if (prev_fd != STDIN_FILENO)
			close(prev_fd);
	}
	int status;
	pid_t wpid;
	while ((wpid = waitpid(-1, &status, 0)) > 0)
	{
		if (wpid == pid)
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