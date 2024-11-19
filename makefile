
CC = gcc

CFLAGS = -Wall -Wextra -pthread -g -Iinclude

EXE = race

SRC= src
INCLUDE = include
BUILD = build

# Arquivos fonte e objetos
SRCS = $(wildcard $(SRC)/*.c)
OBJS = $(SRCS:$(SRC)/%.c=$(BUILD)/%.o)


all: $(EXE)

# Regra para criar o executável
$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS)

# Regra para compilar os objetos
$(BUILD)/%.o: $(SRC)/%.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para criar o diretório de build
$(BUILD):
	mkdir -p $(BUILD)

# Regra de limpeza
clean:
	rm -rf $(BUILD) $(TARGET)