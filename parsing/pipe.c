/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:00:37 by sjoukni           #+#    #+#             */
/*   Updated: 2025/04/24 16:22:50 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void pipex(t_cmd *cmd, char **envp)
{
	int pipe_fd[2];
	pid_t pid1, pid2;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return;
	}

	pid1 = fork();
	if (pid1 == 0)
	{
		set_child_signals();

		if (cmd->infile)
		{
			int fd_in = open(cmd->infile, O_RDONLY);
			if (fd_in < 0)
			{
				perror("open infile");
				exit(1);
			}
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}

		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);

		execve(cmd->args[0], cmd->args, envp);
		perror("execve");
		exit(1);
	}


	pid2 = fork();
	if (pid2 == 0)
{
	set_child_signals(); 

	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[1]);
	close(pipe_fd[0]);

	t_cmd *next_cmd = cmd->next;

	if (next_cmd->outfile)
	{
		int flags = O_WRONLY | O_CREAT;
		if (next_cmd->append)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;

		int fd_out = open(next_cmd->outfile, flags, 0644);
		if (fd_out < 0)
		{
			perror("open outfile");
			exit(1);
		}
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}

	execve(next_cmd->args[0], next_cmd->args, envp);
	perror("execve");
	exit(1);
}


	close(pipe_fd[0]);
	close(pipe_fd[1]);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

