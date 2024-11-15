# Название исполняемого файла по умолчанию
TARGET = main

# Компилятор и флаги по умолчанию
CC = gcc
CFLAGS = -std=c11
INCLUDES = -lm

# Правило по умолчанию (компиляция и запуск программы)
all: $(TARGET)
	./$(TARGET).out $(ARGW)

# Правило для компиляции исходного файла
$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET).out $(TARGET).c $(INCLUDES)

run:
	./$(TARGET).out $(ARGW)

clean:
	rm -f $(TARGET).out

.PHONY: all clean render