/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:08:28 by hakader           #+#    #+#             */
/*   Updated: 2025/05/28 17:44:12 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	is_new_line(char *arg)
{
	int	j;

	j = 1;
	if (arg[0] != '-' || arg[1] != 'n')
		return (EXIT_SUCCESS);
	while (arg[j])
	{
		if (arg[j] != 'n')
			return (0);
		j++;
	}
	return (EXIT_FAILURE);
}

int	handle_outfiles(t_cmd *cmd, int *fd, t_shell *shell)
{
	int (j), (flags), (temp_fd);
	j = 0;
	while (cmd->outfiles && cmd->outfiles[j])
	{
		// flags = O_WRONLY | O_CREAT;
		// if (cmd->append_flags[j] == 1)
		// 	flags |= O_APPEND;
		// else
		// 	flags |= O_TRUNC;
		// temp_fd = open(cmd->outfiles[j], flags, 0644);
		in_out(shell);
		if (temp_fd == -1)
		{
			ft_putstr_fd ("minishell: ", 2);
			perror(cmd->outfiles[j]);
			return (0);
		}
		if (cmd->outfiles[j + 1] == NULL)
			*fd = temp_fd;
		else
			close(temp_fd);
		j++;
	}
	return (0);
}

int	open_and_write(t_cmd *cmd, int flag, int i, t_shell *shell)
{
	int	fd;

	fd = -1;
	if (handle_outfiles(cmd, &fd, shell))
		return (1);
	if (fd == -1)
		return (EXIT_FAILURE);
	while (cmd->args[i])
	{
		if ((write(fd, cmd->args[i], ft_strlen(cmd->args[i]))) == -1)
			return (err_write());
		if (cmd->args[i + 1])
			write(fd, " ", 1);
		i++;
	}
	if (flag == 0)
		write(fd, "\n", 1);
	close(fd);
	return (EXIT_SUCCESS);
}

int	open_infile(char **infiles)
{
	int (fd), (i), (error);
	fd = -1;
	i = 0;
	error = 0;
	while (infiles && infiles[i])
	{
		fd = open(infiles[i], O_RDONLY);
		if (fd < 0)
		{
			ft_putstr_fd ("minishell: ", 2);
			perror(infiles[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	execute_echo(t_shell *shell)
{
	t_cmd	*cmd = shell->cmds;
	int		i = 1;
	int		n_flag = 0;

	if (inn_out(shell))
	{
		ft_putendl_fd("here", 1);
		return (1);
	}
	while (cmd->args[i] && is_new_line(cmd->args[i]))
	{
		n_flag = 1;
		i++;
	}

	while (cmd->args[i])
	{
		write(1, cmd->args[i], ft_strlen(cmd->args[i]));
		if (cmd->args[i + 1])
			write(1, " ", 1);
		i++;
	}

	if (!n_flag)
		write(1, "\n", 1);

	return (EXIT_SUCCESS);
}


