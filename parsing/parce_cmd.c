/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:54:25 by sjoukni           #+#    #+#             */
/*   Updated: 2025/04/20 16:41:25 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_cmd *create_cmd()
{
    t_cmd *new_cmd;

    new_cmd = malloc(sizeof(t_cmd));
    if (!new_cmd)
        return (NULL);
    new_cmd->args = NULL;
    new_cmd->infile = NULL;
    new_cmd->outfile = NULL;
    new_cmd->append = 0;
    new_cmd->has_pipe = 0;
    new_cmd->next = NULL;
    return (new_cmd);
}

static int calculate_args(t_cmd *cmd)
{
    int i = 0;
    if (!cmd->args)
        return 0;
    while (cmd->args[i])
        i++;
    return i;
}
char *remove_quotes(const char *str)
{
    int i = 0;
    int j = 0;
    int in_single_quote = 0;
    int in_double_quote = 0;
    char *result = malloc(ft_strlen(str) + 1); 

    if (!result)
        return NULL;

    while (str[i])
    {
        if (str[i] == '\'' && !in_double_quote)
        {
            in_single_quote = !in_single_quote;
            i++;
        }
        else if (str[i] == '"' && !in_single_quote)
        {
            in_double_quote = !in_double_quote;
            i++;
        }
        else if(str[i] == '\\' && str[i + 1] == '"')
        {
            i += 1;
        }
        else
        {
            result[j++] = str[i++];
        }
    }
    result[j] = '\0';
    return result;
}


static void add_arg_to_cmd(t_cmd *cmd, char *arg)
{
    // printf("arg is %s\n", arg);
    arg = remove_quotes(arg);
    // printf("arg is %s\n", arg);
    int old_len = calculate_args(cmd);
    char **args = malloc(sizeof(char *) * (old_len + 2));
    if (!args)
        return;
    int i = 0;
    while (i < old_len)
    {
        args[i] = ft_strdup(cmd->args[i]);
        i++;
    }
    args[i++] = ft_strdup(arg);  
    args[i] = NULL;              
    if (cmd->args)
        free_array(cmd->args);
    cmd->args = args;
}

void add_cmd_to_list(t_cmd **head, t_cmd *new_cmd)
{
    t_cmd *temp;

    if (!*head)
    {
        *head = new_cmd;
        return;
    }
    temp = *head;
    while (temp->next)
        temp = temp->next;
    temp->next = new_cmd;
}

int handle_token_redirection_or_arg(t_token **current, t_cmd *cmd)
{
    t_token *token = *current;

    if (token->type == WORD)
    {
        add_arg_to_cmd(cmd, token->value);
    }
    else if (token->type == REDIR_IN || token->type == REDIR_OUT || token->type == APPEND || token->type == HEREDOC)
    {
        if (!token->next || token->next->type != WORD)
        {
            printf("syntax error near unexpected token\n");
            return 0;
        }

        char *target = ft_strdup(token->next->value);

        if (token->type == REDIR_IN)
            cmd->infile = target;
        else if (token->type == REDIR_OUT)
        {
            cmd->outfile = target;
            cmd->append = 0;
        }
        else if (token->type == APPEND)
        {
            cmd->outfile = target;
            cmd->append = 1;
        }
        else if (token->type == HEREDOC)
        {
            cmd->heredoc_delim = remove_quotes(target);
           
            cmd->heredoc_expand = !is_quote(*token->next->value);
            free(target);
        }

        *current = token->next; 
    }

    return 1;
}
t_cmd *build_cmd_list(t_token *tokens)
{
    t_cmd *cmd_list = NULL;
    t_cmd *current_cmd = create_cmd();
    t_token *current = tokens;

    while (current)
    {
        if (current->type == PIPE)
        {
            current_cmd->has_pipe = 1;
            add_cmd_to_list(&cmd_list, current_cmd);
            current_cmd = create_cmd();
        }
        else
        {
            if (!handle_token_redirection_or_arg(&current, current_cmd))
                return NULL; 
        }

        current = current->next;
    }

    add_cmd_to_list(&cmd_list, current_cmd);
    return cmd_list;
}
