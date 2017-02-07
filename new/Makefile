#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbelazou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/07 20:16:27 by sbelazou          #+#    #+#              #
#    Updated: 2017/02/07 20:34:55 by sbelazou         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		=	ft_ls
DIRSRC		=	./srcs/
DIROBJ		=	./objs/
INC_LIB		=	./includes/libft/libft.a
SRC			=	main.c

OBJ			=	$(SRC:.c=.o)
OBJS		=	$(OBJ:%=$(DIROBJ)%)
FLAGS		=	yes

ifdef FLAGS
	ifeq ($(FLAGS), no)
CFLAGS		=
	endif
	ifeq ($(FLAGS), debug)
CFLAGS		=	-Wall -Wextra -Werror -ansi -pedantic -g
	endif
else
CFLAGS		=	-Wall -Wextra -Werror
endif

CC			=	/usr/bin/gcc
RM			=	/bin/rm -f
ECHO		=	/bin/echo -e


$(NAME)	:		$(OBJ)
				$(CC) $(INC_LIB) $(CFLAGS) -o $(NAME) $(OBJS)
				@$(ECHO) '> Compiled'

clean	:
				@(cd $(DIROBJ) && $(RM) $(OBJ))
				@$(ECHO) '> Directory cleaned'

all		:		$(NAME)

fclean	:		clean
				-@$(RM) $(NAME)
				@$(ECHO) '> Remove executable'

re		:		fclean all

zen		:		clean
				find . \( -name "*~" -o -name "#*#" \) -delete

.PHONY	:		all clean fclean re

%.o		:		$(DIRSRC)/%.c
				$(CC) $(CFLAGS) -o $(DIROBJ)/$@ -c $<
