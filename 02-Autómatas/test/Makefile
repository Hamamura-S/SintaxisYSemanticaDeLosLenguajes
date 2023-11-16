# rm ES UN COMANDO PARA LINUX, NO FUNCIONARA EN WINDOWS
# EN LINUX rm == del EN WINDOWS

# Archivos fuente
SRC_FILES = test.c unity.c

# Nombre del ejecutable
TARGET = runtest

# Opciones de compilación
CFLAGS = -Wall

# Regla para la compilación
$(TARGET): $(SRC_FILES)
	gcc $(CFLAGS) -o $(TARGET) $(SRC_FILES)

# Regla para limpiar archivos generados
clean:
	rm -f $(TARGET)

# Regla para compilar, ejecutar y luego eliminar el binario
test:
	gcc $(CFLAGS) -o $(TARGET) $(SRC_FILES)
	$(TARGET)
	rm -f $(TARGET)
