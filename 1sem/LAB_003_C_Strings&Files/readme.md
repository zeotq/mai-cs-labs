# Массивы в C

## Stack - стопка (структура хранения данных)
Операции:
- взять сверху
- положить сверху

 ```
int sum(int a, int b){
    int res = a + b;
    return res;
}

int main(){
    sum(5, 2);
    return 0;
}
```

|STACK STRUCTURE|
|-|
res
b
a
memeory for return


```
int main() {
    char name[100]; // Выделяем место в stack'е для массива переменных типа char длиной 100 
}
```

|STACK STRUCTURE (Для массива)|
|-|
name[100]
...
name[1]
name[0]

## Возможные проблемы
```
int main(){
    char str[100];
    str[150] = 'w';
    // Рабоать будет, но у программы будет неопределенное поведение из-за замены значения в неопределнной для программы области памяти/занятой доругой программой памяти.
}
```


## Dynamic

```
int main() {
    char* name = malloc(100);
}
```
<br><br>


# Работа с файлами
## Чтение

```c
*file = fopen("name", mode);
```
|mode|функция
|-|-|
|w|запись
|r|чтение
|a|добавление
|r+|чтение + запись
|a+|чтение + добавление

```c
fclose(file);
```

### fscanf
```c
int fscanf(FILE *stream, const char *format, ...);
```
- FILE *stream — указатель на поток, из которого будет читаться информация. Например, stdin для стандартного ввода. Если вы хотите читать из файла, используйте указатель на файл, полученный функцией fopen.

- const char *format — строка формата, которая определяет, как будут интерпретироваться данные. Она может содержать спецификаторы формата (начинающиеся с %), указывающие, какого типа данные следует ожидать.

- ... (аргументы) — переменное количество аргументов, которые представляют указатели на переменные. Эти переменные будут заполнены считанными значениями, соответствующими спецификаторам формата.
#### Пример
```c
#include <stdio.h>

int main() {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int num;
    float pi;

    // Чтение данных из файла
    if (fscanf(file, "%d %f", &num, &pi) == 2) {
        printf("Number: %d, Pi: %.2f\n", num, pi);
    } else {
        printf("Failed to read data\n");
    }

    fclose(file);
    return 0;
}
```

### fgetc / getc
```c
fgetc(file); // - 1 char
getc(file); // - 1 char
```
### fgets
```c
fgets(file, n, buffer); // считывание кусками
```
### fread 
```c
fread(file, size, count, buffer); // size *count байт в буффер
```
### feof(file)




## Запись
### fprintf
```c
fprintf(file, const char *format, аргументы)

```
- FILE *stream — указатель на поток, в который будет записан текст. Например, stdout для стандартного вывода или stderr для вывода ошибок. Если вы хотите записать в файл, используйте указатель на файл, полученный функцией fopen.

- const char *format — строка формата, которая определяет, как будут выведены данные. Она может содержать текст и спецификаторы формата (начинающиеся с %), которые указывают, как выводить последующие аргументы.

- ... (аргументы) — переменное количество аргументов, соответствующих спецификаторам в строке формата. Каждый аргумент по очереди подставляется вместо соответствующего спецификатора в format.
#### Пример
```c
#include <stdio.h>

int main() {
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int num = 42;
    float pi = 3.14159;

    // Вывод переменных в файл
    fprintf(file, "Number: %d, Pi: %.2f\n", num, pi);

    fclose(file);
    return 0;
}
```
### fpute
```c
fpute(file, char)
```
### fputs
```c
fputs(file, buffer)
```
### fwrite
```c
fwrite(file, size, count, buffer)
```
