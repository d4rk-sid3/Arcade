##
## EPITECH PROJECT, 2025
## B-OOP-400-COT-4-1-arcade-amour.guidi
## File description:
## Makefile
##

NAME = arcade

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I. -I./LibDisplay/SFML -I./LibDisplay/SDL -I./LibDisplay/NCURSES -I./LibGames/Snake -I./LibGames/Nibbler -I./Games/Nibbler -I./Games/Snake -I/usr/include/SDL2

LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lncurses -lSDL2 -lSDL2_image

SRC = main.cpp \
      GameElement.cpp \
      LibDisplay/SFML/sfml.cpp \
      LibDisplay/SDL/sdl.cpp \
      LibDisplay/NCURSES/Ncures.cpp \
      LibGames/Snake/Snake.cpp \
      LibGames/Nibbler/nibbler.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(OBJ) -o $(NAME) $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
