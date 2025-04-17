/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:16:08 by hakader           #+#    #+#             */
/*   Updated: 2025/04/17 16:47:11 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execute_echo(t_cmd *cmd)
{
	if (ft_strcmp(cmd->args[1], "-n") == 0)
		print_arr(&cmd->args[1]);
	else
	{
		print_arr(&cmd->args[1]);
		printf("\n");
	}
	return (1);
}
int	execute_cd(t_cmd *cmd)
{
	printf ("here\n");
	if (chdir(cmd->args[1]) == -1)
	{
		printf ("ach hada emmm \n");
		return (1);
	}
	// chdir(cmd->args[1]);
	return (1);
}

void	execute_pwd(void)
{
	char	buffer[1024];
	printf("%s\n", getcwd(buffer, sizeof(buffer)));
}

// void	execute_export(void)
// void	execute_unset(void)
// void	execute_env(void)
// void	execute_exit(void)