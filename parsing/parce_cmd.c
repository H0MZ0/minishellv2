/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:21:24 by hakader           #+#    #+#             */
/*   Updated: 2025/06/01 18:35:02 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	handle_semicolon_case(t_cmd **cmd_list, t_cmd **current_cmd)
{
	if (!(*current_cmd)->args && !(*current_cmd)->infiles
		&& !(*current_cmd)->outfiles)
	{
		print_error("near unexpected token `;'");
		return (0);
	}
	add_cmd_to_list(cmd_list, *current_cmd);
	return (1);
}

static void	handle_pipe_case(t_cmd **cmd_list, t_cmd **current_cmd,
		t_list *alloc_list)
{
	(*current_cmd)->has_pipe = 1;
	add_cmd_to_list(cmd_list, *current_cmd);
	*current_cmd = create_cmd(alloc_list);
}

static int	handle_token_case(t_token **current, t_token *token,
		t_build_ctx *ctx)
{
	if (token->type == PIPE)
		handle_pipe_case(&ctx->cmd_list, &ctx->current_cmd, ctx->alloc_list);
	else if (token->type == SEMICOLON)
	{
		if (!handle_semicolon_case(&ctx->cmd_list, &ctx->current_cmd))
			return (0);
		ctx->current_cmd = create_cmd(ctx->alloc_list);
	}
	else
	{
		if (!handle_token_redirection_or_arg(current, ctx->current_cmd,
				ctx->alloc_list, ctx->shell))
			return (0);
	}
	return (1);
}

static int	process_tokens(t_token *tokens, t_build_ctx *ctx)
{
	t_token	*current;
	t_token	*token;

	current = tokens;
	while (current)
	{
		token = current;
		if (!handle_token_case(&current, token, ctx))
			return (0);
		current = current->next;
	}
	return (1);
}

t_cmd	*build_cmd_list(t_token *tokens, t_list *alloc_list, t_shell *shell)
{
	t_build_ctx	ctx;

	ctx.cmd_list = NULL;
	ctx.current_cmd = create_cmd(alloc_list);
	ctx.alloc_list = alloc_list;
	ctx.shell = shell;
	if (!process_tokens(tokens, &ctx))
		return (NULL);
	add_cmd_to_list(&ctx.cmd_list, ctx.current_cmd);
	return (ctx.cmd_list);
}
