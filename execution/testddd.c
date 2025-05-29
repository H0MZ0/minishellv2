/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testddd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:37:50 by hakader           #+#    #+#             */
/*   Updated: 2025/05/29 16:46:38 by hakader          ###   ########.fr       */
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
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(outfile, flags, 0644);
	if (fd < 0)
	{
		shell->exit_status = EXIT_FAILURE;
		return (oi_err(outfile));
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
		return (oi_err(infile));
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (EXIT_SUCCESS);
}

int	in_out(t_shell *shell)
{
	int		i, j;
	int		found;
	t_cmd	*cmd = shell->cmds;

	i = 0;
	while (cmd->rediriction[i])
	{
		found = 0;
		j = 0;
		while (!found && cmd->infiles && cmd->infiles[j])
		{
			if (ft_strcmp(cmd->rediriction[i], cmd->infiles[j]) == 0)
			{
				if (infiless(shell, cmd->infiles[j]))
					return (1);
				found = 1;
			}
			j++;
		}
		j = 0;
		while (!found && cmd->outfiles && cmd->outfiles[j])
		{
			if (ft_strcmp(cmd->rediriction[i], cmd->outfiles[j]) == 0)
			{
				if (outfiless(shell, cmd->outfiles[j], j))
					return (1);
				found = 1;
			}
			j++;
		}
		i++;
	}
	return (0);
}
