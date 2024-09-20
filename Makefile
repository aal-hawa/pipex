NAME = pipex
NAME_BNS = pipex_b
CC = cc
CFLAGS = -Wall -Wextra -Werror 
SRC_MAIN = main_fun.c 
SRC_BNS = main_bonus.c 

SRC = ft_split.c libft_fun.c r_wr_func.c pipes.c \
	pipes_utils.c where_func.c  get_next_line.c get_next_line_utils.c 

OBGS = $(SRC:.c=.o) $(SRC_MAIN:.c=.o)

OBGS_BNS = $(SRC:.c=.o) $(SRC_BNS:.c=.o)

all: $(NAME)

$(NAME): $(OBGS)
	$(CC) $(OBGS) -o $(NAME)

$(NAME_BNS): $(OBGS_BNS)
	$(CC) $(OBGS_BNS) -o $(NAME_BNS)

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBGS) $(OBGS_BNS)

fclean: clean
	rm -f $(NAME) $(NAME_BNS)

re: fclean all

bonus: $(NAME_BNS)

.PHONY: all clean fclean re