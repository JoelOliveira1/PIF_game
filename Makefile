# Makefile - Paranoia (C + Raylib)
#
# Uso:
#   make-> compila o jogo
#   make run -> compila e executa
#   make clean -> apaga o executavel

CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -Iinclude
LDFLAGS = -lraylib -lm

SRC     = $(wildcard src/*.c)
TARGET  = jogo

# Precisa disso pra funcionar no Windows!!!
ifeq ($(OS),Windows_NT)
    LDFLAGS += -lopengl32 -lgdi32 -lwinmm
    TARGET  = jogo.exe
endif

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean