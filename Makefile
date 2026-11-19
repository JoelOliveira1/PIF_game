# Makefile - Paranoia (C + Raylib)
#
# Uso:
#   make       -> compila o jogo
#   make run   -> compila e executa
#   make clean -> apaga o executavel

CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -Iinclude
LDFLAGS = -lraylib -lm

SRC     = $(wildcard src/*.c)
TARGET  = jogo
RM      = rm -f
RUN     = ./$(TARGET)

ifeq ($(OS),Windows_NT)
    LDFLAGS += -lopengl32 -lgdi32 -lwinmm
    TARGET  = jogo.exe
    ifeq ($(findstring sh,$(SHELL)),)
        RM  = del /Q
        RUN = $(TARGET)
    endif
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
        BREW_PREFIX := $(shell brew --prefix 2>/dev/null || echo /usr/local)
        CFLAGS  += -I$(BREW_PREFIX)/include
        LDFLAGS := -L$(BREW_PREFIX)/lib $(LDFLAGS) -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
    else
        LDFLAGS += -lGL -lpthread -ldl -lrt -lX11
    endif
endif

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

run: $(TARGET)
	$(RUN)

clean:
	$(RM) $(TARGET)

.PHONY: all run clean