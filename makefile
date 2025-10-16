CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall

# List all .cpp source files here
SRC = maincode.cpp encode.cpp inputoutput.cpp utils.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = maincode

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)