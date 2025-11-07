# define the compiler:
CC = g++

# define the compiler flags:
CFLAGS = -g -Wall -std=c++17

# the build target:
TARGET = dessert

# define the source files:
SOURCES = dessert.h dessert.cpp error.h error.cpp rand.h 234node.h 234node.cpp 234Tree.h 234Tree.cpp main.cpp

# define text file:
TEXTFILE = toppings_fillings.txt

# define object files:
OBJECTS = $(SOURCES:.cpp=.o) # turn .cpp files into .o files

# define the target to build:
all: $(TARGET)

# rule to build the target:
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# rule for building object files:
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# rule for running with text file dependency:
run: $(TARGET) $(TEXTFILE)
	./$(TARGET) $(TEXTFILE)

# rule to clean the target and object files:
clean:
	rm -f $(TARGET) $(OBJECTS)
