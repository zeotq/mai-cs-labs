# Data Base

## generate.c
### Usage
```
<program_name> -f <database_name> -p <count_of_lines> [--new]
```

### Options:
||||
|-|-|-|
-f, --file|<database_name>|Имя базы данных
-p, --count|<count_of_lines>|Количество строк для генерации
--new||Создать новый файл (если флаг указан)

## reader.c 
### Usage
```
<program_name> -f <database_name> [--header]
```

### Options
||||
|-|-|-|
-f, --file|<database_name>|Имя базы данных
--header||Распечатать заголовки

## searcher.c
### Usage:
```
<program_name> -f <database_name>
```

||||
|-|-|-|
-f, --file|<database_name>|Имя базы данных

## fillfromkeyboard.c
### Usage:
```
<program_name> -f <database_name>
```

||||
|-|-|-|
-f, --file|<database_name>|Имя базы данных

---

*[Реализация работы с базой данных](sqbyte/readme.md)*

