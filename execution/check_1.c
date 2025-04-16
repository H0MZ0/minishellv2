/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 08:23:55 by hakader           #+#    #+#             */
/*   Updated: 2025/04/16 16:57:15 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// void is_builtin(t_cmd *cmd)
// {
// 	(void)cmd4;
// 	if (!ft_strcmp(cmd1, "cd"))
// 		execute_cd(cmd2);
// 	if (!ft_strcmp(cmd1, "echo"))
// 		execute_echo(cmd2, cmd3);
// 	if (!ft_strcmp(cmd1, "pwd"))
// 		execute_pwd();
// 	if (!ft_strcmp(cmd1, "export"))
// 		printf("export\n");
// 	if (!ft_strcmp(cmd1, "unset"))
// 		printf("unset\n");
// 	if (!ft_strcmp(cmd1, "env"))
// 		printf("env\n");
// 	if (!ft_strcmp(cmd1, "exit"))
// 		exit(127);
// }

char	*check_cmd(char **paths, char *cmd)
{
	char	*command;
	int		i;

	if (!cmd || !paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		command = ft_strjoin(paths[i], "/");
		command = ft_strjoin(command, cmd);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}
