# Nome do executável
TARGET = TED

# Nome do aluno
ALUNO = LuanaUeno

# Compilador
CC = gcc

# Flags
CFLAGS = -std=c99 -Wall -Wextra -g -O0

# Diretórios
SRC_DIR = .
BUILD_DIR = build

# Bibliotecas
LIBS = -lm

# Lista de arquivos .c em src/
SRCS = $(wildcard *.c)

# Arquivos objeto dentro de build/
OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))

# --------------------------------
# Regras
# --------------------------------

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(TARGET)

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

rebuild: clean all
