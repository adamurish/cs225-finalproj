# Set compiler to clang++
CXX = clang++
# Set linker to clang++
LD = clang++

ALL_NON_EXE_OBJS = ./build/AirGraph.o ./build/file_parser.o ./build/graph.o ./build/PNG.o ./build/HSLAPixel.o ./build/lodepng.o


# Set compiler flags to standard for course
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -Werror -pedantic
# Set linker flags to standard for course
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi

# Link final project
main : $(ALL_NON_EXE_OBJS) ./build/main.o
	$(LD) ./build/main.o ./build/AirGraph.o ./build/graph.o ./build/file_parser.o $(LDFLAGS) -o $@

# Link tests
test: $(ALL_NON_EXE_OBJS) ./build/tests.o ./build/catchmain.o
	$(LD) ./build/catchmain.o ./build/tests.o $(LDFLAGS) -o test

# Compile final project
./build/main.o : ./main.cpp ./AirGraph/AirGraph.h ./parsing/file_parser.h
	$(CXX) $(CXXFLAGS) $< -o $@

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
./build/graph.o : ./graph/graph.cpp ./graph/graph.h ./graph/edge.h ./graph/random.h ./graph/random.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Compile file_parser
./build/file_parser.o : ./parsing/file_parser.cpp ./parsing/file_parser.h 
	$(CXX) $(CXXFLAGS) $< -o $@

# Compile PNG
./build/PNG.o : ./cs225/PNG.cpp ./cs225/PNG.h ./cs225/HSLAPixel.h ./cs225/RGB_HSL.h 
	$(CXX) $(CXXFLAGS) $< -o $@

# Compile HSLAPixel
./build/HSLAPixel.o : ./cs225/HSLAPixel.cpp ./cs225/HSLAPixel.h
	$(CXX) $(CXXFLAGS) $< -o $@

# Compile lodepng
./build/lodepng.o : ./cs225/lodepng/lodepng.cpp ./cs225/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) $< -o $@

# Clean all build artifacts
clean : 
	rm -f ./build/* ./main ./test