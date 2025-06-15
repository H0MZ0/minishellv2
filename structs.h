/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 21:13:58 by sjoukni           #+#    #+#             */
/*   Updated: 2025/06/15 21:36:55 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "libft/libft.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}					t_token;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	APPEND,
	REDIR_OUT,
	HEREDOC,
	SEMICOLON
}					t_token_type;

typedef struct s_heredoc_tmp
{
	char			*delim;
	int				expand;
}					t_heredoc_tmp;

typedef struct s_cmd
{
	char			**args;
	char			**infiles;
	char			**outfiles;
	int				*rediriction_ag;
	int				*append_flags;
	char			**rediriction;
	int				has_pipe;
	t_heredoc_tmp	*heredocs;
	int				heredoc_count;
	char			*heredoc_delim;
	int				heredoc_expand;
	int				heredoc_fd;
	int				input_error;
	int				len;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_shell
{
	t_env			*env;
	t_token			*tokens;
	t_cmd			*cmds;
	int				skip_syntax_error;
	char			**envp;
	int				exit_status;
	int				in;
	int				out;
}					t_shell;

typedef struct s_build_ctx
{
	t_cmd			*cmd_list;
	t_cmd			*current_cmd;
	t_list			*alloc_list;
	t_shell			*shell;
}					t_build_ctx;

typedef struct s_token_input
{
	char			*segment;
	int				len;
	t_list			*alloc_list;
}					t_token_input;

typedef struct s_token_ctx
{
	t_shell			*shell;
	t_token			**head;
	t_token			*last;
	t_list			*alloc_list;
	char			*token_str;
	int				prev_heredoc;
	t_token_type	type;
}					t_token_ctx;

typedef struct s_expand_ctx
{
	t_token			**head;
	t_token			*last;
	char			*token_str;
	t_shell			*shell;
	t_list			*alloc_list;
}					t_expand_ctx;

typedef struct s_pipex_info
{
	t_shell			*shell;
	t_list			*alloc_list;
	char			**paths;
	int				prev_fd;
	pid_t			last_pid;
}					t_pipex_info;

typedef struct s_exec_state
{
	t_shell		*shell;
	t_list		*alloc_list;
	t_cmd		*current;
	char		**paths;
	int			prev_fd;
}	t_exec_state;
typedef struct s_exec_data
{
	t_shell		*shell;
	t_cmd		*cmd;
	char		**paths;
	int			in_fd;
	int			out_fd;
	t_list		*alloc_list;
}	t_exec_data;

#endif /* STRUCTS_H */
