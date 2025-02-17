NAME = libft.a

SOURCES = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c \
		ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c \
		ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c \
		ft_substr.c ft_strjoin.c ft_putchar_fd.c ft_putendl_fd.c ft_putstr_fd.c ft_putnbr_fd.c \
		ft_itoa.c ft_strmapi.c ft_striteri.c ft_strtrim.c ft_split.c free_2d.c

SOURCESALL = $(SOURCES)

OBJECTS = $(SOURCES:.c=.o)

OBJECTSALL = $(SOURCESALL:.c=.o)
CC = cc
CFLAGS = -Wall -Werror -Wextra -g

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
