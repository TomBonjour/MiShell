# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tobourge <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/07 21:03:24 by tobourge          #+#    #+#              #
#    Updated: 2025/03/03 20:07:24 by tobourge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a
CC	=	gcc
CFLAGS	+=	-Wall -Werror -Wextra -I include

SRCS	=	ft_isalpha.c ft_isalnum.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_strlcpy.c ft_memmove.c ft_tolower.c ft_toupper.c ft_atoi.c ft_strrchr.c ft_strchr.c ft_strncmp.c ft_strnstr.c ft_memchr.c ft_memcpy.c ft_memcmp.c ft_strdup.c ft_calloc.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strlcat.c

BONUS	=	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJS	=	$(SRCS:.c=.o)

OBONUS	=	$(BONUS:.c=.o)
	
all	:	$(NAME)

%.o : %.c
		@$(CC) $(CFLAGS) -fPIC -c $< -o $@

$(NAME)	:	$(OBJS)
	@ar -rcs $(NAME) $(OBJS)


bonus : $(OBJS) $(OBONUS)
	@ar -rcs $(NAME) $(OBJS) $(OBONUS)

so:
	@$(CC) -fPIC $(CFLAGS) $(SRCS)
	@gcc -shared -o libft.so $(OBJS) $(OBONUS)

clean	:
	@rm -f $(OBJS) $(OBONUS)

fclean	:	clean
	@rm -f ${NAME}

re	:	fclean all

.PHONY	:	clean fclean re so bonus
