/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:54:25 by sjoukni           #+#    #+#             */
/*   Updated: 2025/04/14 16:26:42 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd *create_cmd()
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

int calculate_args(t_cmd *cmd)
{
    int i = 0;
    if (!cmd->args)
        return 0;
    while (cmd->args[i])
        i++;
    return i;
}

void add_arg_to_cmd(t_cmd *cmd, char *arg)
{
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
char *copy_token_value(char *src)
{
    if (!src)
        return NULL;
    return ft_strdup(src);
}


t_cmd *build_cmd_list(t_token *tokens)
{
    t_cmd *cmd_list = NULL;
    t_cmd *current_cmd = create_cmd();
    t_token *current = tokens;
    int redir_type;
    while (current)
    {
        if (current->type == WORD)
        {
            add_arg_to_cmd(current_cmd, current->value);
        }
        else if (current->type == REDIR_IN || current->type == REDIR_OUT || current->type == APPEND)
        {
            redir_type = current->type;
            current = current->next;
            if (current && current->type == WORD)
            {
                if (redir_type == REDIR_IN)
                    current_cmd->infile = copy_token_value(current->value);
                else if (redir_type == REDIR_OUT)
                {
                    current_cmd->outfile = copy_token_value(current->value);
                    current_cmd->append = 0;
                }
                else if (redir_type == APPEND)
                {
                    current_cmd->outfile = copy_token_value(current->value);
                    current_cmd->append = 1;
                }
            }
            else
            {
                return 0;
            }
        }
        else if (current->type == PIPE)
        {
            current_cmd->has_pipe = 1;
            add_cmd_to_list(&cmd_list, current_cmd);
            current_cmd = create_cmd();
        }

        current = current->next;
    }

    add_cmd_to_list(&cmd_list, current_cmd);
    return cmd_list;
}
