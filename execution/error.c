/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:51:09 by hakader           #+#    #+#             */
/*   Updated: 2025/04/12 17:56:14 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	put_error(char *msg)
{
	write(2, "Error\n", ft_strlen("ERROR\n"));
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(1);
}
