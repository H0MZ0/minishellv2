/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testddd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:37:50 by hakader           #+#    #+#             */
/*   Updated: 2025/05/28 17:50:43 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	outfiless(t_shell *shell, char *outfile, int j)
{
	int (fd), (flags);
	fd = -1;
	flags = O_WRONLY | O_CREAT;
    if (shell->cmds->append_flags[j])
        flags |= O_APPEND;
    else
        flags |= O_TRUNC;
    fd = open(outfile, flags, 0644);
    if (fd < 0)
        return (oi_err(outfile));
    else
    {
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
	return (EXIT_SUCCESS);
}



int	infiless(char *infile)
{
	int	fd;

	fd = -1;
	fd = open(infile, O_RDONLY);
	if (fd < 0)
    {
        perror(infile);
        return (1);
    }
	else
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (EXIT_SUCCESS);
}

// void	in_out(t_shell *shell)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (shell->cmds->rediriction[i])
// 	{
// 		j = 0;
// 		while (shell->cmds->infiles[j])
// 		{
// 			if (ft_strcmp(shell->cmds->rediriction[i], shell->cmds->infiles[j]) == 0)
// 			{
// 				ft_putendl_fd("hhoro", 1);
// 				infiless(shell->cmds->rediriction[i]);
// 				break ;
// 			}
// 			j++;
// 		}
// 		j = 0;
// 		while (shell->cmds->outfiles[j])
// 		{
// 			if (ft_strcmp(shell->cmds->rediriction[i], shell->cmds->outfiles[j]) == 0)
// 			{
// 				ft_putendl_fd("here", 1);
// 				outfiless(shell, shell->cmds->outfiles[j], j);
// 				break ;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }
void	in_out(t_shell *shell)
{
	int		i;
	int		j;
	t_cmd	*cmd = shell->cmds;

	i = 0;
	while (cmd->rediriction[i])
	{
		// Handle heredocs
		// j = 0;
		// while (cmd->heredoc_delim && cmd->heredoc_delim[j])
		// {
		// 	if (ft_strcmp(cmd->rediriction[i], cmd->heredoc_delim[j]) == 0)
		// 	{
		// 		if (cmd->heredoc_fd == -1)
		// 			exit(shell->exit_status);
		// 		dup2(cmd->heredoc_fd, STDIN_FILENO);
		// 		close(cmd->heredoc_fd);
		// 		break ;
		// 	}
		// 	j++;
		// }

		// Handle infiles
		j = 0;
		while (cmd->infiles && cmd->infiles[j])
		{
			if (ft_strcmp(cmd->rediriction[i], cmd->infiles[j]) == 0)
			{
				if (infiless(cmd->infiles[j]))
					exit(EXIT_FAILURE);
				break ;
			}
			j++;
		}

		// Handle outfiles (append or truncate)
		j = 0;
		while (cmd->outfiles && cmd->outfiles[j])
		{
			if (ft_strcmp(cmd->rediriction[i], cmd->outfiles[j]) == 0)
			{
				if (outfiless(shell, cmd->outfiles[j], j))
					exit(EXIT_FAILURE);
				break ;
			}
			j++;
		}
		i++;
	}
}
int	outfilesssssss(t_shell *shell, char *outfile, int j)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (shell->cmds->append_flags[j])
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;

	fd = open(outfile, flags, 0644);
	if (fd < 0)
		return (oi_err(outfile));

	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (oi_err(outfile));
	}

	close(fd);  // Close only the original, not the new dup'ed STDOUT
	return (EXIT_SUCCESS);
}
int	inn_out(t_shell *shell)
{
	int		i, j;
	int		last_out_index = -1;
	t_cmd	*cmd = shell->cmds;

	// Apply the last infile that exists in redirection
	for (i = 0; cmd->infiles && cmd->infiles[i]; i++)
	{
		for (j = 0; cmd->rediriction && cmd->rediriction[j]; j++)
		{
			if (ft_strcmp(cmd->rediriction[j], cmd->infiles[i]) == 0)
			{
				if (infiless(cmd->infiles[i]))
					return (1);
			}
		}
	}

	// Find the LAST matching outfile in redirection
	for (i = 0; cmd->outfiles && cmd->outfiles[i]; i++)
	{
		for (j = 0; cmd->rediriction && cmd->rediriction[j]; j++)
		{
			if (ft_strcmp(cmd->rediriction[j], cmd->outfiles[i]) == 0)
				last_out_index = i;
		}
	}

	// Apply only the last redirection
	if (last_out_index != -1)
	{
		if (outfilesssssss(shell, cmd->outfiles[last_out_index], last_out_index))
			return (1);
	}

	return (0);
}
