/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:01:14 by sjoukni           #+#    #+#             */
/*   Updated: 2025/05/30 21:15:05 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	child_heredoc(t_cmd *cmd, t_shell *shell,
						t_list *alloc_list, int *pipe_fd)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	close(pipe_fd[0]);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, cmd->heredocs->delim) == 0)
		{
			free(line);
			break ;
		}
		if (cmd->heredocs->expand)
			line = expand_token_value(line, shell, alloc_list);
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		clear_history();
		free(line);
	}
	close(pipe_fd[1]);
	exit(0);
}

static int	handle_heredoc_child(t_cmd *cmd, t_shell *shell,
								t_list *alloc_list, int *pipe_fd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), 0);
	if (pid == 0)
		child_heredoc(cmd, shell, alloc_list, pipe_fd);
	waitpid(pid, &status, 0);
	close(pipe_fd[1]);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(1, "\n", 1);
		close(pipe_fd[0]);
		shell->exit_status = 130;
		return (0);
	}
	return (1);
}

int	read_heredoc(t_cmd *cmd, t_shell *shell, t_list *alloc_list)
{
	int		pipe_fd[2];
	int		i;

	i = 0;
	while (i < cmd->heredoc_count)
	{
		if (pipe(pipe_fd) == -1)
			return (perror("pipe"), 0);
		cmd->heredocs += i;
		if (!handle_heredoc_child(cmd, shell, alloc_list, pipe_fd))
			return (0);
		if (i == cmd->heredoc_count - 1)
		{
			cmd->heredoc_fd = pipe_fd[0];
			cmd->heredoc_delim = cmd->heredocs->delim;
			cmd->heredoc_expand = cmd->heredocs->expand;
		}
		else
			close(pipe_fd[0]);
		cmd->heredocs -= i;
		i++;
	}
	return (1);
}
