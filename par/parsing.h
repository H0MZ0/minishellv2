/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:20:48 by sjoukni           #+#    #+#             */
/*   Updated: 2025/04/19 18:07:23 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../minishell.h"

t_token	*tokenize_line(char *line, t_env *env, int last_exit_status);
char	*expand_token_value(char *value, t_env *env, int last_exit);
int		check_syntax(t_token *token_list);
t_cmd	*build_cmd_list(t_token *tokens);
t_env	*env_copy(char *content);
int		ft_isspace(int c);
void	append_env(t_env **head, t_env *new_node);
void	free_array(char **arr);
void	print_list_env(t_env **head);
void	print_cmd_list(t_cmd *cmd_list);
void	print_list(t_token *head);
int		is_empty(char *line);
void    pipex(t_cmd *cmd, char **envp);

#endif
