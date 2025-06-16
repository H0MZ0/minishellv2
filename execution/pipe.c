/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:00:37 by sjoukni           #+#    #+#             */
/*   Updated: 2025/06/16 14:11:18 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	handle_pipes(t_shell *shell, t_list **alloc_list)
{
	t_cmd	*cmd;

	cmd = shell->cmds;
	if (!heredoc_pipe(cmd, shell, *alloc_list))
		return ;
	pipex(&shell, *alloc_list);
	while (shell->cmds && shell->cmds->has_pipe)
	{
		close_heredoc_fd(shell->cmds);
		shell->cmds = shell->cmds->next;
	}
	if (shell->cmds)
	{
		close_heredoc_fd(shell->cmds);
		shell->cmds = shell->cmds->next;
	}
}

static void	init_exec_state(t_exec_state *state, t_shell **shell,
		t_list *alloc_list)
{
	state->shell = *shell;
	state->alloc_list = alloc_list;
	state->paths = get_paths(shell, alloc_list);
	state->current = (*shell)->cmds;
	state->prev_fd = dup(STDIN_FILENO);
}

static void	handle_pipe(t_exec_state *s)
{
	int		pipe_fd[2];
	pid_t	pid;

	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		child_exec(s, pipe_fd[1]);
	}
	close(pipe_fd[1]);
	if (s->prev_fd != STDIN_FILENO)
		close(s->prev_fd);
	s->prev_fd = pipe_fd[0];
}

static void	handle_last_command(t_exec_state *s)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		child_exec(s, STDOUT_FILENO);
	if (s->prev_fd != STDIN_FILENO)
		close(s->prev_fd);
	wait_all_processes(pid, &s->shell);
}

void	pipex(t_shell **shell, t_list *alloc_list)
{
	t_exec_state	s;

	init_exec_state(&s, shell, alloc_list);
	while (s.current && s.current->has_pipe)
	{
		handle_pipe(&s);
		s.current = s.current->next;
	}
	if (s.current)
		handle_last_command(&s);
}
