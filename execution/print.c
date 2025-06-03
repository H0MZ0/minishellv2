/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:40:15 by hakader           #+#    #+#             */
/*   Updated: 2025/06/02 16:50:21 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	print_sorted_env(t_env *sorted)
{
	while (sorted)
	{
		if (sorted->value)
			printf("declare -x %s=\"%s\"\n", sorted->key, sorted->value);
		else
			printf("declare -x %s\n", sorted->key);
		sorted = sorted->next;
	}
}

void	sort_env(t_env *sorted)
{
	t_env	*i;
	t_env	*j;

	i = sorted;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (ft_strcmp(i->key, j->key) > 0)
				swap_env(i, j);
			j = j->next;
		}
		i = i->next;
	}
}

void	print_list_env(t_env **head, t_list *alloc_list)
{
	t_env	*sorted;

	sorted = copy_env(*head, alloc_list);
	if (!sorted)
		return ;
	sort_env(sorted);
	print_sorted_env(sorted);
}
