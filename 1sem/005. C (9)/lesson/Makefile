# Название исполняемого файла
TARGET = main

# Компилятор и флаги
CC = gcc
CFLAGS = -std=c11

# Правило по умолчанию (компиляция и запуск программы)
all: $(TARGET)
	./$(TARGET).out

# Правило для компиляции исходного файла
$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET).out main.c

# Очистка скомпилированных файлов
clean:
	rm -f $(TARGET).out

# Фиктивная цель для предотвращения конфликта с файлами
.PHONY: all clean