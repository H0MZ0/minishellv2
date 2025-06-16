NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
HEADER = minishell.h 

SRC = parsing/array_helpers.c parsing/env_copy.c parsing/get_token_length.c \
      parsing/handle_token_redirection.c parsing/parce_cmd.c parsing/parcing.c \
      parsing/signals.c parsing/token_utils.c parsing/build_cmd_list.c \
      parsing/expand.c parsing/handel_error.c parsing/minishell.c \
      parsing/parce_dollar.c parsing/token_helpers.c parsing/handle_redirection.c \
      execution/tools_1.c execution/tools_2.c execution/execution.c \
      execution/in_out.c execution/pipe.c execution/exit_status.c \
      execution/heredoc.c execution/errors.c execution/builtin/built_in.c \
      execution/builtin/ft_echo.c execution/builtin/ft_exit.c \
      execution/builtin/ft_export.c execution/builtin/ft_export_helpers.c \
      execution/builtin/ft_unset.c execution/builtin/ft_cd.c \
      execution/builtin/ft_env.c execution/builtin/ft_pwd.c \
      execution/builtin/ft_export_helpers2.c execution/print.c \
      execution/pipe_redirection.c  execution/heredoc_utils.c  execution/pipe_utils.c \
      libft/ft_malloc.c libft/ft_strcmp.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ) 
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re bonus

.SECONDARY:
