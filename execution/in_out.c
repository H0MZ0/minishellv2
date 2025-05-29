/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:06:12 by hakader           #+#    #+#             */
/*   Updated: 2025/05/29 16:37:17 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	oi_err(char *err)
{
	ft_putstr_fd("minishell: ", 2);
	perror(err);
	return (EXIT_FAILURE);
}

int	check_all_infiles(t_shell *shell, char **infiles)
{
	int		i;
	int		fd;
	int		in_backup;
	int		out_backup;

	i = 0;
	in_backup = dup(STDIN_FILENO);
	out_backup = dup(STDOUT_FILENO);
	while (infiles && infiles[i])
	{
		fd = open(infiles[i], O_RDONLY);
		if (fd < 0)
		{
			shell->exit_status = EXIT_FAILURE;
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(infiles[i], 2);
			ft_putstr_fd(": ", 2);
			perror("");
			return (EXIT_FAILURE);
		}
		close(fd);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	check_all_outfiles(t_shell *shell, char **outfiles, int *append_flags)
{
	int		i;
	int		fd;
	int		flags;

	i = 0;
	while (outfiles && outfiles[i])
	{
		flags = O_WRONLY | O_CREAT;
		if (append_flags && append_flags[i])
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		fd = open(outfiles[i], flags, 0644);
		if (fd < 0)
		{
			shell->exit_status = EXIT_FAILURE;
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(outfiles[i], 2);
			ft_putstr_fd(": ", 2);
			perror("");
			return (EXIT_FAILURE);
		}
		close(fd);
		i++;
	}
	return (EXIT_SUCCESS);
}
