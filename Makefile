##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## a Makefile that compile my libmy.
##

SRC = sfml.cpp  \

OBJ = 	$(subst .cpp,.o,$(SRC))

NAME =	arcade

all : $(NAME)

$(NAME) : $(OBJ)
	g++ -o $(NAME) $(OBJ) -g3 -lsfml-graphics -lsfml-window -lsfml-system -lncurses

clean :
	find . -type f \( -name "#*#" -o -name "*~" -o -name "*.o" \) -delete

fclean : clean
	rm -f $(NAME) a.out $(autre) unit_tests

re : fclean all
