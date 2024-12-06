## Введение в C (Официально ЛР №2)

### Команда компиляции кода C стандарта 2011 года 
gcc -std=c11 main.c -o test.out

### #include <stdio.h>
Станлартная бибилиотека языка c

### Как работает компилятор?
gcc:
.c -> .o -> .out (линковка .o файлов)

.o - таблица имён / значений <br>
.h - только имена без кода

#include <> - системный заголовочный файл <br>
#include "" - пользовательский заголовочный файл

### Типы данных языка C

|Тип|Размер|Память|Обозначение|
|---|---|---|---|
|int|[-2^31; 2^31 - 1]|4 bites|%d| 
|unsigned int|[0; 2^32 - 1]|4 bites|%d|
|long int|[-2^63; 2^63 - 1]|8 bites|%d|
|unsigned long int|[0; 2^64 - 1] |8 bites|%d|
|long long int|[-2^63; 2^63 - 1]|8 bites|%d|
|float| |4 bites|%f|
|double| |8 bites|%f|

### Операции с разнотиповыми операндами

double / int -> double (int приводится к типу первого операнда)