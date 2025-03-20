SHELL = /bin/bash
CC = cc 
CFLAGS = -Wall -Wextra -Werror -g -pthread

NAME = philo

SRC = handle_thread_mutex.c monitoring.c philo_data.c philo_input.c\
	philo_mutex.c philo_simulation.c philo_utils.c philo.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@clear
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo -n "  Compiling"
	@$(MAKE) -s loading
	@clear
	@echo -e "\033[32m ✓ \033[0m Compilation successful!"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean: 
	@rm -f $(OBJ)

fclean: clean
	@clear
	@echo -n "  Cleaning"
	@$(MAKE) -s loading
	@rm -f $(NAME)
	@echo -e "\033[32m ✓ \033[0m Clean complete!"

re: fclean all

loading:
	@spin=("⠁" "⠃" "⠇" "⠧" "⠷" "⠿" "⠷" "⠧" "⠇" "⠃"); \
	for i in {1..1}; do \
		for j in $${spin[@]}; do \
			echo -ne "$$j\r"; \
			sleep 0.1; \
		done; \
	done

.PHONY: all clean fclean loading

