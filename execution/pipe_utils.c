/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:56:42 by sjoukni           #+#    #+#             */
/*   Updated: 2025/06/15 19:07:23 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	wait_all_processes(pid_t last_pid, t_shell **shell)
{
    int		status;
    pid_t	wpid;

    while ((wpid = waitpid(-1, &status, 0)) > 0)
    {
        if (wpid == last_pid)
        {
            if (WIFEXITED(status))
                (*shell)->exit_status = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                (*shell)->exit_status = 128 + WTERMSIG(status);
            else
                (*shell)->exit_status = 1;
        }
    }
}

int	setup_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	return (0);
}
