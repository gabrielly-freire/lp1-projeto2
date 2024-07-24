CXX = g++
CXXFLAGS = -Iinclude -std=c++11
SRC = $(wildcard src/**/*.cpp) Main.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ -lmysqlclient

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
