/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:19:01 by hakader           #+#    #+#             */
/*   Updated: 2025/06/02 16:57:00 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	err_dir(t_shell *shell)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(shell->cmds->args[0], 2);
	ft_putstr_fd(": Is a directory\n", 2);
	shell->exit_status = 126;
}

int	err_write(void)
{
	ft_putstr_fd("minishell: echo: write error: ", 2);
	ft_putstr_fd("No space left on device\n", 2);
	return (EXIT_FAILURE);
}

int	oi_err(t_shell *shell, char *err)
{
	shell->exit_status = EXIT_FAILURE;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd(": ", 2);
	perror("");
	return (EXIT_FAILURE);
}
