/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:56:19 by hakader           #+#    #+#             */
/*   Updated: 2025/06/18 10:30:03 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define EXIT_CMD_NOT_FOUND 127
# define EXIT_INVALID_ARGS 2

# include "structs.h"
# include "execution/execution.h"
# include "parsing/parsing.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define RESET   "\001\x1b[0m\002"
# define BLACK   "\001\x1b[30m\002"
# define RED     "\001\x1b[31m\002"
# define GREEN   "\001\x1b[32m\002"
# define YELLOW  "\001\x1b[33m\002"
# define BLUE    "\001\x1b[34m\002"
# define MAGENTA "\001\x1b[35m\002"
# define CYAN    "\001\x1b[36m\002"
# define WHITE   "\001\x1b[37m\002"

# define PROMPT "\001\x1b[36m\002💃minishell$ \001\x1b[0m\002"

#endif