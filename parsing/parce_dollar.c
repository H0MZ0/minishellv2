/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:30:42 by sjoukni           #+#    #+#             */
/*   Updated: 2025/06/14 18:15:10 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*extract_non_dollar(char *value, int *i, t_list *alloc_list)
{
	char	buf[2];

	buf[0] = value[*i];
	buf[1] = '\0';
	(*i)++;
	return (ft_strdup(buf, alloc_list));
}

char	*handle_env_var(char *value, int *i, t_shell *shell, t_list *alloc_list)
{
	char	*var_name;
	char	*var_value;
	int		var_len;

	var_len = 0;
	while (value[*i + var_len] && (ft_isalnum(value[*i + var_len]) || value[*i
				+ var_len] == '_'))
		var_len++;
	var_name = ft_substr(value, *i, var_len, alloc_list);
	*i += var_len;
	var_value = get_env_value(shell, var_name, alloc_list);
	if (!var_value)
		return (ft_strdup("", alloc_list));
	return (var_value);
}

char	*handle_exit_status(int *i, t_shell *shell, t_list *alloc_list)
{
	(*i)++;
	return (ft_itoa(shell->exit_status, alloc_list));
}

char	*handle_dollar(char *value, int *i, t_shell *shell, t_list *alloc_list)
{
	(*i)++;
	if (value[*i] == '?')
		return (handle_exit_status(i, shell, alloc_list));
	if (ft_isalpha(value[*i]) || value[*i] == '_')
		return (handle_env_var(value, i, shell, alloc_list));
	if (ft_isdigit(value[*i]))
	{
		(*i)++;
		return (ft_strdup("", alloc_list));
	}
	return (ft_strdup("$", alloc_list));
}

char	*expand_token_value(char *value, t_shell *shell, t_list *alloc_list)
{
	int		i;
	char	*result;
	char	*var_value;
	int		any_expanded;
	char	*tmp;

	i = 0;
	result = ft_strdup("", alloc_list);
	any_expanded = 0;
	while (value[i])
	{
		if (value[i] == '$')
		{
			var_value = handle_dollar(value, &i, shell, alloc_list);
			if (var_value[0] != '\0')
				any_expanded = 1;
		}
		else
			var_value = extract_non_dollar(value, &i, alloc_list);
		tmp = ft_strjoin(result, var_value, alloc_list);
		result = tmp;
	}
	return (result);
}
