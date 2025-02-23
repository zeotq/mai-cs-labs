#include "SQByte.h"
#include "StudentData.h"

#include <stdlib.h>
#include <string.h>
#include <getopt.h>

void usageError() {
    fprintf(stderr ,"Usage:\n\
<program_name> -f <database_name>\
\n\
Options:\n\
\t-f, --file <database_name>    Имя базы данных\n");
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
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

    size_t lineSize = getLineSize(studentsBase);
    uint8_t * dataToWrite = malloc(getLineSize(studentsBase));
    size_t dataIndex = 0;  

    for (int k = 0; k < studentsBase->fieldsCount; ++k) {
        size_t elementSize = DataBaseTypesMemorySize(studentsBase->fieldsData[k].dataType);
        size_t numberOfElements = studentsBase->fieldsData[k].numberOfElements;
        size_t blockSize = numberOfElements * elementSize;
        uint8_t * buffer = malloc(blockSize);

        if (dataIndex + blockSize > lineSize) {
            printf(ANSI_COLOR_RED "WARNING: Buffer overflow!\n" ANSI_COLOR_RESET);
            break;
        }

        fprintf(stdout, "%s %s * %ld: ", studentsBase->fieldsData[k].dataName, DataBaseTypesToStr(studentsBase->fieldsData[k].dataType), numberOfElements);

        switch (studentsBase->fieldsData[k].dataType)
        {
        case db_int8: case db_int16: case db_int32: case db_int64: 
            for (uint32_t i = 0; i < numberOfElements; ++i) {
                fscanf(stdin ,"%lu", (size_t*) &buffer[elementSize * i]);
            }
            break;
            
        case db_double:
            for (uint32_t i = 0; i < numberOfElements; ++i) {
                fscanf(stdin ,"%lf", (double*) &buffer[elementSize * i]);
            }
            break;

        case db_char:
            char * format = (char*) malloc(blockSize);
            for (uint32_t c = 0; c < numberOfElements; ++c) {
                buffer[c] = 0;
            }
            if (!format) {
                free(format);
                free(dataToWrite);
                free(buffer);
                fprintf(stderr, "Error at fillfromkeyboard");
                exit(EXIT_FAILURE);
            };
            sprintf(format, "%%%lds", numberOfElements);
            fscanf(stdin, format, (char*) buffer);
            free(format);
            break;
        
        default:
            break;
        }
        
        memcpy(&dataToWrite[dataIndex], buffer, blockSize);
        clearInputBuffer();
        free(buffer);
        dataIndex += blockSize;
    }

    writeLine(studentsBase, dataToWrite);
    closeBase(&studentsBase);
    free(dataToWrite);
}