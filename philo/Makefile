CC = cc
CFLAGS = -Wall -Werror -Wextra #-ggdb -fsanitize=thread
SRC = main.c main_utils.c monitor_utils.c parsing.c parsing_utils.c philos.c philo_utils.c
NAME = philo
OBJECT = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJECT)
	$(CC) $(CFLAGS) $(OBJECT) -o $(NAME)

clean:
	rm -f $(OBJECT)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
