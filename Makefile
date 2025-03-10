CC = cc 

CFLAGS = -Wall -Wextra -Werror -Iinc -g

PRINT = printf

NAME = philo

SRC = handle_thread_mutex.c monitoring.c philo_data.c philo_input.c\
	philo_mutex.c philo_simulation.c philo_utils.c philo.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@clear
	@make -s -C $(PRINT)
	@$(CC) $(CFLAGS) $(OBJ) -L$(PRINT) -lftprintf -o $(NAME)
	@echo -n "  Compiling"
	@bash ./loading.sh
	@clear
	@echo "\033[32m ✓ \033[0m Compilation successful!"

.c.o: 
	@$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

clean: 
	@make clean -s -C $(PRINT)
	@rm -f $(OBJ)

fclean: clean
	@clear
	@echo -n "  Cleaning"
	@bash ./loading.sh
	@rm -f $(NAME)
	@echo "\033[32m ✓ \033[0m Clean complete!"
re: fclean all

.PHONY:	all clean fclean