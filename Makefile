# Set compiler to clang++
CXX = clang++
# Set linker to clang++
LD = clang++

output_msg: ; $(CLANG_VERSION_MSG)

# Set compiler flags to standard for course
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -Werror -pedantic
# Set linker flags to standard for course
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi

# Link final project
main : ./build/AirGraph.o ./build/file_parser.o ./build/main.o ./build/graph.o ./build/random.o
	$(LD) ./build/main.o ./build/AirGraph.o ./build/graph.o ./build/random.o ./build/file_parser.o $(LDFLAGS) -o $@

# Compile final project
./build/main.o : ./main.cpp ./AirGraph/AirGraph.h ./parsing/file_parser.h
	$(CXX) $(CXXFLAGS) $< -o $@

# Link tests
test: ./build/tests.o ./build/catchmain.o
	$(LD) ./build/catchmain.o ./build/tests.o $(LDFLAGS) -o test

# Compile tests
 ./build/tests.o : ./tests/tests.cpp ./AirGraph/AirGraph.h ./parsing/file_parser.h
	$(CXX) $(CXXFLAGS) $< -o $@

# Compile catch test suite
./build/catchmain.o : ./cs225/catch/catchmain.cpp ./cs225/catch/catch.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Compile AirGraph
./build/AirGraph.o : ./AirGraph/AirGraph.cpp ./AirGraph/AirGraph.h ./graph/graph.h
	$(CXX) $(CXXFLAGS) $< -o $@

# Compile Graph (required by AirGraph)
./build/graph.o : ./graph/graph.cpp ./graph/graph.h ./graph/edge.h ./graph/random.h
	$(CXX) $(CXXFLAGS) $< -o $@

# Compile random (required by Graph)
./build/random.o : ./graph/random.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Compile file_parser
./build/file_parser.o : ./parsing/file_parser.cpp ./parsing/file_parser.h
	$(CXX) $(CXXFLAGS) $< -o $@

# Clean all build artifacts
clean : 
	rm ./build/*