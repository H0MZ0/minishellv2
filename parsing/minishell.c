/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:23:38 by sjoukni           #+#    #+#             */
/*   Updated: 2025/05/02 13:14:04 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_empty(char *line)
{
	return (line[0] == '\0');
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	char	*line;
	t_shell	*shell = malloc(sizeof(t_shell));
	if (!shell)
		return (1);
	shell->env = NULL;
	shell->tokens = NULL;
	shell->cmds = NULL;
	shell->last_exit_status = 0;

	int i = 0;
	while (envp[i])
	{
		t_env *node = env_copy(envp[i]);
		if (node)
			append_env(&shell->env, node);
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
			free_shell(shell);
			exit(0);
		}

		else if (is_empty(line))
		{
			free(line);
		}

		add_history(line);

		shell->tokens = tokenize_line(line);
		if (shell->tokens && check_syntax(shell->tokens))
		{
			shell->cmds = build_cmd_list(shell->tokens);
			if (shell->cmds)
			{
				print_cmd_list(shell->cmds);
				// execution_part(shell->cmds, shell->env, envp, shell);
			}
		}

		free_token_list(shell->tokens);
		shell->tokens = NULL;
		// free_cmd_list(shell->cmds);
		// shell->cmds = NULL;
		free(line);
	}

	free_shell(shell);
	return (0);
}
