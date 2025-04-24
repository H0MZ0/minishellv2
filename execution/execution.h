/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:49:02 by hakader           #+#    #+#             */
/*   Updated: 2025/04/24 22:53:52 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../minishell.h"

typedef struct s_memblock {
    void *ptr;
    struct s_memblock *next;
} t_memblock;

void	execution_part(t_cmd *cmd_list, t_env *env_list, char **envp);
void	print_arr(char **arr);
void	free_arr(char **str);
void	put_error(char *msg);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strcmp(const char *str1, const char *str2);
char	**get_paths(t_env *env_list);
char	*check_cmd(char **paths, char *cmd);
int		count_args(char **args);
void	mini_display(void);
void	print_this(t_env **env_list, char *sch);
// char	*ft_strdup(char *str);

//BUILT_IN
int		is_builtin(t_cmd *cmd, t_env *envp);
int		execute_echo(t_cmd *cmd);
int 	execute_pwd(void);
int	    execute_cd(t_cmd *cmd, t_env **env_list);
int		execute_env(t_env *envp);
void	execute_exit(void);

//BUILT_IN_HELPERS
int 	is_new_line(char *arg);
void	env_path(t_env **env_list, t_cmd *cmd);
//FREE
void    *ft_malloc(size_t size);
void    ft_free_all(void);


#endif
