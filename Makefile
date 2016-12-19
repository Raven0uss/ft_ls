##
## Makefile for  in /home/ravenous/42/ft_ls
## 
## Made by Sofiane Belazouz
## 
## Started on  Fri Dec 16 19:35:10 2016 Sofiane Belazouz
## Last update Fri Dec 16 19:39:43 2016 Sofiane Belazouz
##

SRC = main.c

OBJ = $(SRC:.c=.o)

NAME = ft_ls

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
