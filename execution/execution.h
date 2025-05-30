/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:49:02 by hakader           #+#    #+#             */
/*   Updated: 2025/05/29 18:53:54 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../libft/libft.h"
# include "../minishell.h"

/* ======================== EXECUTION CORE ======================== */

void	execution_part(t_shell *shell, t_list **alloc_list);
// void	mini_display(void);
// void	print_arr(char **arr);
// void	print_this(t_env **env_list, char *sch);

/* ======================== BUILTIN COMMANDS ======================== */

int		execute_cd(t_cmd *cmd, t_env **env, t_list *alloc_list);
int		execute_pwd(t_cmd *cmd);
int		execute_echo(t_cmd *cmd);
int		execute_env(t_cmd *cmd, t_env *envp);
void	execute_exit(t_shell *shell, t_list *alloc_list);
int		execute_export(t_shell **shell, t_list *alloc_list);
int		excute_unset(t_shell **shell, t_list *alloc);
int		exec_builtin(t_shell **shell, t_cmd *cmd, t_list *alloc_list);

/* ======================== BUILTIN HELPERS ======================== */

int		check_exp(t_shell *shell, t_list *alloc_list);
void	update_env(t_env **env, char *key, char *val, t_list *alloc);
void	ft_envadd_back(t_env **env, char *key, char *val, t_list *alloc);

/* ======================== PATH RESOLUTION ======================== */

char	**get_paths(t_shell **shell, t_list *alloc_list);
char	*check_cmd(char **paths, char *cmd, t_list *alloc_list);
int		count_args(char **args);

/* ======================== STRING UTILS ======================== */

int		ft_strcmp(const char *str1, const char *str2);

/* ======================== REDIRECTIONS ======================== */

int		read_heredoc(t_cmd *cmd, t_shell *shell, t_list *alloc_list);

/* ======================== PIPES ======================== */

void	pipex(t_shell **shell, t_list *alloc_list);
int		check_inout(t_shell *shell);
int		is_builtin_name(const char *name);
void	update_exit_status(t_shell *shell, pid_t pid);
void	set_cmd_not_found(t_shell *shell, char *cmd);
int		if_builtin(t_shell *shell, t_list *alloc_list);
int		is_valid_key(char *s);
void	non_valide(t_shell **shell, char *identifier);
char	*get_value(char *arg, t_list *alloc_list);
void	err_dir(t_shell *shell);
int		err_write(void);
void	swap_env(t_env *a, t_env *b);
t_env	*copy_env(t_env *env, t_list *alloc_list);
char	*get_key(char *arg, t_list *alloc_list);
int		check_options(t_cmd *cmd, char *msg);
int		check_all_infiles(t_shell *shell, char **infiles);
int		check_all_outfiles(t_shell *shell, char **outfiles, int *append_flags);
void	print_cmd_list(t_cmd *cmd_list);
void	print_list_env(t_env **head, t_list *alloc_list);
int		infiless(t_shell *shell, char *infile);
int		in_out(t_shell *shell);
int		oi_err(t_shell *shell, char *err);

#endif
