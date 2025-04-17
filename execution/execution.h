/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:49:02 by hakader           #+#    #+#             */
/*   Updated: 2025/04/17 16:44:08 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../minishell.h"

void	execution_part(t_cmd *cmd_list, t_env *env_list, char **av, char **envp);
int     is_builtin(t_cmd *cmd);
int     execute_echo(t_cmd *cmd);
void    print_arr(char **arr);
void	execute_pwd(void);
int     execute_cd(t_cmd *cmd);
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
