/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:00:53 by hakader           #+#    #+#             */
/*   Updated: 2025/04/18 18:22:30 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void    print_arr(char **arr)
{
	int i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		printf("%s", arr[i]);
			if (arr[i + 1])
				printf(" ");
		i++;
	}
}

int		count_args(char **args)
{
	int	i;

	i = 0;
	if (!args || !args[i])
		return (0);
	while (args[i])
		i++;
	return (i);
}
