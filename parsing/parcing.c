/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:36:31 by sjoukni           #+#    #+#             */
/*   Updated: 2025/06/02 15:52:52 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	update_last_token_and_heredoc(t_token *head,
	t_token **last_token, int *prev_is_heredoc)
{
	*last_token = head;
	while (*last_token && (*last_token)->next)
		*last_token = (*last_token)->next;
	*prev_is_heredoc = (*last_token && (*last_token)->type == HEREDOC);
}

static void	init_token_ctx(t_token_ctx *ctx, t_shell *shell,
	t_token **head, t_token_input *input)
{
	ctx->shell = shell;
	ctx->head = head;
	ctx->alloc_list = input->alloc_list;
	ctx->token_str = ft_strndup(input->segment, input->len, input->alloc_list);
	ctx->type = get_token_type(ctx->token_str);
	update_last_token_and_heredoc(*head, &ctx->last, &ctx->prev_heredoc);
}

static int	handle_word_token(t_token_ctx *ctx)
{
	t_token			*current;
	t_expand_ctx	exp_ctx;

	if (ctx->type == WORD && !ctx->prev_heredoc
		&& should_expand_dollar(ctx->token_str))
	{
		exp_ctx.head = ctx->head;
		exp_ctx.last = ctx->last;
		exp_ctx.token_str = ctx->token_str;
		exp_ctx.shell = ctx->shell;
		exp_ctx.alloc_list = ctx->alloc_list;
		if (handle_expansion(&exp_ctx))
			return (0);
		return (1);
	}
	current = create_token(ctx->token_str, ctx->type, ctx->alloc_list);
	append_token(ctx->head, current);
	return (1);
}

static int	tokenize_core(t_shell *shell, t_token **head,
	t_token_input *input)
{
	t_token_ctx	ctx;

	init_token_ctx(&ctx, shell, head, input);
	return (handle_word_token(&ctx));
}

t_token	*tokenize_line(t_shell *shell, char *line, t_list *alloc_list)
{
	int				i;
	int				len;
	t_token			*head;
	t_token_input	input;

	i = 0;
	head = NULL;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (!line[i])
			break ;
		len = get_token_length(line, i);
		if (len < 0)
			return (return_syntax(shell, len));
		input.segment = &line[i];
		input.len = len;
		input.alloc_list = alloc_list;
		if (!tokenize_core(shell, &head, &input))
			return (NULL);
		i += len;
	}
	return (head);
}
