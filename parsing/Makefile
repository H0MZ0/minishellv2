NAME = minishell
CC = cc
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
CFLAGS = -Wall -Wextra -Werror 
HEADER = parsing.h 

SRC_FILES = minishell.c parcing.c parce_dollar.c handel_error.c parce_cmd.c env_copy.c free_all.c print_lists.c pipe.c


OBJ_FILES = $(SRC_FILES:.c=.o)

all: $(NAME)


$(NAME): $(OBJ_FILES) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) -lreadline -o $(NAME)

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_FILES) 
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re bonus

