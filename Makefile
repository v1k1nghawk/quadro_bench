CC = gcc
CFLAGS = -Wall -O3
LIBS = -lm
SOURCE = quadro_bench.c
TARGET = quadro_bench
RM = rm -f

all:	$(TARGET)

$(TARGET):	$(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE) $(LIBS)

clean:
	$(RM) $(TARGET)

