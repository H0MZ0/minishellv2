/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:13:18 by sjoukni           #+#    #+#             */
/*   Updated: 2025/05/12 17:03:43 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void print_list_env(t_env **head)
{
    t_env *tmp = *head;

    while (tmp)
    {
        printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
        tmp = tmp->next;
    }
}

void print_cmd_list(t_cmd *cmd_list)
{
    int i;
    int cmd_num = 1;

    while (cmd_list)
    {
        printf("🔹 CMD %d:\n", cmd_num++);

        printf("  args    = ");
        if (cmd_list->args)
        {
            i = 0;
            while (cmd_list->args[i])
                printf("\"%s\" ", cmd_list->args[i++]);
        }
        else
            printf("(none)");
        printf("\n");

        // Print redirections
        printf("  infile  = %s\n", cmd_list->infile ? cmd_list->infile : "(none)");
        printf("  outfile = %s\n", cmd_list->outfile ? cmd_list->outfile : "(none)");
        printf("  append  = %d\n", cmd_list->append);
        printf("  pipe    = %s\n", cmd_list->has_pipe ? "true" : "false");
        printf("  herdok  = %s\n", cmd_list->heredoc_delim);
        printf("  herdok num = %d\n", cmd_list->heredoc_expand);
        printf("\n");

        cmd_list = cmd_list->next;
    }
}

void print_list(t_token *head)
{
	t_token *tmp = head;

	while (tmp)
	{
		printf("value: %s || type: %d\n", tmp->value, tmp->type);
		tmp = tmp->next;
	}
}