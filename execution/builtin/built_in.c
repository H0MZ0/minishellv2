/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:16:08 by hakader           #+#    #+#             */
/*   Updated: 2025/04/29 17:32:47 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	is_builtin(t_cmd *cmd, t_env *envp)
{
	if (!ft_strcmp(cmd->args[0], "cd"))
		return (execute_cd(cmd, &envp));
	else if (!ft_strcmp(cmd->args[0], "echo"))
		return (execute_echo(cmd));
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		return (execute_pwd());
	else if (!ft_strcmp(cmd->args[0], "export"))
		execute_export(cmd, &envp);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		execute_unset(cmd, &envp);
	else if (!ft_strcmp(cmd->args[0], "env"))
		return (execute_env(envp));
	else if (!ft_strcmp(cmd->args[0], "exit"))
		execute_exit();
	return (0);
}

int	execute_pwd(void)
{
	char	*cwd;

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

int	execute_env(t_env *envp)
{
	t_env	*tmp;

	tmp = envp;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (1);
}

int	execute_cd(t_cmd *cmd, t_env **env)
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
		free(old_pwd);
		return (1);
	}
	update_env(env, "OLDPWD", old_pwd);
	free(old_pwd);
	new_pwd = getcwd(NULL, 0);
	update_env(env, "PWD", new_pwd);
	free(new_pwd);
	return (1);
}

