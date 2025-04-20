# Nombre del ejecutable
EXEC = tarea2

# Compilador
CC = gcc

# Opciones de compilación
CFLAGS = -Wall -Wextra -std=c99 -I./modules

# Archivos fuente
SRCS = main.c \
       modules/processor.c \
       modules/validator.c

# Archivos objeto (los .o generados)
OBJS = $(SRCS:.c=.o)

# Regla por defecto
all: $(EXEC)

# Regla para compilar el ejecutable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Limpieza de archivos temporales
clean:
	rm -f $(EXEC) $(OBJS)

# Compila sin ejecutar
compile:
	$(CC) $(CFLAGS) -c $(SRCS)

.PHONY: all clean compile
