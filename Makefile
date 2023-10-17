NAME		= 		philo

SRCS		=		main.c 

OBJS 		=		$(addprefix objs/, $(SRCS:.c=.o))

CFLAGS		=		-g -Wall -Wextra -Werror

RM			=		rm -f

COLOUR_GREEN=\033[32m
COLOUR_RED=\033[31m
COLOUR_END=\033[0m

objs/%.o: srcs/%.c
					@mkdir -p objs
					@cc $(CFLAGS) -c $< -o $@

ifeq ($(shell uname), Linux)
install: install-linux
else
install: install-mac
endif

install-linux:
	python3 -m pip install --upgrade pip setuptools
	python3 -m pip install norminette
	sudo apt install valgrind -y

install-mac:
	python3 -m pip install --upgrade pip setuptools
	python3 -m pip install norminette

check:
		python3 -m norminette

$(NAME):    	$(OBJS)
					@cc $(OBJS) $(CFLAGS) -o $(NAME) -lpthread #-fsanitize=thread
					@echo "$(COLOUR_GREEN)philo Compiled! ᕦ$(COLOUR_RED)♥$(COLOUR_GREEN)_$(COLOUR_RED)♥$(COLOUR_GREEN)ᕤ\n$(COLOUR_END)"

all:      	$(NAME)

clean:
					@$(RM) $(OBJS)
					@echo "$(COLOUR_RED)Deleting all objs! ⌐(ಠ۾ಠ)¬\n$(COLOUR_END)"

fclean:		clean
					@$(RM) $(NAME)

re:         fclean all