/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:49:04 by hakader           #+#    #+#             */
/*   Updated: 2025/04/16 13:55:36 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	execution_part(t_cmd *f_cmd, t_env *env_list)
{
	// print_list_env(&env_list);
	// print_cmd_list(f_cmd);
	(void)f_cmd;
	(void)env_list;
	char	**paths;

	paths = get_paths(f_cmd, env_list);
	for (int i = 0; paths[i]; i++)
		printf("%s\n", paths[i]);
}
