/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:20:48 by sjoukni           #+#    #+#             */
/*   Updated: 2025/04/14 17:45:02 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}		t_env;

typedef struct s_token
{
	char *value;
	int type; 
	struct s_token *next;
} t_token;

typedef enum e_token_type
{
    WORD,       // 0: words
    PIPE,       // 1: |
    REDIR_IN,   // 2: <
    REDIR_OUT,  // 3: >
    APPEND,     // 4: >>
    HEREDOC     // 5: <<
} t_token_type;

typedef struct s_cmd {
	char **args;         // command and its arguments
	char *infile;        // file for input redirection
	char *outfile;       // file for output redirection
	int append;          // 1 if >>
	int has_pipe;        // 1 if this cmd is followed by |
	struct s_cmd *next;
} t_cmd;


# include <fcntl.h>
# include <limits.h>
# include <stddef.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "../execution/minishell.h"
# include "../libft/libft.h"


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



#endif