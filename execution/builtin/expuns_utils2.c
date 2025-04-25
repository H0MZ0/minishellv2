/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expuns_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 02:48:45 by hakader           #+#    #+#             */
/*   Updated: 2025/04/25 16:41:30 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	remove_env_var(t_env **envp, const char *key)
{
	t_env	*current;
	t_env	*prev;

	current = *envp;
	prev = NULL;
	while (current)
	{
		if (!ft_strcmp(current->key, key))
		{
			if (prev)
				prev->next = current->next;
			else
				*envp = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	is_new_line(char *arg)
{
	int	j;

	j= 1;
	if (arg[0] != '-' || arg[1] != 'n')
		return (0);
	while (arg[j])
	{
		if (arg[j] != 'n')
			return (0);
		j++;
	}
	return (1);
}

void	env_path(t_env **env_list, t_cmd *cmd)
{
	// int	i;

	// i = 0;
	if (!cmd->args[1])
		print_this(env_list, "HOME");
	
}

void	execute_exit(void)
{
	printf("exit\n");
	ft_free_all();
	exit (1);
}
