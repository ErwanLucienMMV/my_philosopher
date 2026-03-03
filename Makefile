RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m
MAKEFLAGS += --no-print-directory
CC      = cc
CFLAGS  = -Wall -Wextra -Werror

SRC = main.c \

OBJ = $(SRC:.c=.o)

NAME = philo

all: $(NAME)

debug: CFLAGS += -g -D IS_DEBUG=1

debug: re

$(NAME): $(OBJ)
	@echo "$(YELLOW)[philo] $(GREEN).o created $(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(YELLOW)[philo] $(GREEN)executable created$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@



clean:
	@rm -f $(OBJ)
	@echo "$(YELLOW)[philo] $(RED).o deleted$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(YELLOW)[philo] $(RED).a deleted$(RESET)"

re: fclean all