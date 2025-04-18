/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:16:08 by hakader           #+#    #+#             */
/*   Updated: 2025/04/18 18:13:48 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execute_echo(t_cmd *cmd)
{
	if (ft_strcmp(cmd->args[1], "-n") == 0)
		print_arr(&cmd->args[2]);
	else
	{
		print_arr(&cmd->args[1]);
		printf("\n");
	}
	return (1);
}

int	execute_cd(t_cmd *cmd)
{
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
// void	execute_exit(void)