NAME = minishell
CC = cc
# CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_SRC = $(wildcard libft/*.c)

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
      execution/pipe_redirection.c \
      libft/ft_malloc.c libft/ft_strcmp.c

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT): $(LIBFT_SRC) libft/libft.h
	$(MAKE) -C $(LIBFT_DIR)

all: $(LIBFT) $(NAME)

clean:
	@rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

.SECONDARY:
