#include "SQByte.h"
#include "StudentData.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

void usageError() {
    fprintf(stderr ,"Usage:\n\
<program_name> -f <database_name> -p <count_of_lines> [--new --fast]\
\n\
Options:\n\
\t-f, --file <database_name>    Имя базы данных\n\
\t-p, --count <count_of_lines>  Количество строк для генерации\n\
\t--new                         Создать новый файл (если флаг указан)\n\
\t--fast                        Использовать быстрый генератор (если флаг указан)\n");
}

int main(int argc, char * argw[]) {
    uint32_t linesCount = 0;
    int newFlag = 0;
    int fastFlag = 0;
    char * dataBaseName = NULL;

    struct option LongOption[] = {
        {"file", required_argument, 0, 'f'},
        {"count", required_argument, 0, 'p'},
        {"new", no_argument, &newFlag, 1},
        {"fast", no_argument, &fastFlag, 1},
        {0, 0, 0, 0}
    };

    if (argc < 5){
        usageError();
        exit(EXIT_FAILURE);
    }

    uint32_t opt;
    uint32_t optionIndex = 0;

    while ((opt = getopt_long(argc, argw, "f:p:", LongOption, &optionIndex)) != -1) {
        switch (opt)
        {
        case 'f':
            dataBaseName = optarg;
            break;
        case 'p':
            linesCount = atoi(optarg);
            break;
        default:
            break;
        }
    }

    if (dataBaseName == NULL || linesCount <= 0) {
        usageError();
        exit(EXIT_FAILURE);
    }

    DataBase * DB = NULL;
    if (newFlag) {
        DB = createBase(dataBaseName, tableStudentsFieldsCount, tableStudentsFields); 
    } else {
        DB = openBase(dataBaseName);
    }

    if (fastFlag) {
        fastRandomData(DB, linesCount);
    } else {
        fillRandomData(DB, linesCount);
    }
    closeBase(&DB);

    return 0;
}