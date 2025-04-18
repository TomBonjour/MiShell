NAME = dprintf.a

MY_SOURCES = ft_dprintf.c \
			 ft_dhexa.c \
			 ft_dputchar.c \
			 ft_dputnbr.c \
			 ft_dputptr.c \
			 ft_dputstr.c \
			 ft_dusint.c

AR = ar -rcs
CC = gcc
CFLAGS += -Wall -Wextra -Werror -I include

OBJECTS = $(MY_SOURCES:.c=.o)

all: $(NAME)

%.o : %.c
		@$(CC) $(CFLAGS) -g -fPIC -c $< -o $@

$(NAME): $(OBJECTS)
	$(AR) $(NAME) $(OBJECTS) -o $(NAME)

so:
	@$(CC) -fPIC $(CFLAGS) $(MY_SOURCES)
	@gcc -shared -o dprintf.so $(OBJECTS)

clean:
	rm -f $(OBJECTS)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re so
