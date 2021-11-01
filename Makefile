CXX		  := g++
CXX_FLAGS := -std=c++17 -Wall -Wextra -Werror -Wshadow -Wconversion -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused -Wnull-dereference -Wfloat-equal -Wduplicated-branches


BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib
EXT = .cpp
FONTES = $(wildcard $(SRC)/*$(EXT))

LIBRARIES	:= -lsfml-graphics -lsfml-window -lsfml-system
EXECUTABLE	:= main.bin


all: build run clean

valgrind: build runValgrind clean

build:
	$(CXX) $(CXX_FLAGS) $(FONTES) -I$(INCLUDE) -L$(LIB) $(LIBRARIES) -o ./${BIN}/$(EXECUTABLE)

run:./$(BIN)/$(EXECUTABLE)
	./$(BIN)/$(EXECUTABLE)

runValgrind: ./$(BIN)/$(EXECUTABLE)
	valgrind --leak-check=yes ./$(BIN)/$(EXECUTABLE)

clean:
	-rm $(BIN)/*
