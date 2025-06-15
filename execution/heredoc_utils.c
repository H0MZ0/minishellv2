/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:36:13 by sjoukni           #+#    #+#             */
/*   Updated: 2025/06/15 17:03:00 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	open_last_heredoc_file(t_cmd *cmd, t_heredoc_tmp *heredoc,
		char *filename)
{
	if (cmd->heredoc_fd != -1)
		close(cmd->heredoc_fd);
	cmd->heredoc_fd = open(filename, O_RDONLY);
	if (cmd->heredoc_fd == -1)
	{
		perror("open heredoc");
		return (0);
	}
	cmd->heredoc_delim = heredoc->delim;
	cmd->heredoc_expand = heredoc->expand;
	return (1);
}

int	handle_single_heredoc(t_cmd *cmd, t_shell *shell, t_list *alloc_list, int i)
{
	char			*filename;
	t_heredoc_tmp	*heredoc;

	heredoc = &cmd->heredocs[i];
	filename = generate_tmp_name(alloc_list);
	if (!filename)
		return (0);
	if (!handle_heredoc_child(heredoc, shell, alloc_list, filename))
		return (0);
	if (i == cmd->heredoc_count - 1)
		return (open_last_heredoc_file(cmd, heredoc, filename));
	return (1);
}

int	open_heredoc_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	return (fd);
}

void	close_heredoc_fd(t_cmd *cmd)
{
	if (cmd->heredoc_fd != -1 && cmd->heredoc_fd != STDIN_FILENO)
	{
		close(cmd->heredoc_fd);
		cmd->heredoc_fd = -1;
	}
}
