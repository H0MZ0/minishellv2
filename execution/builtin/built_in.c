/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:16:08 by hakader           #+#    #+#             */
/*   Updated: 2025/05/03 17:36:43 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	is_builtin(t_shell **shell, t_list *alloc_list)
{
	if (!ft_strcmp((*shell)->cmds->args[0], "cd"))
		return (execute_cd((*shell)->cmds, &(*shell)->env, alloc_list));
	else if (!ft_strcmp((*shell)->cmds->args[0], "echo"))
		return (execute_echo((*shell)->cmds));
	else if (!ft_strcmp((*shell)->cmds->args[0], "pwd"))
		return (execute_pwd((*shell)->cmds));
	else if (!ft_strcmp((*shell)->cmds->args[0], "export"))
		return (execute_export((*shell)->cmds, &(*shell)->env, alloc_list));
	else if (!ft_strcmp((*shell)->cmds->args[0], "unset"))
		return (excute_unset((*shell)->cmds, &(*shell)->env,
				shell, alloc_list));
	else if (!ft_strcmp((*shell)->cmds->args[0], "env"))
		return (execute_env((*shell)->cmds, (*shell)->env));
	else if (!ft_strcmp((*shell)->cmds->args[0], "exit"))
		return (execute_exit((*shell)->cmds, alloc_list));
	return (0);
}

int	execute_pwd(t_cmd *cmd)
{
	char	*cwd;

	if (count_args(cmd->args) > 1)
	{
		put_error("pwd: too many arguments");
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
	}
	else
		perror("pwd");
	return (1);
}

int	execute_env(t_cmd *cmd, t_env *envp)
{
	t_env	*tmp;

	tmp = envp;
	if (count_args(cmd->args) > 1)
	{
		put_error("env: too many arguments");
		return (1);
	}
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (1);
}

int	execute_cd(t_cmd *cmd, t_env **env, t_list *alloc_list)
{
	char	*old_pwd;
	char	*new_pwd;

	if (count_args(cmd->args) > 2)
		return ((put_error("cd: too many arguments")), 1);
	if (!cmd->args[1])
		return ((put_error("please type relative or absolute path")), 1);
	old_pwd = getcwd(NULL, 0);
	if (chdir(cmd->args[1]) == -1)
	{
		perror("cd");
		// free(old_pwd);
		return (1);
	}
	update_env(env, "OLDPWD", old_pwd, alloc_list);
	// free(old_pwd);
	new_pwd = getcwd(NULL, 0);
	update_env(env, "PWD", new_pwd, alloc_list);
	free(new_pwd);
	return (1);
}

