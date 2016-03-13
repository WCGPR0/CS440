CC = g++ 
CFLAGS = -g -Wall -std=c++0x -fmax-errors=5 -w

TARGET = Driver
TARGET2 = test



all: $(TARGET2)

custom: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp

$(TARGET2): $(TARGET2).cpp
	$(CC) $(CFLAGS) -o $(TARGET2) $(TARGET2).cpp

clean:
	$(RM) $(TARGET) *.o
