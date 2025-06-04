/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:01:14 by sjoukni           #+#    #+#             */
/*   Updated: 2025/06/03 16:02:07 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	child_heredoc(t_heredoc_tmp *heredoc, t_shell *shell,
						t_list *alloc_list, int *pipe_fd)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	close(pipe_fd[0]);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, heredoc->delim) == 0)
		{
			free(line);
			break;
		}
		if (heredoc->expand)
			line = expand_token_value(line, shell, alloc_list);
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		clear_history();
		free(line);
	}
	close(pipe_fd[1]);
	exit(0);
}

static int	handle_heredoc_child(t_heredoc_tmp *heredoc, t_shell *shell,
								t_list *alloc_list, int *pipe_fd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return 0;
	}
	if (pid == 0)
		child_heredoc(heredoc, shell, alloc_list, pipe_fd);
	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(pipe_fd[0]);
		shell->exit_status = 130;
		return 0;
	}
	return 1;
}

int read_heredoc(t_cmd *cmd, t_shell *shell, t_list *alloc_list)
{
    int	pipe_fd[2];
    int	i;
    t_heredoc_tmp *heredoc;

    i = 0;
    cmd->heredoc_fd = -1;
    while (i < cmd->heredoc_count)
    {
        heredoc = &cmd->heredocs[i];
        if (pipe(pipe_fd) == -1)
        {
            perror("pipe");
            return 0;
        }
        if (!handle_heredoc_child(heredoc, shell, alloc_list, pipe_fd))
            return 0;
        if (i == cmd->heredoc_count - 1)
        {
            cmd->heredoc_fd = pipe_fd[0];
            cmd->heredoc_delim = heredoc->delim;
            cmd->heredoc_expand = heredoc->expand;
        }
        else
            close(pipe_fd[0]); 
        i++;
    }
    return 1;
}


