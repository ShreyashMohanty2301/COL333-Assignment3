# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall

# Targets
TARGETS = maincode generate_output

# Source and object files for each target
MAIN_SRC = maincode.cpp encode.cpp inputoutput.cpp utils.cpp
MAIN_OBJ = $(MAIN_SRC:.cpp=.o)

GEN_SRC = generate_output.cpp encode.cpp inputoutput.cpp utils.cpp
GEN_OBJ = $(GEN_SRC:.cpp=.o)

# Default rule
all: $(TARGETS)

# Build rules
maincode: $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(MAIN_OBJ)

generate_output: $(GEN_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(GEN_OBJ)

# Individual object rules with dependencies
maincode.o: maincode.cpp encode.h inputoutput.h input.h utils.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

encode.o: encode.cpp encode.h utils.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

inputoutput.o: inputoutput.cpp inputoutput.h input.h utils.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

utils.o: utils.cpp utils.h encode.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

generate_output.o: generate_output.cpp inputoutput.h input.h utils.h encode.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cleanup
clean:
	rm -f *.o $(TARGETS)

# Convenience rules
run_main: maincode
	./maincode

run_output: generate_output
	./generate_output