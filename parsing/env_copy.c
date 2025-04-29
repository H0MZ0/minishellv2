/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:08:35 by sjoukni           #+#    #+#             */
/*   Updated: 2025/04/29 11:02:03 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char *key(char *str)
{
    int i = 0;
    while (str[i] && str[i] != '=')
        i++;

    char *key = malloc(i + 1);
    if (!key)
        return NULL;

    int j = 0;
    while (j < i)
    {
        key[j] = str[j];
        j++;
    }
    key[i] = '\0';

    return key;
}

char *value(char *str)
{
    int i = 0;
    while (str[i] && str[i] != '=')
        i++;

    if (str[i] == '\0') 
        return NULL;

    i++; 
    int len = 0;
    while (str[i + len])
        len++;

    char *value = malloc(len + 1);
    if (!value)
        return NULL;

    int j = 0;
    while (j < len)
    {
        value[j] = str[i + j];
        j++;
    }
    value[len] = '\0';

    return value;
}

t_env *env_copy(char *content)
{
    t_env *new_node = malloc(sizeof(t_env));
    if (!new_node)
        return NULL;

    new_node->key = key(content);
    new_node->value = value(content);
    new_node->next = NULL;

    return new_node;
}
void append_env(t_env **head, t_env *new_node)
{
	if (!*head)
	{
		*head = new_node;
		return;
	}
	t_env *tmp = *head;
	while (tmp->next)
		tmp = tmp->next;

	tmp->next = new_node; 
}
