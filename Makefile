NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread

SRC = main.c parse.c init.c utils.c philo_routine.c philo_utils.c monitor.c rules_init.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean fcleanall re