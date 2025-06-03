/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:21:26 by sjoukni           #+#    #+#             */
/*   Updated: 2025/06/02 15:56:52 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	*create_token(char *str, t_token_type type, t_list *alloc_list)
{
	t_token	*new_token;

	new_token = ft_malloc(sizeof(t_token), &alloc_list);
	if (!new_token)
		return (NULL);
	new_token->value = ft_strdup(str, alloc_list);
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

void	append_token(t_token **head, t_token *new)
{
	t_token	*temp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

t_token_type	get_token_type(char *str)
{
	if (!strcmp(str, "|"))
		return (PIPE);
	if (!strcmp(str, ">"))
		return (REDIR_OUT);
	if (!strcmp(str, ">>"))
		return (APPEND);
	if (!strcmp(str, "<"))
		return (REDIR_IN);
	if (!strcmp(str, "<<"))
		return (HEREDOC);
	if (!strcmp(str, ";"))
		return (SEMICOLON);
	return (WORD);
}

int	is_redirect_type(t_token_type type)
{
	return (type == APPEND || type == REDIR_OUT || type == REDIR_IN);
}

int	is_ambiguous(t_token *last_token, char *expanded_value)
{
	int	i;

	if (!last_token || !is_redirect_type(last_token->type))
		return (0);
	if (!expanded_value || expanded_value[0] == '\0')
		return (1);
	i = 0;
	while (expanded_value[i])
	{
		if (ft_isspace(expanded_value[i]))
			return (1);
		i++;
	}
	return (0);
}
