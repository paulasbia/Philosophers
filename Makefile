NAME		= 		philo

SRCS		=		main.c errors.c checks.c utils.c threads.c starts.c frees.c

OBJS 		=		$(addprefix objs/, $(SRCS:.c=.o))

CFLAGS		=		-g -Wall -Wextra -Werror

RM			=		rm -f

COLOUR_GREEN=\033[32m
COLOUR_RED=\033[31m
COLOUR_END=\033[0m

objs/%.o: srcs/%.c
					@mkdir -p objs
					@cc $(CFLAGS) -c $< -o $@

$(NAME):    	$(OBJS)
					@cc $(OBJS) $(CFLAGS) -o $(NAME) -lpthread #-fsanitize=thread
					@echo "$(COLOUR_GREEN)Philo Compiled! ᕦ$(COLOUR_RED)♥$(COLOUR_GREEN)_$(COLOUR_RED)♥$(COLOUR_GREEN)ᕤ$(COLOUR_END)"

all:      	$(NAME)

ifeq ($(shell uname), Linux)
install: install-linux
else
install: install-mac
endif

install-linux:
	@python3 -m pip install --upgrade pip setuptools
	@python3 -m pip install norminette
	@sudo apt update
	@sudo apt install valgrind -y

install-mac:
	@python3 -m pip install --upgrade pip setuptools
	@python3 -m pip install norminette

check:
		python3 -m norminette


clean:
					@$(RM) $(OBJS)
					@echo "$(COLOUR_RED)Deleting all objs! ⌐(ಠ۾ಠ)¬$(COLOUR_END)"

fclean:		clean
					@$(RM) $(NAME)

re:         fclean all

.PHONY: all clean fclean re install 