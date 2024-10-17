### Вывести все строки между `<body>` и `<\body>` из .html файлов

### Sample link: 
```https://faq8.ru/file.php/download/2/272/jstu4-2.3.zip```

#### Создание дирректории и загрузка архива
```
./MAI_labs$ mkdir Лаба_UNIX
./MAI_labs$ cd Лаба_UNIX
./MAI_labs/Лаба_UNIX$ wget <link>
```

#### Распаковка zip-архива
```
./MAI_labs/Лаба_UNIX$ sudo apt install zip
./MAI_labs/Лаба_UNIX$ unzip jstu4-2.3.zip
./MAI_labs/Лаба_UNIX$ cd jstu4-2.3/
```

~~Неудачный способ:~~
```
find . -name "*.html" -exec grep -A 1000 '<body>' {} \; | grep -B 1000 '</body>'
```

#### Универсальный способ выполнения ключевой задачи
```
find . -name "*.html" -exec awk '/<body>/,/<\/body>/' {} \;
```

#### Дополнительная задача
__&&__ - параллельное выполнение<br>
__;__ - последовательное выполнение<br>

```
mkdir -p logs_123 && find /var/log -name "*.log" -exec sudo cp {} logs_123/ \;; tar -cvf logs_123.tar logs_123; cat ./logs_123/*
```