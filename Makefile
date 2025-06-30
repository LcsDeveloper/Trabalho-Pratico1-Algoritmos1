INCLUDE = ./include
SRC = ./src
OBJ = ./obj
BIN = ./bin
CXX = g++
EXEC = tp1

FLAGS = -Wall -Wextra -Wpedantic -Wformat-security -Wconversion -Werror -lm

all: compile

compile:\
	$(OBJ)/graph.o \
	$(OBJ)/node.o
	$(CXX) $(SRC)/main.cpp  $(OBJ)/* $(FLAGS) -I $(INCLUDE) -o $(BIN)/$(EXEC)

$(OBJ)/%.o: $(SRC)/%.cpp $(INCLUDE)/%.hpp
	$(CXX) -c $< $(FLAGS) -I $(INCLUDE) -o $@

clean:
	rm -rf $(BIN)/* $(OBJ)/*

run:
	$(BIN)/$(EXEC)

