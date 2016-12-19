##
## Makefile for  in /home/ravenous/42/ft_ls
## 
## Made by Sofiane Belazouz
## 
## Started on  Fri Dec 16 19:35:10 2016 Sofiane Belazouz
## Last update Mon Dec 19 19:26:10 2016 Sofiane Belazouz
##

SRC = main.c\
	options.c

OBJ = $(SRC:.c=.o)

NAME = ft_ls

LIB = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) $(LIB)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
