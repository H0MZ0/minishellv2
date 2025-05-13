/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoukni <sjoukni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:01:14 by sjoukni           #+#    #+#             */
/*   Updated: 2025/05/13 15:56:49 by sjoukni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h" 

void	read_heredoc(t_cmd *cmd, t_shell *shell, t_list *alloc_list)
{
	int		pipe_fd[2];
	char	*line;

	if (!cmd->heredoc_delim)
		return ;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		line = readline("> ");
		if (!line)
			break;
		if (ft_strcmp(line, cmd->heredoc_delim) == 0)
		{
			free(line);
			break;
		}

		if (cmd->heredoc_expand)
			line = expand_token_value(line, shell, alloc_list);

		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	cmd->heredoc_fd = pipe_fd[0];  
}
