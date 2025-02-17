NAME = gnl.a

SOURCES = get_next_line.c get_next_line_utils.c get_next_line_internals.c

SOURCESALL = $(SOURCES)

OBJECTS = $(SOURCES:.c=.o)

OBJECTSALL = $(SOURCESALL:.c=.o)
CC = cc
CFLAGS = -Wall -Werror -Wextra

%.o : %.c
		@$(CC) $(CFLAGS) -o $@ -c $<

all: $(NAME)

$(NAME): $(OBJECTSALL)
		@ar rcs $(NAME) $(OBJECTSALL)

clean:
		@rm -f $(OBJECTSALL)

fclean: clean
		@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
