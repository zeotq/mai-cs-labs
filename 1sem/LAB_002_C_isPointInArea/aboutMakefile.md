## UNIX: Make (Makefile)
#### Способ автоматизации выполнения последовательности команд
|||
|-|-|
|$__make__ | из Makefile выполняет цель all|
|$__make__ task| из Makefile выполняет цель task|
|$__make__ -f task| из task выполняет цель all|

#### __Цели__
|Название|Суть|
|-|-|
|all|Цель вызываемая по умолчанию|
|all: task|Перед выполнением all должна быть выполнена task|
|task|Отдельно обозначенная цель|

В терминале UNIX после вызова __make__ можно передать конкретную задачу из __Makefile__. Только она будет выполнена (с учетом условий).

---

#### Компиляция и запуск кода, написанного на языке C
```
all:
	gcc -std=c11 main.c -o main.out
	./main.out
```
#### Разделение команд
```
all: clear build run

delete:
	rm -f main.out

build: delete
	gcc -std=c11 main.c -o main.out
	
run:
	./main.out
	
clear:
	clear
```
#### Продвинутый вариант

```
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
```