/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:49:02 by hakader           #+#    #+#             */
/*   Updated: 2025/04/16 17:19:23 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../minishell.h"

void	execution_part(t_cmd *cmd_list, t_env *env_list, char **av, char **envp);
void	is_builtin(char *cmd1, char *cmd2, char *cmd3, char *cmd4);
void	execute_echo(char *param, char *input);
void	execute_pwd(void);
int		execute_cd(char *path);
void	free_arr(char **str);
void	put_error(char *msg);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strcmp(const char *str1, const char *str2);
char	**get_paths(t_env *env_list);
char	*check_cmd(char **paths, char *cmd);
// char	*ft_strdup(char *str);

#endif
