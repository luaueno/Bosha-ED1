# -------------------------------
# Makefile modular com subpastas
# -------------------------------

# Nome do executável
TARGET = simulador

# Nome do aluno (para pack)
ALUNO = LuanaUeno

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -std=c99 -Wall -Wextra -g -O0

# Diretórios
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
LIB_DIR = lib

# Bibliotecas adicionais
LIBS = -lm
LIB_FLAGS = -L$(LIB_DIR)
INC_FLAGS = -I$(INC_DIR)

# Lista de arquivos de origem automaticamente
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Lista de arquivos objeto em build/
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# -------------------------------
# Regras
# -------------------------------

# Criar build se não existir
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compilar todos
all: $(BUILD_DIR) $(TARGET)

# Compilar executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB_FLAGS) $(LIBS) -o $(TARGET)

# Compilar cada objeto
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

# Limpar arquivos intermediários e executável
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Recompilar do zero
rebuild: clean all

# Criar pacote zip do projeto
pack:
	rm -f ../$(ALUNO).zip
	zip -r ../$(ALUNO).zip src include Makefile LEIA-ME.txt

# Falsos alvos
.PHONY: all clean rebuild pack
