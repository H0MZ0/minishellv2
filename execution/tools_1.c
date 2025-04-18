/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:58:34 by hakader           #+#    #+#             */
/*   Updated: 2025/04/18 18:44:38 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	int i;

	i = 0;
	if (!str1 || !str2)
		return (1);
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

char	**get_paths(t_env *env_list)
{
	int	i;

	i = 0;
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PATH") == 0)
			return(ft_split(tmp->value, ':'));
		tmp = tmp->next;
	}
	return (NULL);
}
int	is_builtin(t_cmd *cmd, t_env *envp)
{
	if (!ft_strcmp(cmd->args[0], "cd"))
		return (execute_cd(cmd));
	else if (!ft_strcmp(cmd->args[0], "echo"))
		return (execute_echo(cmd));
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		return (execute_pwd());
	// else if (!ft_strcmp(cmd->args[0], "export"))
	// 	printf("%s\n", cmd->args[0]);
	// else if (!ft_strcmp(cmd->args[0], "unset"))
	// 	printf("%s\n", cmd->args[0]);
	else if (!ft_strcmp(cmd->args[0], "env"))
		return (execute_env(envp));
	else if (!ft_strcmp(cmd->args[0], "exit"))
		printf("%s\n", cmd->args[0]);
	return (0);
}

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

void	put_error(char *msg)
{
	// write(2, "Error\n", ft_strlen("ERROR\n"));
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	// exit(1);
}
