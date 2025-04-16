CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = minishell.c tools_1.c ft_split.c ft_strjoin.c check_1.c built_in.c \
		
OSRC = $(SRC:.c=.o)

NAME = minishell
HEADER = minishell.h

all : $(NAME)

$(NAME) : $(OSRC) $(HEADER)
	@$(CC) $(CFLAGS) $(OSRC) -o $(NAME) -lreadline -lhistory

clean :
	@rm -f $(OSRC)

fclean : clean
	@rm -f $(NAME)
re : fclean all

.PHONY : all clean fclean re