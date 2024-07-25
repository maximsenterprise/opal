CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -pedantic -std=c++11 -O3 -I include

SRC = src
BIN = bin
OBJ = obj

CXXSRCS = $(shell find $(SRC) -name "*.cpp")
CXXOBJS = $(patsubst $(SRC)/%, $(OBJ)/%, $(CXXSRCS:.cpp=.o))
EXECUTABLE = ./bin/opal

.PHONY: all clean run recompile

all: $(EXECUTABLE)

recompile: clean all

$(EXECUTABLE): $(CXXOBJS)
	$(CXX) $(CXXFLAGS) -o $(BIN)/opal $^
	@echo "Compilation successful!"

$(OBJ)/%.o: $(SRC)/%.cpp
	mkdir -p $(@D) # Create the directory if it doesn't exist
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(EXECUTABLE)
	rm -rf $(OBJ)
	mkdir -p $(OBJ)

run: $(EXECUTABLE)
	@$(EXECUTABLE)
