#include "SQByte.h"
#include "StudentData.h"

#include <stdlib.h>
#include <getopt.h>

void usageError() {
    fprintf(stderr ,"Usage:\n\
<program_name> -f <database_name>\
\n\
Options:\n\
\t-f, --file <database_name>    Имя базы данных\n");
}

int condition(int linesCount, uint8_t * marks) {
    int canTakeMoney_1 = 1;
    int countBadMarks_1 = 0;
    int canTakeMoney_2 = 1;
    int countBadMarks_2 = 0;

    for (int i = 0; i < linesCount; ++i) {
        if (marks[i * DataBaseTypesMemorySize(db_int8)] < 4) {
            canTakeMoney_1 = 0;
            countBadMarks_2 += 1;
        }
        if (canTakeMoney_1 && marks[i] < 5) {
            countBadMarks_1 += 1;
        }
    }
    if (canTakeMoney_1 && countBadMarks_1 < 2) {
        return 1;
    }
    if (canTakeMoney_2 && countBadMarks_2 < 2) {
        return 1;
    }
    return 0;
}

int main(int argc, char * argv[]) {
    char * dataBaseName = NULL;

    struct option LongOption[] = {
        {"file", required_argument, 0, 'f'},
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

    DataBase * studentsBase =  openBase(dataBaseName);
    
    if (!studentsBase) {
        exit(EXIT_FAILURE);
    }

    DataBaseCondition condit = {
        .check = condition,
        .columnName = "marks"
    };

    DataBaseResponse * response = selectLines(studentsBase, condit);
    size_t lineSize = getLineSize(studentsBase);

    putc('\t', stdout);
    printBaseColums(stdout, studentsBase);
    putc('\n', stdout);

    for (int i = 0; i < response->linesCount; ++i) {
        printf("%d.\t", i);
        printLine(stdout, studentsBase, lineSize, &(response->data[lineSize * i]));
        putc('\n', stdout);
    }

    free(response->data);
    free(response);
    closeBase(&studentsBase);
    return 0;
}