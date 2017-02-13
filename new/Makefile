#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbelazou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/07 20:16:27 by sbelazou          #+#    #+#              #
#    Updated: 2017/02/08 18:42:33 by sbelazou         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		=	ft_ls
DIRSRC		=	./srcs/
DIROBJ		=	./objs/
INC_LIB		=	./includes/libft/libft.a
SRC			=	main.c ft_ls.c sort_result.c lsl_ft.c recurs.c

OBJ			=	$(SRC:.c=.o)
OBJS		=	$(OBJ:%=$(DIROBJ)%)
FLAGS		=

ifdef FLAGS
	ifeq ($(FLAGS), yes)
CFLAGS		=	-Wall -Wextra -Werror
	endif
	ifeq ($(FLAGS), debug)
CFLAGS		=	-Wall -Wextra -Werror -ansi -pedantic -g
	endif
	else
CFLAGS		=
endif

CC			=	/usr/bin/gcc
RM			=	/bin/rm -f
ECHO		=	echo


$(NAME)	:		$(OBJ)
				-@$(CC) $(INC_LIB) $(CFLAGS) -o $(NAME) $(OBJS)
				@$(ECHO) "\033[32mAll sources are compiled."
				@$(ECHO) "$(NAME) has been created.\033[0m"

clean	:
				@(cd $(DIROBJ) && $(RM) $(OBJ))
				@$(ECHO) "\033[31mObjects are removed.\033[0m"

all		:		$(NAME)

fclean	:		clean
				-@$(RM) $(NAME)
				@$(ECHO) "\033[31m$(NAME) has been removed.\033[0m"

re		:		fclean all

zen		:		clean
				-@find . \( -name "*~" -o -name "#*#" \) -delete
				@$(ECHO) "\033[31mBack-up files are removed.\033[0m"

.PHONY	:		all clean fclean re

%.o		:		$(DIRSRC)/%.c
				$(CC) $(CFLAGS) -o $(DIROBJ)/$@ -c $<
