/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:20:48 by sjoukni           #+#    #+#             */
/*   Updated: 2025/05/12 16:08:49 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <fcntl.h>
# include <limits.h>
# include <stddef.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include "../libft/libft.h"
# include "../minishell.h"

t_token *tokenize_line(t_shell *shell, char *line, t_list *alloc_list);
char    *expand_token_value(char *value, t_shell *shell, t_list *alloc_list);
int		check_syntax(t_token *token_list);
t_cmd	*build_cmd_list(t_token *tokens, t_list *alloc_list);
t_env	*env_copy(char *content, t_list	*alloc_list);
int		ft_isspace(int c);

// Utility
void	append_env(t_env **head, t_env *new_node);
void	print_list_env(t_env **head);
void	print_cmd_list(t_cmd *cmd_list);
void	print_list(t_token *head);


// Signal handling
void	set_prompt_signals(t_shell *shell);
void	set_child_signals(void);
void	set_heredoc_signals(t_shell *shell);

#endif
