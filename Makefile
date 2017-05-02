CC	:= gcc

RM	:= rm -rf

LDFLAGS	+= -lncurses

CFLAGS	+= -W -Wall -pedantic -Wextra -std=c89 -Werror

SRCS	:= main.c \
	   my.c \
	   get_tetri.c

OBJS	:= $(SRCS:.c=.o)

NAME	:= tetris

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all re clean fclean
