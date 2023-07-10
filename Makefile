CC = g++
CFLAGS = -std=c++11 -Wall

#target: name of exec
TARGET = LinkedListTest
#srcs: source files
SRCS = LinkedList.cpp LinkedListTest.cpp

#phony: to avoid name conflict
.PHONY: all clean

all: $(TARGET)

#$^: list of dependencies for the target
#$@: name of the target
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)