# the compiler
CC=gcc

# compiler flags:
CFLAGS= -Os -O3

# target executable:
TARGET = exificient-for-json.exe

all: $(TARGET)

$(TARGET):
	$(CC) src/*.c $(CFLAGS) -o $(TARGET)

.PHONY: clean

clean:
	$(RM) $(TARGET)

