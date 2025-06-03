/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 16:38:23 by sjoukni           #+#    #+#             */
/*   Updated: 2025/06/01 18:22:40 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	handle_redir_in(t_cmd *cmd, char *target, t_list *alloc_list)
{
	cmd->infiles = append_str_array(cmd->infiles, target, alloc_list);
	cmd->rediriction = append_str_array(cmd->rediriction, target, alloc_list);
	return (1);
}

int	handle_output_redir(t_cmd *cmd, int type, char *target, t_list *alloc_list)
{
	cmd->outfiles = append_str_array(cmd->outfiles, target, alloc_list);
	if (type == APPEND)
	{
		cmd->append_flags = append_arr(cmd->append_flags, 1, alloc_list);
		cmd->rediriction_ag = append_arr(cmd->rediriction_ag, 2, alloc_list);
	}
	else
	{
		cmd->append_flags = append_arr(cmd->append_flags, 0, alloc_list);
		cmd->rediriction_ag = append_arr(cmd->rediriction_ag, 1, alloc_list);
	}
	return (1);
}

static void	handle_output_wrap(t_cmd *cmd, int type, char *target,
		t_list *alloc_list)
{
	handle_output_redir(cmd, type, target, alloc_list);
	cmd->rediriction = append_str_array(cmd->rediriction, target, alloc_list);
}

static void	handle_input_redir(t_cmd *cmd, char *target, t_list *alloc_list)
{
	cmd->infiles = append_str_array(cmd->infiles, target, alloc_list);
	cmd->rediriction_ag = append_arr(cmd->rediriction_ag, 0, alloc_list);
	cmd->rediriction = append_str_array(cmd->rediriction, target, alloc_list);
}

int	handle_redirection(t_token **current, t_cmd *cmd, t_list *alloc_list,
		t_shell *shell)
{
	t_token	*token;
	char	*target;

	token = *current;
	if (!token->next || token->next->type != WORD)
		return (print_error("near unexpected token"));
	target = ft_strdup(token->next->value, alloc_list);
	target = remove_quotes(target, alloc_list);
	if (token->type == REDIR_IN)
		handle_input_redir(cmd, target, alloc_list);
	else if (token->type == REDIR_OUT || token->type == APPEND)
		handle_output_wrap(cmd, token->type, target, alloc_list);
	else if (token->type == HEREDOC)
	{
		if (!handle_heredoc(cmd, target, token->next->value, alloc_list))
		{
			ft_putstr_fd("minishell: max heredoc\n", 2);
			return (shell->exit_status = 2, 0);
		}
		cmd->rediriction = append_str_array(cmd->rediriction, target,
				alloc_list);
		cmd->rediriction_ag = append_arr(cmd->rediriction_ag, 3, alloc_list);
	}
	*current = token->next;
	return (1);
}
