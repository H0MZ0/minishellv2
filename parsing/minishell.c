/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:23:38 by sjoukni           #+#    #+#             */
/*   Updated: 2025/04/24 18:50:37 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int is_empty(char *line)
{
	if (line[0] == '\0')
	{
		return (1);
	}
	return 0;
}
int main(int ac, char **av, char **envp)
{
    (void) ac;
    (void) av;

    char *line;
    int i = 0;
    t_env *env_list = NULL;
    t_token *cmd = NULL;
    t_cmd *f_cmd = NULL;

    while (envp[i])
    {
        t_env *node = env_copy(envp[i]);
        if (node)
            append_env(&env_list, node);
        i++;
    }

    mini_display();

    while (1)
    {
        set_prompt_signals();
        line = readline(CYAN "minishell$ " RESET);

        if (!line)
        {
            free(line); 
            free_env_list(env_list);
            exit(0);
        }

        if (is_empty(line))
        {
            free(line);
            continue;
        }

        add_history(line);

        int last = 0;
        cmd = tokenize_line(line, env_list, last);
        if (cmd && check_syntax(cmd))
        {
            f_cmd = build_cmd_list(cmd);
            if (f_cmd)
            {
                // print_cmd_list(f_cmd);
                // parce_cmd(f_cmd);
                execution_part(f_cmd, env_list, envp);
                // free_cmd_list(f_cmd);
            }
        }

        // free_token_list(cmd);
        free(line);        
    }

    free_env_list(env_list);
    return 0;
}

