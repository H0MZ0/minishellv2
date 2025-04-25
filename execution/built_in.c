/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:16:08 by hakader           #+#    #+#             */
/*   Updated: 2025/04/25 02:17:31 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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
/*GOOD*/
int	execute_echo(t_cmd *cmd)
{
	int	 (i), (n_flag);
	i = 1;
	n_flag = 0;
	while (cmd->args[i] && is_new_line(cmd->args[i]))
	{
		n_flag = 1;
		i++;
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
	return (1);
}

/*GOOD*/
int	execute_pwd(void)
{
	char	*cwd = getcwd(NULL, 0);

	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
	}
	else
		perror("pwd");
	return (1);
}

/*GOOD*/
int	execute_env(t_env *envp)
{
	t_env *tmp = envp;
	
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (1);
}

void	execute_exit(void)
{
	ft_free_all();
	exit (1);
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

// void	execute_export(void)
// void	execute_unset(void)