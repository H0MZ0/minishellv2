/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:11:01 by hakader           #+#    #+#             */
/*   Updated: 2025/06/15 17:14:29 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	execute_exit(t_shell *shell, t_list *alloc_list)
{
	long	status;

	status = (long)shell->exit_status;
	if (shell->cmds->args[1])
		status = ft_atoi(shell->cmds->args[1], alloc_list);
	if (count_args(shell->cmds->args) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		shell->exit_status = 1;
		return ;
	}
	if (!shell->cmds->has_pipe)
		ft_putendl_fd("exit", 2);
	close(shell->in);
	close(shell->out);
	free_all(&alloc_list);
	exit (status);
}
