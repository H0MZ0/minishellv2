/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:57:57 by hakader           #+#    #+#             */
/*   Updated: 2025/06/02 20:16:57 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	execute_pwd(t_cmd *cmd)
{
	char	*cwd;

	if (check_options(cmd, "pwd"))
		return (EXIT_FAILURE);
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_putendl_fd(cwd, 1);
		free(cwd);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		perror("pwd");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
