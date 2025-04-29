NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

HEADER = execution/execution.h parsing/parsing.h minishell.h

PRS_FILES = parsing/minishell.c parsing/parcing.c parsing/parce_dollar.c parsing/handel_error.c \
			parsing/parce_cmd.c parsing/env_copy.c parsing/free_all.c parsing/print_lists.c \
			parsing/pipe.c parsing/signals.c

EXC_FILES = execution/tools_1.c execution/tools_2.c \
			execution/execution.c \
			execution/in_out.c execution/builtin/built_in.c \
			execution/builtin/exp_uns.c execution/builtin/expuns_utils1.c \
			execution/builtin/expuns_utils2.c execution/ft_malloc.c \
			execution/builtin/echo.c

POBJ_FILES = $(PRS_FILES:.c=.o)
EOBJ_FILES = $(EXC_FILES:.c=.o)

all: $(LIBFT) $(NAME)

$(NAME): $(POBJ_FILES) $(EOBJ_FILES)
	$(CC) $(CFLAGS) $(POBJ_FILES) $(EOBJ_FILES) $(LIBFT) -lreadline -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(POBJ_FILES) $(EOBJ_FILES)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
