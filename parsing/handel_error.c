/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:46:03 by sjoukni           #+#    #+#             */
/*   Updated: 2025/04/14 11:15:35 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_redirection(t_token_type type)
{
    return (type == REDIR_OUT || type == REDIR_IN || type == APPEND || type == HEREDOC);
}

int  print_error(char *message)
{
    printf("%s\n", message);
    return 0;
}

int check_syntax(t_token *token_list)
{
    t_token *current = token_list;
    t_token *prev = NULL;

    if (!current)
        return print_error("error: empty input");
    if (current->type == PIPE)
        return print_error("syntax error near unexpected token `|`");
    while (current)
    {
        if (prev && prev->type == PIPE && current->type == PIPE)
            return print_error("syntax error near unexpected token `|`");

        if (is_redirection(current->type))
        {
            if (!current->next || current->next->type != WORD)
                return print_error("syntax error: missing filename after redirection");
        }

        prev = current;
        current = current->next;
    }
    if (prev && prev->type == PIPE)
        return print_error("syntax error: unexpected end of input after `|`");

    return 1;
}

