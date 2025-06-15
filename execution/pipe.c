/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:00:37 by sjoukni           #+#    #+#             */
/*   Updated: 2025/06/15 21:06:58 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"


void	exec_pipeline_cmd(t_shell *shell , t_cmd *cmd,char **paths , int in_fd, int out_fd, t_list *alloc_list)
{
    char	*cmd_path;

    set_child_signals();
    dup2(in_fd, STDIN_FILENO);
    dup2(out_fd, STDOUT_FILENO);
    if (handle_redirections(cmd, alloc_list))
        exit(EXIT_FAILURE);
    if (!cmd->args || !cmd->args[0])
        exit(EXIT_SUCCESS);
    if (is_builtin_name(cmd->args[0]))
        exit(exec_builtin(&shell, cmd, alloc_list));
    cmd_path = check_cmd(paths, cmd->args[0], alloc_list);
    if (!cmd_path)
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
        ft_putstr_fd(cmd->args[0], STDERR_FILENO);
        ft_putendl_fd(": command not found\n", STDERR_FILENO);
        exit(127);
    }
    execve(cmd_path, cmd->args, shell->envp);
    perror("execve");
    exit(EXIT_FAILURE);
}

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

void	setup_pipe_and_exec(t_shell **shell, t_cmd *current, char **paths,
    int *prev_fd, t_list *alloc_list)
{
    int		pipe_fd[2];
    pid_t	pid;

    setup_pipe(pipe_fd);
    pid = fork();
    if (pid == 0)
    {
        close(pipe_fd[0]);
        exec_pipeline_cmd(*shell, current, paths, *prev_fd, pipe_fd[1], alloc_list);
    }
    close(pipe_fd[1]);
    if (*prev_fd != STDIN_FILENO)
        close(*prev_fd);
    *prev_fd = pipe_fd[0];
}

void	exec_last_command(t_shell **shell, t_cmd *current, char **paths,
    int prev_fd, t_list *alloc_list)
{
    pid_t	pid;

    pid = fork();
    if (pid == 0)
        exec_pipeline_cmd(*shell, current, paths, prev_fd, STDOUT_FILENO, alloc_list);
    if (prev_fd != STDIN_FILENO)
        close(prev_fd);
    wait_all_processes(pid, shell);
}

void	pipex(t_shell **shell, t_list *alloc_list)
{
    int		in_fd;
    int		prev_fd;
    char	**paths;
    t_cmd	*current;

    in_fd = dup(STDIN_FILENO);
    prev_fd = in_fd;
    paths = get_paths(shell, alloc_list);
    current = (*shell)->cmds;
    while (current && current->has_pipe)
    {
        setup_pipe_and_exec(shell, current, paths, &prev_fd, alloc_list);
        current = current->next;
    }
    if (current)
        exec_last_command(shell, current, paths, prev_fd, alloc_list);
}