/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:00:37 by sjoukni           #+#    #+#             */
/*   Updated: 2025/05/13 10:37:59 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
// #include <sys/wait.h>

void handle_redirections(t_cmd *cmd)
{
	int fd = -1;
	int i = 0;

	while (cmd->infiles && cmd->infiles[i])
	{
		fd = open(cmd->infiles[i], O_RDONLY);
		if (fd < 0)
		{
			perror(cmd->infiles[i]);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	if (fd != -1)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	fd = -1;
	i = 0;
	while (cmd->outfiles && cmd->outfiles[i])
	{
		int flags = O_WRONLY | O_CREAT;
		if (cmd->append_flags && cmd->append_flags[i] == 1)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;

		fd = open(cmd->outfiles[i], flags, 0644);
		if (fd < 0)
		{
			perror(cmd->outfiles[i]);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	if (fd != -1)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}


void exec_pipeline_cmd(t_shell *shell, char **paths, int in_fd,
						int out_fd, t_list *alloc_list)
{
	char *cmd_path;

	set_child_signals();
	dup2(in_fd, STDIN_FILENO);
	dup2(out_fd, STDOUT_FILENO);
	handle_redirections(shell->cmds);

	if (!shell->cmds->args || !shell->cmds->args[0])
		exit(EXIT_SUCCESS);

	if (is_builtin_name(shell->cmds->args[0]))
		exit(exec_builtin(&shell, alloc_list));

	cmd_path = check_cmd(paths, shell->cmds->args[0], alloc_list);
	if (!cmd_path)
	{
		fprintf(stderr, "%s: command not found\n", shell->cmds->args[0]);
		exit(127);
	}
	execve(cmd_path, shell->cmds->args, shell->envp);
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
			exec_pipeline_cmd((*shell), paths, prev_fd, pipe_fd[1], alloc_list);
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
			 exec_pipeline_cmd((*shell), paths, prev_fd, STDOUT_FILENO, alloc_list);
		if (prev_fd != STDIN_FILENO)
			close(prev_fd);
	}
	// int status, exit_code;
	// waitpid(pid, &status, 0);
	// if (WIFEXITED)
	// 	exit_code = WEXITSTATUS(status);
	while (wait(NULL) > 0)
		;
	// free_array(paths);
}