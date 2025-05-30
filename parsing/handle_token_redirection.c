/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token_redirection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:01:44 by sjoukni           #+#    #+#             */
/*   Updated: 2025/05/30 16:47:45 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	handle_heredoc(
	t_cmd *cmd,
	char *target,
	char *raw_value,	
	t_list *alloc_list)
{
	char	*delim;
	int		expand;

	delim = remove_quotes(target, alloc_list);
	expand = is_quote(raw_value);
	cmd->heredocs = alloc_array(cmd->heredocs, cmd->heredoc_count + 1,
			alloc_list);
	cmd->heredocs[cmd->heredoc_count].delim = delim;
	cmd->heredocs[cmd->heredoc_count].expand = expand;
	cmd->heredoc_count++;
	if (cmd->heredoc_count >= 17)
		return (0);
	return (1);
}

int	handle_token_redirection_or_arg(t_token **current, t_cmd *cmd,
		t_list *alloc_list, t_shell *shell)
{
	t_token	*token;

	token = *current;
	if (token->type == WORD)
		add_arg_to_cmd(cmd, token->value, alloc_list);
	else if (token->type == REDIR_IN || token->type == REDIR_OUT
		|| token->type == APPEND || token->type == HEREDOC)
		return (handle_redirection(current, cmd, alloc_list, shell));
	return (1);
}
