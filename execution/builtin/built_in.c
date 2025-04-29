/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:16:08 by hakader           #+#    #+#             */
/*   Updated: 2025/04/29 13:09:43 by hakader          ###   ########.fr       */
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
		printf("%s\n", cmd->args[0]);
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
	env_path(env, cmd);
	if (count_args(cmd->args) > 2)
	{
		put_error("cd: too many arguments");
		return (1);
	}
	if (!cmd->args[1])
	{
		if (chdir(getenv("HOME")) == -1)
			perror("cd");
	}
	else
	{
		if (chdir(cmd->args[1]) == -1)
			perror("cd");
	}
	return (1);
}
