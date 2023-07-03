# Nome do arquivo executável
TARGET = solver

# Comando de compilação
CC = g++
CFLAGS = -std=c++11 -Wall

# Lista de arquivos-fonte
SRC = solver.cpp 

all: main
# Regra para compilar o executável
main: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# Regra para limpar os arquivos objeto e o executável
clean:
	rm -f $(OBJS) $(TARGET)

# Regra para executar o programa
run: $(TARGET)
	./$(TARGET)
