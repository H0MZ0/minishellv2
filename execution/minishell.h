/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:49:02 by hakader           #+#    #+#             */
/*   Updated: 2025/04/13 19:19:13 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <limits.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

// typedef struct s_token
// {
// 	char *value;
// 	int type; 
// 	struct s_token *next;
// } t_token;

// typedef enum e_token_type
// {
//     WORD,       // 0: words
//     PIPE,       // 1: |
//     REDIR_IN,   // 2: <
//     REDIR_OUT,  // 3: >
//     APPEND,     // 4: >>
//     HEREDOC     // 5: <<
// } t_token_type;

typedef struct s_cmd {
	char **args;         // command and its arguments
	char *infile;        // file for input redirection
	char *outfile;       // file for output redirection
	int append;          // 1 if >>
	int has_pipe;        // 1 if this cmd is followed by |
	struct s_cmd *next;
} t_cmd;

//CHECK
void    is_builtin(char *cmd1, char *cmd2, char *cmd3, char *cmd4);
void	execute_echo(char *param, char *input);
void	execute_pwd(void);
// void    execute_cd()

//TOOLS
size_t  ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int	ft_strcmp(const char *str1, const char *str2);
char	*ft_strdup(char *str);

//FT_FREE
void	free_arr(char **str);
//ERROR
void    put_error(char *msg);
//SPLIT
char	**ft_split(char const *s, char c);

//strjoin
char	*ft_strjoin(char const *s1, char const *s2);

//BUILT_IN
int	execute_cd(char *path);



#endif
