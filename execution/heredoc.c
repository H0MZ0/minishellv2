/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:52:28 by sjoukni           #+#    #+#             */
/*   Updated: 2025/06/15 17:00:57 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*generate_tmp_name(t_list *alloc_list)
{
	int		i;
	char	*num;
	char	*filename;
	char	*base;

	i = 1;
	base = "/tmp/.here_doc";
	while (1)
	{
		num = ft_itoa(i, alloc_list);
		filename = ft_strjoin(base, num, alloc_list);
		if (access(filename, F_OK) != 0)
			return (filename);
		i++;
	}
}

static void	child_heredoc(t_heredoc_tmp *heredoc, t_shell *shell,
		t_list *alloc_list, const char *filename)
{
	int		fd;
	char	*line;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	fd = open_heredoc_file(filename);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO, alloc_list);
		if (!line)
			break ;
		if (ft_strcmp(line, heredoc->delim) == 0)
			break ;
		if (heredoc->expand)
			line = expand_token_value(line, shell, alloc_list);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	exit(0);
}

int	handle_heredoc_child(t_heredoc_tmp *heredoc, t_shell *shell,
		t_list *alloc_list, const char *filename)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (0);
	}
	if (pid == 0)
		child_heredoc(heredoc, shell, alloc_list, filename);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		shell->exit_status = 130;
		return (0);
	}
	return (1);
}

int	read_heredoc(t_cmd *cmd, t_shell *shell, t_list *alloc_list)
{
	int	i;

	i = 0;
	cmd->heredoc_fd = -1;
	while (i < cmd->heredoc_count)
	{
		if (!handle_single_heredoc(cmd, shell, alloc_list, i))
			return (0);
		i++;
	}
	return (1);
}
