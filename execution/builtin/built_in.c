/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:16:08 by hakader           #+#    #+#             */
/*   Updated: 2025/06/02 22:25:20 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	is_builtin_name(const char *name)
{
	return (!ft_strcmp(name, "cd") || !ft_strcmp(name, "echo")
		|| !ft_strcmp(name, "pwd") || !ft_strcmp(name, "export")
		|| !ft_strcmp(name, "unset") || !ft_strcmp(name, "env")
		|| !ft_strcmp(name, "exit"));
}

static void	no_pipe(t_shell *shell, t_list *alloc_list)
{
	int	in_backup;
	int	out_backup;

	in_backup = dup(STDIN_FILENO);
	out_backup = dup(STDOUT_FILENO);
	if (shell->cmds->infiles || shell->cmds->outfiles)
		in_out(shell);
	exec_builtin(&shell, shell->cmds, alloc_list);
	dup2(in_backup, STDIN_FILENO);
	dup2(out_backup, STDOUT_FILENO);
	close(in_backup);
	close(out_backup);
}

static void	with_pipe(t_shell *shell, t_list *alloc_list)
{
	pid_t	pid;

	if (shell->cmds->infiles || shell->cmds->outfiles)
		in_out(shell);
	pid = fork();
	if (pid == 0)
		exit(exec_builtin(&shell, shell->cmds, alloc_list));
	else
		update_exit_status(shell, pid);
}

int	if_builtin(t_shell *shell, t_list *alloc_list)
{
	if (shell->cmds->args && !is_builtin_name(shell->cmds->args[0]))
		return (0);
	if (shell->cmds->has_pipe)
		with_pipe(shell, alloc_list);
	else
		no_pipe(shell, alloc_list);
	return (1);
}

int	exec_builtin(t_shell **shell, t_cmd *cmd, t_list *alloc_list)
{
	if (!cmd->args)
		return ((*shell)->exit_status);
	if (!ft_strcmp(cmd->args[0], "cd"))
		(*shell)->exit_status = execute_cd((*shell), cmd,
				&(*shell)->env, alloc_list);
	else if (!ft_strcmp(cmd->args[0], "echo"))
		(*shell)->exit_status = execute_echo(cmd);
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		(*shell)->exit_status = execute_pwd(cmd);
	else if (!ft_strcmp(cmd->args[0], "export"))
		return (execute_export(shell, alloc_list));
	else if (!ft_strcmp(cmd->args[0], "unset"))
		return (excute_unset(shell, alloc_list));
	else if (!ft_strcmp(cmd->args[0], "env"))
		(*shell)->exit_status = execute_env(cmd, (*shell)->env);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		execute_exit((*shell), alloc_list);
	return ((*shell)->exit_status);
}
