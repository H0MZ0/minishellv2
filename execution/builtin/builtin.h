/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 02:54:02 by hakader           #+#    #+#             */
/*   Updated: 2025/04/25 02:56:21 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




int	is_builtin(t_cmd *cmd, t_env *envp);
int	execute_echo(t_cmd *cmd);
int	execute_pwd(void);
int	execute_env(t_env *envp);
int	execute_cd(t_cmd *cmd, t_env **env);
int	execute_export(t_cmd *cmd, t_env **envp);
int	execute_unset(t_cmd *cmd, t_env **envp);
int	is_valid_key(const char *str);
t_env	*find_env(t_env *env, const char *key);
char	*extract_key(const char *str);
char	*extract_value(const char *str);
void	add_or_update_env(t_env **env, char *arg);
void	remove_env_var(t_env **envp, const char *key);;
int	is_new_line(char *arg);
void	env_path(t_env **env_list, t_cmd *cmd);
void	execute_exit(void);
