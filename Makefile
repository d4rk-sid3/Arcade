##
## EPITECH PROJECT, 2025
## B-OOP-400-COT-4-1-arcade-amour.guidi
## File description:
## Makefile
##

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I. -I./LibDisplay/SFML -I./LibDisplay/SDL -I./LibDisplay/NCURSES -I./LibGames/Snake -I./LibGames/Nibbler -I./Games/Nibbler -I./Games/Snake -I/usr/include/SDL2

SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system
NCURSES_FLAGS = -lncurses
SDL_FLAGS = -lSDL2 -lSDL2_image


LIB_SDL = arcade_sdl.so
LIB_SFML = arcade_sfml.so
LIB_NCURSES = arcade_ncurses.so
LIB_SNAKE = arcade_snake.so
LIB_NIBBLER = arcade_nibbler.so
CORE = arcade

SRC_CORE =        		main.cpp \
                  		GameElement.cpp

SRC_SFML =        		LibDisplay/SFML/sfml.cpp
SRC_SDL =         		LibDisplay/SDL/sdl.cpp
SRC_NCURSES =     		LibDisplay/NCURSES/Ncures.cpp
SRC_SNAKE =        		LibGames/Snake/Snake.cpp
SRC_NIBBLER =         	LibGames/Nibbler/nibbler.cpp

OBJ_SDL = $(SRC_SDL:.cpp=.o)
OBJ_SFML = $(SRC_SFML:.cpp=.o)
OBJ_NCURSES = $(SRC_NCURSES:.cpp=.o)
OBJ_SNAKE = $(SRC_SNAKE:.cpp=.o)
OBJ_NIBBLER = $(SRC_NIBBLER:.cpp=.o)
OBJ_CORE = $(SRC_CORE:.cpp=.o)

all: games graphicals core

ncurses: $(LIB_NCURSES)

$(LIB_NCURSES): $(OBJ_NCURSES)
	mkdir -p lib
	$(CXX) $(OBJ_NCURSES) -o ./lib/$(LIB_NCURSES) -shared $(NCURSES_FLAGS)

sfml: $(LIB_SFML)

$(LIB_SFML): $(OBJ_SFML)
	mkdir -p lib
	$(CXX) $(OBJ_SFML) -o ./lib/$(LIB_SFML) -shared $(SFML_FLAGS)

sdl: $(LIB_SDL)

$(LIB_SDL): $(OBJ_SDL)
	mkdir -p lib
	$(CXX) $(OBJ_SDL) -o ./lib/$(LIB_SDL) -shared $(SDL_FLAGS)

snake: $(LIB_SNAKE)

$(LIB_SNAKE): $(OBJ_SNAKE)
	mkdir -p lib
	$(CXX) $(OBJ_SNAKE) -o ./lib/$(LIB_SNAKE) -shared

nibbler: $(LIB_NIBBLER)

$(LIB_NIBBLER): $(OBJ_NIBBLER)
	mkdir -p lib
	$(CXX) $(OBJ_NIBBLER) -o ./lib/$(LIB_NIBBLER) -shared

core: $(CORE)

$(CORE): $(OBJ_CORE)
	$(CXX) $(OBJ_CORE) -o $(CORE)


%.o: %.cpp
	$(CXX) -c -fPIC $< -o $@


games: nibbler snake

graphicals: sfml ncurses sdl

clean:
	rm -f $(OBJ_CORE) $(OBJ_SFML) $(OBJ_SDL) $(OBJ_NCURSES) $(OBJ_SNAKE) $(OBJ_NIBBLER)

fclean: clean
	rm -f ./lib/$(CORE) ./lib/$(LIB_SDL) ./lib/$(LIB_SFML) ./lib/$(LIB_NCURSES) ./lib/$(LIB_SNAKE) ./lib/$(LIB_NIBBLER)

re: fclean all

.PHONY: all core graphicals games sfml ncurses sdl snake nibbler clean fclean re
