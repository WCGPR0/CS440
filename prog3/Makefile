CC=g++
CFLAGS=-std=c++11
SOURCES := SharedPtr_test.cpp
# Objs are all the sources, with .cpp replaced by .o
OBJS := $(SOURCES:.cpp=.o)

all: t

 # Compile the binary 't' by calling the compiler with cflags, lflags, and any libs (if defined) and the list of objects.
t: $(OBJS)
	$(CC) $(CFLAGS) -o t $(OBJS) $(LFLAGS) $(LIBS)

     # Get a .o from a .cpp by calling compiler with cflags and includes (if defined)
.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<
