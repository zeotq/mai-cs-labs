#include "SQByte.h"

#include <stdlib.h>
#include <getopt.h>

void usageError() {
    fprintf(stderr ,"Usage:\n\
<program_name> -f <database_name> [--header]\
\n\
Options:\n\
\t-f, --file <database_name>    Имя базы данных\n\
\t--header                      Распечатать заголовки\n");
}

int main(int argc, char * argv[]) {
    int headerFlag = 0;
    char * dataBaseName = NULL;

    struct option LongOption[] = {
        {"file", required_argument, 0, 'f'},
        {"header", no_argument, &headerFlag, 1},
        {0, 0, 0, 0}
    };

    if (argc < 3){
        usageError();
        exit(EXIT_FAILURE);
    }

    int opt;
    int optIndex = 0;

    while ((opt = getopt_long(argc, argv, "f:", LongOption, &optIndex)) != -1) {
        switch (opt)
        {
        case 'f':
            dataBaseName = optarg;
            break;
        default:
            break;
        }
    }

    if (dataBaseName == NULL) {
        usageError();
        exit(EXIT_FAILURE);
    }

    DataBase * DB = openBase(dataBaseName);

    if (headerFlag) {
        printBaseColums(stdout, DB);
        printf("\n");
    }
    
    for (uint32_t k = 0; k < DB->linesCount; ++k) {
        uint8_t * lineData = readLine(DB, k);
        printLine(stdout, DB, getLineSize(DB), lineData);
        printf("\n");
    }
    closeBase(&DB);
    
    return 0;
}