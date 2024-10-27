# Название исполняемого файла по умолчанию
TARGET = test

# Компилятор и флаги по умолчанию
CC = gcc
CFLAGS = -std=c11
INCLUDES = -lm

# Настройки INCLUDES
gl_render: INCLUDES += -lGL -lGLU -lglut
wn_render: INCLUDES += -lgdi32


# Правило по умолчанию (компиляция и запуск программы)
all: $(TARGET)
	./$(TARGET).out

# Правило для компиляции исходного файла
$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET).out $(TARGET).c $(INCLUDES)

# Только запуск для уже скомпилированного целевого файла
run:
	./$(TARGET).out

# Настройка INCLUDES
gl_render: $(TARGET)
wn_render: $(TARGET)

# Очистка скомпилированных файлов
clean:
	rm -f $(TARGET).out

# Фиктивная цель для предотвращения конфликта с файлами заданных имён
.PHONY: all clean render