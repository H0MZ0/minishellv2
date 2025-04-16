/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:16:08 by hakader           #+#    #+#             */
/*   Updated: 2025/04/13 19:09:14 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_echo(char *param, char *input)
{
	if (ft_strcmp("-n", param) == 0)
		printf("%s", input);
	else
		printf("%s\n", param);
}
int	execute_cd(char *path)
{
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	chdir(path);
	return (0);
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