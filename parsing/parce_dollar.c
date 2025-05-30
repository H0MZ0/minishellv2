/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:30:42 by sjoukni           #+#    #+#             */
/*   Updated: 2025/05/30 16:26:53 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_env_value(t_shell *shell, char *key, t_list *alloc_list)
{
	t_env	*tmp;

	if (!strcmp(key, "?"))
		return (ft_itoa(shell->exit_status, alloc_list));
	tmp = shell->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (ft_strdup(tmp->value, alloc_list));
		tmp = tmp->next;
	}
	return (0);
}


char	*expand_token_value(char *value, t_shell *shell, t_list *alloc_list)
{
	int		i = 0;
	char	*result = ft_strdup("", alloc_list);
	char	*var_name;
	char	*var_value;
	char	*tmp;
	int		start;
	int		any_expanded = 0;

	while (value[i])
	{
		if (value[i] == '$')
		{
			start = i++;
			if (value[i] == '?')
			{
				var_value = ft_itoa(shell->exit_status, alloc_list);
				i++;
			}
			else if (ft_isalpha(value[i]) || value[i] == '_')
			{
				int var_len = 0;
				while (value[i + var_len] && (ft_isalnum(value[i + var_len]) || value[i + var_len] == '_'))
					var_len++;

				var_name = ft_substr(value, i, var_len, alloc_list);
				var_value = get_env_value(shell, var_name, alloc_list);
				if (!var_value)
					var_value = ft_strdup("", alloc_list);
				i += var_len;
			}
			else if (ft_isdigit(value[i]))
			{
				i++; 
				var_value = ft_strdup("", alloc_list);
			}
			else
			{
				var_value = ft_strdup("$", alloc_list);
			}

			if (var_value[0] != '\0')
				any_expanded = 1;

			tmp = ft_strjoin(result, var_value, alloc_list);
			result = tmp;
		}
		else
		{
			char buf[2] = { value[i], 0 };
			tmp = ft_strjoin(result, buf, alloc_list);
			result = tmp;
			i++;
		}
	}
	return result;
}


// static char	*expand_exit_status(char *result, int pos,
// 	t_shell *shell, t_list *alloc_list)
// {
// 	char	*value;
// 	char	*new_result;

// 	value = ft_itoa(shell->exit_status, alloc_list);
// 	new_result = replace_var_in_string(result, pos, 1, value, alloc_list);
// 	return (new_result);
// }

// static char	*expand_env_var(char *result, int pos,
// 	t_shell *shell, t_list *alloc_list)
// {
// 	char	*var;
// 	char	*value;
// 	char	*new_result;

// 	var = extract_var_name(result, pos, alloc_list);
// 	if (!var)
// 		return (result);
// 	value = get_env_value(shell, var, alloc_list);
// 	new_result = replace_var_in_string(result, pos, ft_strlen(var),
// 			value, alloc_list);
// 	return (new_result);
// }

// char	*expand_token_value(char *value, t_shell *shell, t_list *alloc_list)
// {
// 	char	*result;
// 	int		pos;

// 	result = ft_strdup(value, alloc_list);
// 	while ((pos = get_dollar_pos(result)) != -1)
// 	{
// 		if (result[pos + 1] == '?')
// 			result = expand_exit_status(result, pos, shell, alloc_list);
// 		else
// 			result = expand_env_var(result, pos, shell, alloc_list);
// 	}
// 	return (result);
// }

