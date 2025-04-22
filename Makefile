NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

HEADER =  execution/execution.h parsing/parsing.h minishell.h

PRS_FILES = parsing/minishell.c parsing/parcing.c parsing/parce_dollar.c parsing/handel_error.c \
			parsing/parce_cmd.c parsing/env_copy.c parsing/free_all.c parsing/print_lists.c \
			parsing/pipe.c

EXC_FILES = execution/tools_1.c execution/tools_2.c execution/ft_split.c \
			execution/built_in.c execution/ft_free.c execution/execution.c \
			execution/built_in_helpers.c

POBJ_FILES = $(PRS_FILES:.c=.o)
EOBJ_FILES = $(EXC_FILES:.c=.o)

all: $(NAME)

$(NAME): $(POBJ_FILES) $(EOBJ_FILES) $(LIBFT)
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

re: fclean all

.PHONY: all bonus clean fclean re