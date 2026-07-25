CC = gcc
CFLAGS = -Wall -Wextra -Werror -O2 -std=c11
LDFLAGS = -lm

BUILD = ../build
TARGET = $(BUILD)/graph

SRC = src/graph.c src/lexer_and_check.c src/shunting_yard.c src/stack.c src/rpn.c
HDR = src/graph.h src/shunting_yard.h src/lexer_and_check.h src/token.h src/stack.h src/rpn.h

all: $(TARGET)

$(TARGET): $(SRC) $(HDR)
	mkdir -p $(BUILD)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -rf $(BUILD)

rebuild: clean all

.PHONY: all clean rebuild
