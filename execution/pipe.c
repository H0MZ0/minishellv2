/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:00:37 by sjoukni           #+#    #+#             */
/*   Updated: 2025/06/01 14:19:21 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "execution.h"
int handle_redirections(t_cmd *cmd, t_list *alloc_list)
{
	int i = 0;
	int in_fd = -1;
	int out_fd = -1;
	int tmp_fd;

	while (cmd->rediriction[i] && cmd->rediriction_ag[i])
	{
		char *file = cmd->rediriction[i];

		if (cmd->rediriction_ag[i] == 0) // <
		{
			tmp_fd = open(file, O_RDONLY);
			if (tmp_fd < 0)
			{
				perror(file);
				return (1);
			}
			if (in_fd != -1)
				close(in_fd);
			in_fd = tmp_fd;
		}
		else if (cmd->rediriction_ag[i] == 1) // >
		{
			tmp_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (tmp_fd < 0)
			{
				perror(file);
				return (1);
			}
			if (out_fd != -1)
				close(out_fd);
			out_fd = tmp_fd;
		}
		else if (cmd->rediriction_ag[i] == 2) // >>
		{
			tmp_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (tmp_fd < 0)
			{
				perror(file);
				return (1);
			}
			if (out_fd != -1)
				close(out_fd);
			out_fd = tmp_fd;
		}
		i++;
	}
	if (in_fd != -1)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != -1)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	return (0);
}



void exec_pipeline_cmd(t_shell *shell, t_cmd *cmd, char **paths, int in_fd,
						int out_fd, t_list *alloc_list)
{
	char *cmd_path;
	set_child_signals();
	dup2(in_fd, STDIN_FILENO);
	dup2(out_fd, STDOUT_FILENO);
    int redir_failed = handle_redirections(cmd, alloc_list);
    if (redir_failed)
	    exit(EXIT_FAILURE); 


	if (!cmd->args || !cmd->args[0])
	{
		// ft_putstr_fd("here\n", 2);
		exit(EXIT_SUCCESS);
	}

	if (is_builtin_name(cmd->args[0]))
	{
		exit(exec_builtin(&shell, cmd, alloc_list));
	}

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
