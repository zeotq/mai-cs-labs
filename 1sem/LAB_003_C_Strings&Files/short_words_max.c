#include <stdlib.h>
#include <stdio.h>

int is_lowercase_char(char ch) {
    // Проверка на строчные буквы английского и русского алфавитов
    return ((ch >= 'a' && ch <= 'z') || (ch >= (char)224 && ch <= (char)255));
}

int is_uppercase_char(char ch) {
    // Проверка на заглавные буквы английского и русского алфавитов
    return ((ch >= 'A' && ch <= 'Z') || (ch >= (char)192 && ch <= (char)223));  // (char) - для разных компиляторов
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

    size_t allocated = 15;
    size_t i_tempword = 0;
    char *tempword = malloc(sizeof(char) * allocated);
    if (tempword == NULL) {
        fprintf(stderr, "Ошибка выделения памяти.\n");
        exit(1);
    }

    size_t counter = 0;
    int inWord = 0;
    int wordLen = 0;
    int maxWordLen = 4;
    int isFileFineshed = feof(file);
    scanf("%d", &maxWordLen);

    char c = 0;
    while (!isFileFineshed) {  // Пока не достигнут конец файла
        c = fgetc(file);  // Читаем символ
        isFileFineshed = feof(file);

        // Проверка символа
        if((is_lowercase_char(c) || is_uppercase_char(c)) && !isFileFineshed) {
            if(inWord) {
                ++wordLen;
            } else {
                inWord = 1;
                wordLen = 1;
            }
        } else {
            inWord = 0;
        }

        if(inWord) { // Если находимся в слове, добавляем символ в память 
            tempword[i_tempword] = c;
            ++i_tempword;
            // Выделяем в два раза больше памяти, если закончилось место
            if (i_tempword >= allocated) { 
                allocated *= 2;
                char *tempmem = realloc(tempword, allocated * sizeof(char));
                if (tempmem == NULL) {  // Проверка на успешное выделение
                    fprintf(stderr, "Ошибка расширения памяти.\n");
                    free(tempword);                    
                    return 1;
                }
                tempword = tempmem;
            }
        }

        // Слово закончилось
        if(wordLen && !inWord) {
            if(wordLen <= maxWordLen) {  // Если длина слова не 0 и меньше максимальной длины
                ++counter;
                for (int i = 0; i < i_tempword; ++i) { // Записываем слово в выходной файл
                    fputc(tempword[i], outFile);
                }
                fputc(' ', outFile);
                printf("\e[4;32m");
            }

            for (int i = 0; i < i_tempword; ++i) { // Выводим слово в консоль
                printf("%c", tempword[i]);
            }

            printf(" {%d}", wordLen);
            printf("\e[0;0m");
            printf("%c", c);
            i_tempword = 0;
            inWord = 0;
            wordLen = 0;
            
        } else if(!inWord && !isFileFineshed){
            printf("%c", c);
        }
    }

    printf("\n\e[0;0mShort words in \e[0;3m%s\e[0;0m: %zu\n\e[0;0m", inputFileName, counter);
    free(tempword);
    fclose(file);
    fclose(outFile);

    return 0;
}