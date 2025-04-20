/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:30:42 by sjoukni           #+#    #+#             */
/*   Updated: 2025/04/20 16:30:59 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int get_dollar_pos(char *str)
{
	int i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}


char *extract_var_name(char *str, int pos)
{
	int start = pos + 1;
	int len = 0;

	if (str[start] == '?')
		return (ft_strdup("?")); 

	while (str[start + len] &&
		(ft_isalpha(str[start + len]) || ft_isdigit(str[start + len]) || str[start + len] == '_'))
	{
		len++;
	}

	if (len == 0)
		return (NULL);
	return ft_substr(str, start, len); 
}

char *get_env_value(t_env *env, char *key, int last_exit)
{
	t_env *tmp;

	if (!strcmp(key, "?"))
		return (ft_itoa(last_exit)); 

	tmp = env;
	while (tmp)
	{
		if (strcmp(tmp->key, key) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}


char *replace_var_in_string(char *src, int var_start, int var_len, char *value)
{
	int before_len = var_start;
	int value_len = ft_strlen(value);
	int after_len = ft_strlen(src + var_start + var_len + 1);
	int total_len = before_len + value_len + after_len;

	char *new_str = malloc(total_len + 1);
	if (!new_str)
		return (NULL);

	int i = 0;
	while (i < before_len)
	{
		new_str[i] = src[i];
		i++;
	}

	int j = 0;
	while (j < value_len)
		new_str[i++] = value[j++];

	j = var_start + var_len + 1;
	while (src[j])
		new_str[i++] = src[j++];

	new_str[i] = '\0';
	return new_str;
}

char *expand_token_value(char *value, t_env *env, int last_exit)
{
	char *result = ft_strdup(value);
	int pos;

	while ((pos = get_dollar_pos(result)) != -1)
	{
		char *var = extract_var_name(result, pos);
		if (!var)
			break;

		char *var_value = get_env_value(env, var, last_exit);
		char *expanded = replace_var_in_string(result, pos, ft_strlen(var), var_value);

		free(var_value);
		free(var);
		free(result);
		result = expanded;
	}
	return result;
}



