NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror 
SRC_MAIN = main_fun.c 

SRC = ft_split.c libft_fun.c r_wr_func.c pipes.c \
	forks.c where_func.c 


OBGS = $(SRC:.c=.o) $(SRC_MAIN:.c=.o)

all: $(NAME)

$(NAME): $(OBGS)
	$(CC) $(OBGS) -o $(NAME)

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBGS) $(OBGS_BNS)

fclean: clean
	rm -f $(NAME) $(NAME_BNS)

re: fclean all

bonus: $(NAME_BNS)

.PHONY: all clean fclean re