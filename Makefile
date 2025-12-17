NAME = analyzer.exe
SRC = main.cpp src/Controller.cpp src/OutFile.cpp src/GraphLoader.cpp
OBJ = $(SRC:.cpp=.o)
CC = g++
SFML_PATH = lib/SFML
CFLAGS = -Wall -Wextra -Iincludes -I$(SFML_PATH)/include -DSFML_STATIC
LDFLAGS = -L$(SFML_PATH)/lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lstdc++

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /Q *.o src\*.o 2>nul || true

fclean: clean
	del /Q $(NAME) 2>nul || true

re: fclean all

.PHONY: all clean fclean re
