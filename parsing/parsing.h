/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:20:48 by sjoukni           #+#    #+#             */
/*   Updated: 2025/04/24 15:51:03 by sjoukni          ###   ########.fr       */
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

char	*parce_line(char *line);
t_token	*tokenize_line(char *line);
char	*expand_token_value(char *value, t_env *env, int last_exit);
int		check_syntax(t_token *token_list);
t_cmd	*build_cmd_list(t_token *tokens);
t_env	*env_copy(char *content);
int		ft_isspace(int c);

// Utility and freeing
void	append_env(t_env **head, t_env *new_node);
void	free_array(char **arr);
void	print_list_env(t_env **head);
void	print_cmd_list(t_cmd *cmd_list);
void	print_list(t_token *head);
void	pipex(t_cmd *cmd, char **envp);

// Freeing logic
void	free_cmd(t_cmd *cmd);
void	free_cmd_list(t_cmd *cmd_list);
void	free_token_list(t_token *head);
void	free_env_list(t_env *env);
void	free_shell(t_shell *shell);  

// Signal handling
void	set_prompt_signals(void);
void	set_child_signals(void);
void	set_heredoc_signals(void);

#endif
