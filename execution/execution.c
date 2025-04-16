/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:49:04 by hakader           #+#    #+#             */
/*   Updated: 2025/04/16 13:13:27 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	execution_part(t_cmd *f_cmd, t_env *env_list)
{
	(void)env_list;
	print_cmd_list(f_cmd);
}
