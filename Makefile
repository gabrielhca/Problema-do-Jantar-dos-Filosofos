CC = gcc
CFLAGS = -Wall -pthread

TARGET = jantar_filosofos

all: $(TARGET)

$(TARGET): jantar_filosofos.c 
	$(CC) $(CFLAGS) jantar_filosofos.c -o $(TARGET)

clean:
	rm -f $(TARGET)
