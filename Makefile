NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -I$(INC_DIR)

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

SRC = $(SRC_DIR)/main.c \
      $(SRC_DIR)/parse.c \
      $(SRC_DIR)/init.c \
      $(SRC_DIR)/utils.c \
      $(SRC_DIR)/philo_routine.c \
      $(SRC_DIR)/philo_utils.c \
      $(SRC_DIR)/monitor.c \
      $(SRC_DIR)/rules_init.c \
      $(SRC_DIR)/single_philo.c

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

HEADER = $(INC_DIR)/philo.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re