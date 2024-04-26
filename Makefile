NAME        := philo

SRC			:= clear.c death.c eat_functions.c living.c main.c message.c setting.c time.c utils.c validate.c

OBJ			:= $(SRC:%.c=%.o)

CC          := gcc
CFLAGS      := -Wall -Wextra -Werror

RM          := rm -f

all: $(NAME)
$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: clean fclean re
