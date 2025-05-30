/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:57:57 by hakader           #+#    #+#             */
/*   Updated: 2025/05/30 20:23:11 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	execute_pwd(t_cmd *cmd)
{
	char	*cwd;

	if (check_options(cmd, "pwd"))
		return ((ft_putendl_fd("pwd: too many arguments", 2)), 2);
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_putendl_fd(cwd, 1);
		free(cwd);
	}
	else
	{
		free (cmd);
		perror("pwd");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
