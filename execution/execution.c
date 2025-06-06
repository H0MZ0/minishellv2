/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:49:04 by hakader           #+#    #+#             */
/*   Updated: 2025/06/06 21:13:41 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	exec_child(t_shell *shell, char *cmd, t_list **alloc_list)
{
	int	error;

	error = 0;
	set_child_signals();
	if (shell->cmds->heredoc_delim)
	{
		if (shell->cmds->heredoc_fd == -1)
			exit(shell->exit_status);
		dup2(shell->cmds->heredoc_fd, STDIN_FILENO);
		close(shell->cmds->heredoc_fd);
	}
	else if (shell->cmds->infiles || shell->cmds->outfiles)
		if (in_out(shell))
			exit (shell->exit_status);
	execve(cmd, &shell->cmds->args[0], shell->envp);
	perror("execve failed");
	exit(EXIT_FAILURE);
}

static void	exec_command(t_shell *shell, char **paths, t_list **alloc_list)
{
	pid_t		pid;
	char		*cmd;
	struct stat	sa;

	if (shell->cmds->args && stat(shell->cmds->args[0], &sa) == 0
		&& S_ISDIR(sa.st_mode)
		&& ft_strchr(shell->cmds->args[0], '/'))
		return (err_dir(shell));
	if (if_builtin(shell, (*alloc_list)))
		return ;
	cmd = check_cmd(paths, shell->cmds->args[0], (*alloc_list));
	if (cmd)
	{
		pid = fork();
		if (pid == 0)
			exec_child(shell, cmd, alloc_list);
		else
			update_exit_status(shell, pid);
	}
	else
		set_cmd_not_found(shell, shell->cmds->args[0]);
}

void	execution_part(t_shell *shell, t_list **alloc_list)
{
    char	**paths;

    paths = get_paths(&shell, (*alloc_list));
    while (shell->cmds)
    {
        if (shell->cmds->heredocs)
        {
            if (!read_heredoc(shell->cmds, shell, *alloc_list)) {
                shell->cmds = shell->cmds->next;
                continue;
            }
        }
        if (shell->cmds->has_pipe)
        {
            pipex(&shell, (*alloc_list));
            while (shell->cmds && shell->cmds->has_pipe)
                shell->cmds = shell->cmds->next;
            if (shell->cmds)
                shell->cmds = shell->cmds->next;
            // Always close heredoc_fd if still open
            if (shell->cmds && shell->cmds->heredoc_fd != -1) {
                close(shell->cmds->heredoc_fd);
                shell->cmds->heredoc_fd = -1;
            }
            continue ;
        }
        exec_command(shell, paths, alloc_list);
        if (shell->cmds->heredoc_fd != -1 && shell->cmds->heredoc_fd != STDIN_FILENO)
        {
            close(shell->cmds->heredoc_fd);
            shell->cmds->heredoc_fd = -1;
        }
        shell->cmds = shell->cmds->next;
    }
}
