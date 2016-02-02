# Declaration of variables
CC = g++
CC_FLAGS = -w

# File names
EXEC = Deque
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
TAR_FILE = cs540p1_wu_victor.tar.gz

# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

dist:
	tar -cvzf $(TAR_FILE) $(SOURCES)

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)
