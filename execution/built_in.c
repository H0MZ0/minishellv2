/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:16:08 by hakader           #+#    #+#             */
/*   Updated: 2025/04/22 11:51:06 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_valid_n_flag(char *arg)
{
	int	j;

	j= 1;
	if (arg[0] != '-' || arg[1] != 'n')
		return (0);
	while (arg[j])
	{
		if (arg[j] != 'n')
			return (0);
		j++;
	}
	return (1);
}

int	execute_echo(t_cmd *cmd)
{
	int	 (i), (n_flag);
	i = 1;
	n_flag = 0;
	while (cmd->args[i] && is_valid_n_flag(cmd->args[i]))
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


int	execute_cd(t_cmd *cmd)
{
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

int	execute_pwd(void)
{
	char	buffer[1024];
	if (getcwd(buffer, sizeof(buffer)))
		printf("%s\n", buffer);
	else
		perror("pwd");
	return (1);
}

// void	execute_export(void)
// void	execute_unset(void)
int	execute_env(t_env *envp)
{
	t_env *tmp = envp;

	while (tmp)
	{
		printf("%s%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (1);
}

void	execute_exit(int exit_code)
{
	//all_free_function
	exit (exit_code);
}