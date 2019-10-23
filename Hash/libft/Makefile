# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsferopo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/20 12:06:34 by gsferopo          #+#    #+#              #
#    Updated: 2017/12/07 14:39:23 by gsferopo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		=	$(shell ls | grep '\.c')

OBJ		=	${SRC:%.c=%.o}

OBJPATH	=	./objs/

OBJS	=	$(addprefix $(OBJPATH), $(OBJ))

CFLAGS	= 	-Werror -Wextra -Wall

LIB		=	libft.h

NAME	=	libft.a

all: mk $(NAME) Makefile

mk:
	@if [ -d objs ]; then echo "---NTBD---"; else mkdir objs; fi;

$(OBJPATH)%.o: %.c
	@echo "---UPDATING $<---"
	@gcc $(CFLAGS) -c $<
	@mv *.o objs

$(NAME): $(OBJS)
	@echo "\033[0;31m---COMPILING LIBRARY---"
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

clean:
	@echo "\033[0;34m---REMOVING  OBJECTS---"
	@rm -rf $(OBJS)

fclean: clean
	@echo "\033[0;35m---REMOVING  LIBRARY---"
	@rm -rf $(NAME)

re: fclean all

push:
	if [ -d ./libft ] ; then rm -rf libft ; fi;
	git clone https://github.com/Heagan/libft.git
	mv -f libft/.git ./
	rm -rf libft
	git add -A
	git commit -m "Libft Update"
	git push
	rm -rf .git

cp:
	@echo "\033[0;36m---COPYING LIBRARY---"
	@cp $(NAME) ../
