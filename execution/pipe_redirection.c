/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:35:24 by sjoukni           #+#    #+#             */
/*   Updated: 2025/06/04 11:41:50 by sjoukni          ###   ########.fr       */
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
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
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

static int	process_redir(char **files, int *types, int *in_fd, int *out_fd, t_shell *shell, t_list *alloc_list, t_cmd *cmd)
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
		if (types[i] == 3 && read_heredoc(cmd, shell, alloc_list))
			return (1);
		i++;
	}
	return (0);
}

int	handle_redirections(t_cmd *cmd, t_list *alloc_list, t_shell *shell) 
{
    int	in_fd;
    int	out_fd;

    (void)alloc_list;
    in_fd = -1;
    out_fd = -1;
    if (!cmd->rediriction)
        return (0);
    if (process_redir(cmd->rediriction, cmd->rediriction_ag, &in_fd, &out_fd, shell, alloc_list, cmd))
        return (1);
	printf("here");
    if (cmd->heredoc_fd != -1) 
    {
        dup2(cmd->heredoc_fd, STDIN_FILENO);
        close(cmd->heredoc_fd);
        cmd->heredoc_fd = -1; // Mark as closed
    }
    else if (in_fd != -1) // Redirect input file descriptor
    {
        dup2(in_fd, STDIN_FILENO);
        close(in_fd);
        in_fd = -1; // Mark as closed
    }
    if (out_fd != -1) // Redirect output file descriptor
    {
        dup2(out_fd, STDOUT_FILENO);
        close(out_fd);
        out_fd = -1; // Mark as closed
    }
    return (0);
}
