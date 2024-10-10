##
## EPITECH PROJECT, 2024
## EpiGimp
## File description:
## Makefile of the project
##

# Main file
MAIN		=	src/Main.cpp
MAIN_OBJ	=	$(MAIN:.cpp=.o)

# Sources
SRC_FILES 	=	Application.cpp \
				WindowManager.cpp \
				MenuBar.cpp \
				Tab.cpp \
				Dock.cpp \
				buttons/AButton.cpp \
				buttons/Button.cpp \
				buttons/DraggableButton.cpp \
				buttons/DropdownButton.cpp \
				ImageField.cpp \
				EventManager.cpp \
				buttons/DropdownManager.cpp \

SRC_DIR 	=	src/
SRC		=	$(addprefix $(SRC_DIR), $(SRC_FILES))
SRC_OBJ	=	$(SRC:.cpp=.o)

OBJ		= $(SRC_OBJ) $(MAIN_OBJ)

# Tests
TEST_FILES 	=	TestExample.cpp

TEST_DIR 	=	tests/
TEST		=	$(addprefix $(TEST_DIR), $(TEST_FILES))
TEST_OBJ	=	$(TEST:.cpp=.o)
TEST_FLAGS	=	--coverage -lcriterion -I./include
TEST_GCDA 	=	$(SRC:.cpp=.gcda)
TEST_GCNO 	=	$(SRC:.cpp=.gcno)

# Binary
NAME 	=	epiGimp

# Flags
IFLAGS 	=	-I./include
CFLAGS 	=	-Wall -Wextra -g `sdl2-config --cflags` -I/usr/include/SDL2
LFLAGS  =   `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lSDL2_image

# Compiler
CC = g++

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(LFLAGS) $(CFLAGS) $(IFLAGS)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

src_obj: $(SRC_OBJ)

tests_run: fclean $(TEST_OBJ)
	@$(MAKE) src_obj CFLAGS+=--coverage
	@$(CC) -o unit_tests $(TEST_OBJ) $(SRC_OBJ) $(TEST_FLAGS)
	./unit_tests
	gcovr --exclude tests/

tests_clean: clean
	@rm -f $(TEST_OBJ)
	@rm -f unit_tests
	@rm -f $(TEST_GCDA)
	@rm -f $(TEST_GCNO)

%.o: %.cpp
	@$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)