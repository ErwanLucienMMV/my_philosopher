RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m
MAKEFLAGS += --no-print-directory
CC      = cc
CFLAGS  = -Wall -Wextra -Werror

SRC = src/main.c \
      src/parse_argument.c \
	  src/utils.c \
	  src/debug.c \
	  src/simulation_helpers.c \
	  src/simulation_functions.c \
	  src/init.c \
	  src/cleanup.c 

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