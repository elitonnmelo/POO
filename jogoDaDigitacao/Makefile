TARGET = solver

# Compilador que será utilizado
CC = g++

# Opções de compilação
CFLAGS = -std=c++17 -Wall -Wextra -Werror

# Bibliotecas a serem vinculadas
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Arquivo fonte do seu programa
SOURCE = solver.cpp

# Regra para a compilação do programa
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) $(LIBS) -o $(TARGET)

# Regra para limpar o arquivo executável
clean:
	rm -f $(TARGET)
