CC = g++
CFLAGS = -g -Wall -std=c++11
TARGET = P1

all: $(TARGET)

$(TARGET): main.o added.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o added.o

main.o: main.cpp defs.h timer.h added.h
	$(CC) $(CFLAGS) -c main.cpp

added.o: added.cpp added.h
	$(CC) $(CFLAGS) -c added.cpp

clean:
	rm -f *.o $(TARGET)

