# the compiler: gcc for C program, define as g++ for C++
cc = gcc

# compiler flags:
#  -g     - this flag adds debugging information to the executable file
#  -Wall  - this flag is used to turn on most compiler warnings
TARGET = parse
CFLAGS = -g -Wall

make: *.c
	$(cc) -c *.c $(CFLAGS)
	$(cc) -o $(TARGET) *.o


run: make
	./$(TARGET)

clean:
	del *.o $(TARGET)

