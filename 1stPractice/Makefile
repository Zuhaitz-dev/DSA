CXX = g++
CXXFLAGS = -Wall -g -std=c++11
TARGET = main_rational_t
OBJECTS = rational_t.o main_rational_t.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

rational_t.o: rational_t.cpp rational_t.hpp
	$(CXX) $(CXXFLAGS) -c rational_t.cpp

main_rational_t.o: main_rational_t.cpp rational_t.hpp
	$(CXX) $(CXXFLAGS) -c main_rational_t.cpp

clean:
	rm -f $(TARGET) $(OBJECTS)