/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:38:55 by hakader           #+#    #+#             */
/*   Updated: 2025/06/02 22:06:20 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	update_exit_status(t_shell *shell, pid_t pid)
{
	int (status), (sig);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			write(1, "\n", 1);
		shell->exit_status = 128 + sig;
		if (sig == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", 2);
	}
}

void	set_cmd_not_found(t_shell *shell, char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	if (errno == EACCES)
	{
		ft_putstr_fd(": Permission denied\n", 2);
		shell->exit_status = 126;
		return ;
	}
	else if (strchr(cmd, '/'))
		ft_putstr_fd(": No such file or directory\n", 2);
	else
		ft_putstr_fd(": command not found\n", 2);
	shell->exit_status = 127;
}
