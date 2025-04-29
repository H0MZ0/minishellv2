/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:08:28 by hakader           #+#    #+#             */
/*   Updated: 2025/04/29 13:11:30 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	execute_echo(t_cmd *cmd)
{
	int (i), (n_flag);
	i = 1;
	n_flag = 0;
	while (cmd->args[i] && is_new_line(cmd->args[i]))
	{
		n_flag = 1;
		i++;
	}
	if (cmd->infile || cmd->outfile)
		return (open_and_write(cmd, n_flag, i));
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
	return (1);
}

int	open_and_write(t_cmd *cmd, int flag, int i)
{
	int	fd;

	fd = open(cmd->outfile, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror("fd");
		return (1);
	}
	while (cmd->args[i])
	{
		write(fd, cmd->args[i], ft_strlen(cmd->args[i]));
		if (cmd->args[i + 1])
			write (fd, " ", 1);
		i++;
	}
	if (!flag)
		write (fd, "\n", 1);
	close(fd);
	return (1);
}
