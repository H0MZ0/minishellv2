/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 21:55:41 by hakader           #+#    #+#             */
/*   Updated: 2025/06/16 15:50:29 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	outfiless(t_shell *shell, char *outfile, int j)
{
	int	fd;
	int	flags;

	fd = -1;
	flags = O_WRONLY | O_CREAT;
	if (shell->cmds->append_flags[j])
		flags += O_APPEND;
	else
		flags += O_TRUNC;
	fd = open(outfile, flags, 0644);
	if (fd < 0)
	{
		shell->exit_status = EXIT_FAILURE;
		return (oi_err(shell, outfile));
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (EXIT_SUCCESS);
}

int	infiless(t_shell *shell, char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd < 0)
	{
		shell->exit_status = EXIT_FAILURE;
		return (oi_err(shell, infile));
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (EXIT_SUCCESS);
}

static int	handle_infile(t_shell *shell, t_cmd *cmd, char *redir)
{
	int	j;

	j = 0;
	while (cmd->infiles && cmd->infiles[j])
	{
		if (ft_strcmp(redir, cmd->infiles[j]) == 0)
		{
			if (infiless(shell, cmd->infiles[j]))
				return (1);
			return (0);
		}
		j++;
	}
	return (0);
}

static int	handle_outfile(t_shell *shell, t_cmd *cmd, char *redir)
{
	int	j;

	j = 0;
	while (cmd->outfiles && cmd->outfiles[j])
	{
		if (ft_strcmp(redir, cmd->outfiles[j]) == 0)
		{
			if (outfiless(shell, cmd->outfiles[j], j))
				return (1);
			return (0);
		}
		j++;
	}
	return (0);
}

int	in_out(t_shell *shell)
{
	int		i;
	int		result;
	t_cmd	*cmd;

	cmd = shell->cmds;
	i = 0;
	while (cmd->rediriction[i])
	{
		result = handle_infile(shell, cmd, cmd->rediriction[i]);
		if (result == 1)
			return (1);
		if (result == 0)
		{
			result = handle_outfile(shell, cmd, cmd->rediriction[i]);
			if (result == 1)
				return (1);
		}
		i++;
	}
	return (0);
}
