#include <stdlib.h>
#include <stdio.h>

int is_lowercase_char(char ch) {
    // Проверка на строчные буквы английского и русского алфавитов
    return ((ch >= 'a' && ch <= 'z') || (ch >= (char)224 && ch <= (char)255));
}

int is_uppercase_char(char ch) {
    // Проверка на заглавные буквы английского и русского алфавитов
    return ((ch >= 'A' && ch <= 'Z') || (ch >= (char)192 && ch <= (char)223)); // А вот к типу char я привожу для совместимости с разными компиляторами
}

int main(int argc, char * argv[]) {
    if(argc < 3) {
        // Проверка ввода
        printf("Error: 2 file names were expected, but were received %d\n", argc - 1);
        exit(-1);
    }

    const char * inputFileName = argv[1];
    const char * outputFileName = argv[2];

    FILE * file = fopen(inputFileName, "r");
    FILE * outFile = fopen(outputFileName, "w");

    if(file == NULL) {
        printf("Error: cant open file %s\n", inputFileName);
        exit(1);
     }

    if(outFile == NULL) {
        printf("Error: cant open outFile %s\n", outputFileName);
        exit(1);
    }

    size_t counter = 0;
    int inWord = 0;
    int isLowletter = 0;

    char c = 0;
    while (!feof(file)) { // Пока не достигнут конец файла
        c = fgetc(file); // Читаем символ
        if(!inWord && is_lowercase_char(c)) { // Если прочитали строчную букву и inWord == False
            inWord = 1;
            isLowletter = 1;
        } else if(!inWord && is_uppercase_char(c)) {  // Если прочитали заглавную букву и inWord == False
            inWord = 1;
            isLowletter = 0;
        } else if(inWord && is_uppercase_char(c)) { // Если прочитали заглавную букву и inWord == 1
            // Слово не малобуквенное
            isLowletter = 0;
        /*
        Если символ не является заглавной или строчной буквой 
        или файл закончился
        */
        } else if((!is_lowercase_char(c) && !is_uppercase_char(c)) || feof(file)) {
            // Увеличиваем счетчик, если слово малобуквенное
            counter += isLowletter;
            // Обнуляем проверки
            isLowletter = 0;
            inWord = 0;
        }
    }

    printf("Low-letter words in %s: %zu\n", inputFileName, counter);
    fclose(file);
    fclose(outFile);

    return 0;
}