CXX = g++
CXXFLAGS = -Wall -g -std=c++11
TARGET = main_rational_t
OBJECTS = rational_t.o main_rational_t.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp rational_t.hpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(TARGET) $(OBJECTS)
