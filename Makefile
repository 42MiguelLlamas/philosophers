NAME = philo
SRCS = main.c checkArgs.c aux.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Werror -Wextra -fsanitize=address

.PHONY: all clean fclean re

all: $(NAME)

%.o: %.c
	cc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

$(NAME): $(OBJS)
	$(CC) $(CFLAGS)  -o $(NAME) $(OBJS)