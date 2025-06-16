/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:35:24 by sjoukni           #+#    #+#             */
/*   Updated: 2025/06/16 14:10:20 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	open_input(char *file, int *in_fd)
{
	int	tmp_fd;

	tmp_fd = open(file, O_RDONLY);
	if (tmp_fd < 0)
	{
		perror(file);
		return (1);
	}
	if (*in_fd != -1)
		close(*in_fd);
	*in_fd = tmp_fd;
	return (0);
}

static int	open_output(char *file, int *out_fd, int append)
{
	int	tmp_fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags += O_APPEND;
	else
		flags += O_TRUNC;
	tmp_fd = open(file, flags, 0644);
	if (tmp_fd < 0)
	{
		perror(file);
		return (1);
	}
	if (*out_fd != -1)
		close(*out_fd);
	*out_fd = tmp_fd;
	return (0);
}

static int	process_redir(char **files, int *types, int *in_fd, int *out_fd)
{
	int	i;

	i = 0;
	while (files[i])
	{
		if (!files[i][0])
		{
			ft_putstr_fd("Invalid redirection file\n", 2);
			return (1);
		}
		if (types[i] == 0 && open_input(files[i], in_fd))
			return (1);
		if (types[i] == 1 && open_output(files[i], out_fd, 0))
			return (1);
		if (types[i] == 2 && open_output(files[i], out_fd, 1))
			return (1);
		i++;
	}
	return (0);
}

void	inout(int in_fd, int in_out)
{
	if (in_fd != -1)
	{
		if (dup2(in_fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(in_fd);
		in_fd = -1;
	}
	if (in_out != -1)
	{
		if (dup2(in_out, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(in_out);
		in_out = -1;
	}
}

int	handle_redirections(t_cmd *cmd, t_list *alloc_list)
{
	int	in_fd;
	int	out_fd;

	(void)alloc_list;
	in_fd = -1;
	out_fd = -1;
	if (!cmd->rediriction)
		return (0);
	if (process_redir(cmd->rediriction, cmd->rediriction_ag, &in_fd, &out_fd))
		exit(1);
	if (cmd->heredoc_fd != -1 && cmd->heredoc_fd != STDIN_FILENO)
	{
		if (dup2(cmd->heredoc_fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(cmd->heredoc_fd);
		cmd->heredoc_fd = -1;
	}
	inout(in_fd, out_fd);
	return (0);
}
