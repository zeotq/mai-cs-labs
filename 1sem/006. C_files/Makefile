# Название исполняемого файла по умолчанию
TARGET = low_letter_words_max

# Компилятор и флаги по умолчанию
CC = gcc
CFLAGS = -std=c11
INCLUDES = -lm

IN_F = sample_input.txt
OUT_F = sample_result.txt
ARGW = $(IN_F) $(OUT_F)

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