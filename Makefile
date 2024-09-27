NAME = pipex
NAME_BNS = pipex_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror 
SRC_MAIN = main_func.c 
SRC_BNS = main_bonus.c 

SRC = ft_split.c libft_func.c r_wr_func.c pipes.c parent_func.c \
	pipes_utils.c get_path.c  get_next_line.c get_next_line_utils.c 

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

.PHONY: all clean fclean re bonus 
