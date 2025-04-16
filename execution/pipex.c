/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:22:52 by hakader           #+#    #+#             */
/*   Updated: 2025/04/12 17:58:36 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int main(int ac, char **av, char *envp[])
{
	if (ac != 5)
		put_error("you need 4 inputs");
	int infile = open("infile", O_RDONLY);
	int outfile = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (infile == -1 || outfile == -1)
		put_error("failed to open file");
	int fd[2];

	if (pipe(fd) == -1)
		put_error("failed to create pipe");
	
}