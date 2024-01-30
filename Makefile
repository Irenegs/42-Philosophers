NAME        := philo

SRC			:= main.c utils.c validate.c

OBJ			:= $(SRC:%.c=%.o)

CC          := gcc 
CFLAGS      := -lpthread -Wall -Wextra -Werror
#-fsanitize=address -g3

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
.SILENT:
