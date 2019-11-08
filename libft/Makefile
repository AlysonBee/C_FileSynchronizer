# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: angonyam <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/24 09:13:04 by angonyam          #+#    #+#              #
#    Updated: 2017/07/17 13:23:46 by angonyam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJ = ft_atoi.o ft_bzero.o ft_isalnum.o ft_isalpha.o ft_isascii.o \
     ft_isdigit.o ft_isprint.o ft_memccpy.o ft_memchr.o ft_memcmp.o \
     ft_memcpy.o ft_memmove.o ft_memset.o ft_strcat.o ft_strchr.o \
     ft_strcmp.o ft_strcpy.o ft_strdup.o ft_strlcat.o ft_strlen.o \
     ft_strncat.o ft_strncmp.o ft_strncpy.o ft_strnstr.o ft_strrchr.o \
     ft_strstr.o ft_tolower.o ft_toupper.o ft_memalloc.o ft_memdel.o \
     ft_strnew.o ft_strdel.o ft_strclr.o ft_striter.o ft_striteri.o \
     ft_strmap.o ft_strmapi.o ft_strequ.o ft_strnequ.o ft_strsub.o \
     ft_strjoin.o ft_strtrim.o ft_strsplit.o ft_itoa.o ft_putchar.o \
     ft_putstr.o ft_putendl.o ft_putnbr.o ft_putchar_fd.o ft_putstr_fd.o \
     ft_putendl_fd.o ft_putnbr_fd.o ft_lstadd.o ft_lstnew.o \
     ft_lstdelone.o ft_lstmap.o

CFILES=$(OBJ:.o=.c)

NAME=libft.a

HDDR=-I includes/

$(NAME):
	gcc -Wall -Werror -Wextra -c $(CFILES) -I includes/
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(OBJ) $(NAME)

re: fclean all
