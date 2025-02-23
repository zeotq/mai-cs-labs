#include "SQByte.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Data types convertation

const char *DataBaseTypesToStr(DataBaseTypes type) {
    switch (type) {
        case db_int8: return "db_int8";
        case db_int16: return "db_int16";
        case db_int32: return "db_int32";
        case db_int64: return "db_int64";
        case db_double: return "db_double";
        case db_char: return "db_char";
        default: return "db_unknown";
    }
}

const size_t DataBaseTypesMemorySize(DataBaseTypes type) {
    switch (type) {
        case db_int8: return 1U;
        case db_int16: return 2U;
        case db_int32: return 4U;
        case db_int64: return 8U;
        case db_double: return sizeof(double);
        case db_char: return sizeof(char);
        default: return WRONG_TYPE_SIZE;
    }
}

DataBaseField * getSouceFieldsTable(DataBase * dataBase) {
    DataBaseField * sourceFieldsTable = NULL;

    if (!dataBase) {
        fprintf(stderr, ANSI_COLOR_RED "Error on getSourceFieldsTable: NULL DataBase\n" ANSI_COLOR_RESET);
        return 0;
    }
    
    size_t lineSize = 0;
    for (uint32_t i = 0 ; i < dataBase->fieldsCount; ++i) {
        lineSize += DataBaseTypesMemorySize(dataBase->fieldsData[i].dataType) * dataBase->fieldsData[i].numberOfElements;
    }
    return NULL;
}

// Database connection processing

DataBase * createBase(char * dataBaseFileName, DB_SYS_DATA countFields, DataBaseField * fieldsTable) {
    FILE * file = fopen(dataBaseFileName, "wb+");
    DB_SYS_DATA linesCount = 0;
    if (!file) {
        perror(ANSI_COLOR_RED "Error at createBase: Can't open file correctly " ANSI_COLOR_RESET);
        return NULL;
    }
    fwrite(&countFields, sizeof(DB_SYS_DATA), 1, file);
    fwrite(fieldsTable, sizeof(DataBaseField), countFields, file);
    fwrite(&linesCount, sizeof(DB_SYS_DATA), 1, file);
    
    DataBase * dataBase = malloc(sizeof(DataBase));
    if (!dataBase) {
        fprintf(stderr, ANSI_COLOR_RED "Error at createBase: can't allocate memory for DataBase" ANSI_COLOR_RESET);
        fclose(file);
        return NULL;
    }
    dataBase->dataBaseFile = file;
    dataBase->fieldsCount = countFields;

    dataBase->fieldsData = malloc(sizeof(DataBaseField) * countFields);
    memcpy(dataBase->fieldsData, fieldsTable, sizeof(DataBaseField) * countFields);

    dataBase->linesCount = linesCount;
    dataBase->dataBaseData = NULL;

    return dataBase;
}

DataBase * openBase(char * dataBaseFileName) {
    FILE * file = fopen(dataBaseFileName, "rb+");
    if (!file) {
        perror(ANSI_COLOR_RED "Error at openBase: Can't open file correctly\n" ANSI_COLOR_RESET);
        return NULL;
    }

    DB_SYS_DATA countFields;
    DB_SYS_DATA linesCount;
    char name[NAME_SIZE];

    fseek(file, 0L, SEEK_SET);
    fread(&countFields, sizeof(DB_SYS_DATA), 1, file);

    DataBaseField * fieldsData = malloc(sizeof(DataBaseField) * countFields);
    if (!fieldsData) {
        fprintf(stderr, ANSI_COLOR_RED "Error at openBase: can't allocate memory for DataBase" ANSI_COLOR_RESET);
        fclose(file);
        return NULL;
    }

    fread(fieldsData, sizeof(DataBaseField), countFields, file);
    fread(&linesCount, sizeof(DB_SYS_DATA), 1, file);

    DataBase * dataBase = malloc(sizeof(DataBase));
    if (!dataBase) {
        fprintf(stderr, ANSI_COLOR_RED "Error at openBase: can't allocate memory for DataBase" ANSI_COLOR_RESET);
        free(fieldsData);
        fclose(file);
        return NULL;
    }
    dataBase->dataBaseFile = file;
    dataBase->fieldsCount = countFields;
    dataBase->fieldsData = fieldsData;
    dataBase->linesCount = linesCount;
    dataBase->dataBaseData = NULL;
    return dataBase;
}

void closeBase(DataBase ** dataBase) {
    if (!(*dataBase)) return;
    fclose((*dataBase)->dataBaseFile);
    free((*dataBase)->fieldsData);
    free(*dataBase);
    (*dataBase) = NULL;
}

// Database size and offset information

size_t getHeaderSize(DataBase * dataBase) {
    if (!dataBase) {
        return 0;
    }
    size_t offset = 2 * sizeof(DB_SYS_DATA) + dataBase->fieldsCount * sizeof(DataBaseField);
    return offset;
}

size_t getLineSize(DataBase * dataBase) {
    if (!dataBase) {
        fprintf(stderr, ANSI_COLOR_RED "Error on getLineSize: NULL DataBase\n" ANSI_COLOR_RESET);
        return 0;
    }
    size_t lineSize = 0;
    for (uint32_t i = 0 ; i < dataBase->fieldsCount; ++i) {
        lineSize += DataBaseTypesMemorySize(dataBase->fieldsData[i].dataType) * dataBase->fieldsData[i].numberOfElements;
    }
    return lineSize;
}

size_t getColumnOffset(DataBase * dataBase, char * columnName) {
    size_t targetColumnOffset = 0;
    uint8_t targetFounded = 0;
    
    for (uint32_t i = 0; i < dataBase->fieldsCount; ++i) {
        if (!strncmp(columnName, dataBase->fieldsData[i].dataName, NAME_SIZE)) {
            targetFounded = 1;
            break;
        }
        targetColumnOffset += dataBase->fieldsData[i].numberOfElements * DataBaseTypesMemorySize(dataBase->fieldsData[i].dataType);
    }

    if (!targetFounded) SIZE_MAX;
    return targetColumnOffset;
}

size_t getColumnDataType(DataBase * dataBase, char * columnName) {
    for (uint32_t i = 0; i < dataBase->fieldsCount; ++i) {
        if (!strncmp(columnName, dataBase->fieldsData[i].dataName, NAME_SIZE)) {
            return dataBase->fieldsData[i].dataType;
        }
    }
    return SIZE_MAX;
}

size_t getColumnNumberOfElements(DataBase * dataBase, char * columnName) {
    for (uint32_t i = 0; i < dataBase->fieldsCount; ++i) {
        if (!strncmp(columnName, dataBase->fieldsData[i].dataName, NAME_SIZE)) {
            return dataBase->fieldsData[i].numberOfElements;
        }
    }
    return 0;
}

// Database header information processing

void updateLinesCount(DataBase * dataBase) {
    size_t offset = sizeof(DB_SYS_DATA) + dataBase->fieldsCount * sizeof(DataBaseField);
    fseek(dataBase->dataBaseFile, offset, SEEK_SET);
    fwrite(&dataBase->linesCount, sizeof(DB_SYS_DATA), 1, dataBase->dataBaseFile);
}

// Database processing a single row

uint8_t checkConditionForLine(DataBase * dataBase, uint8_t * lineData, size_t lineSize, DataBaseCondition * condition) {
    return 1;
}

uint8_t writeLine(DataBase * dataBase, uint8_t * data) {
    if (!dataBase || !dataBase->dataBaseFile || !data) {
        fprintf(stderr, ANSI_COLOR_RED "Error: Missing arguments\n" ANSI_COLOR_RESET);
        return 0;
    }

    fseek(dataBase->dataBaseFile, 0L, SEEK_END);
    size_t lineSize = getLineSize(dataBase);
    size_t written = fwrite(data, sizeof(uint8_t), getLineSize(dataBase), dataBase->dataBaseFile);

    if (written != lineSize) {
        printf("Error: written (%ld) != lineSize (%ld)\n", written, lineSize);
        perror("Reason");
        return 0;
    }

    dataBase->linesCount += 1;
    updateLinesCount(dataBase);
    return 1;
}

uint8_t * readLine(DataBase * dataBase, uint32_t lineNumber) {
    if (!dataBase || !dataBase->dataBaseFile) {
        fprintf(stderr, ANSI_COLOR_RED "Error at readLine function: Missing arguments\n" ANSI_COLOR_RESET);
        return NULL;
    }
    size_t lineSize = getLineSize(dataBase);
    size_t headerSize = getHeaderSize(dataBase);
    size_t offset = headerSize + lineSize * lineNumber; 
    uint8_t * lineData = malloc(lineSize);
    if (!lineData) {
        fprintf(stderr, ANSI_COLOR_RED "Error at readLine %d: Can't allocate memory\n" ANSI_COLOR_RESET, lineNumber);
        return NULL;
    }
    fseek(dataBase->dataBaseFile, offset, SEEK_SET);
    fread(lineData, lineSize, 1, dataBase->dataBaseFile);
    return lineData;
}

// Database processing of all data

DataBaseResponse * selectLines(DataBase * dataBase, DataBaseCondition condition) {
    if (!dataBase || !dataBase->dataBaseFile) {
        fprintf(stderr, ANSI_COLOR_RED "Error at selectLines function: Missing arguments\n" ANSI_COLOR_RESET);
        return NULL;
    }

    size_t lineSize = getLineSize(dataBase);
    size_t headerSize = getHeaderSize(dataBase);

    fseek(dataBase->dataBaseFile, headerSize, SEEK_SET);

    DataBaseResponse * dataBuffer = malloc(sizeof(DataBaseResponse));
    size_t realSize = lineSize * 4;
    dataBuffer->linesCount = 0;
    dataBuffer->data = malloc(realSize);
    
    if (!dataBuffer || !dataBuffer->data) {
        fprintf(stderr, ANSI_COLOR_RED "Error at selectLines: Can't allocate memory for dataBaseResponse\n" ANSI_COLOR_RESET);
        free(dataBuffer->data);
        free(dataBuffer); 
        return NULL;
    }

    size_t columnOffset = getColumnOffset(dataBase, condition.columnName);
    size_t columnNumOfEls = getColumnNumberOfElements(dataBase, condition.columnName);
    size_t columnType = getColumnDataType(dataBase, condition.columnName);
    size_t tartgetDataSize = columnNumOfEls * DataBaseTypesMemorySize(columnType);

    if (!columnNumOfEls || columnType == SIZE_MAX || columnOffset == SIZE_MAX) {
        fprintf(stderr, ANSI_COLOR_RED "Error at selectLines function: Wrong column name\n" ANSI_COLOR_RESET);
        free(dataBuffer->data);
        free(dataBuffer); 
        return NULL;
    }
    
    uint8_t * lineData = malloc(lineSize);
    uint8_t * tempTargetData = malloc(tartgetDataSize);
    
    if (!lineData || !tempTargetData) {
        fprintf(stderr, ANSI_COLOR_RED "Error at selectLines: Can't allocate memory\n" ANSI_COLOR_RESET);
        free(dataBuffer->data);
        free(dataBuffer); 
        free(lineData); 
        free(tempTargetData);
        return NULL;
    }

    for (uint32_t line = 0; line < dataBase->linesCount; ++line) {
        fread(lineData, lineSize, 1ULL, dataBase->dataBaseFile);

        for (uint32_t pointer = 0; pointer < tartgetDataSize; ++pointer) {
            tempTargetData[pointer] = lineData[columnOffset + pointer];
        }

        if (condition.check(columnNumOfEls, tempTargetData)) {
            memcpy(&(dataBuffer->data[(dataBuffer->linesCount) * lineSize]), lineData, lineSize);
            dataBuffer->linesCount += 1;

            if (dataBuffer->linesCount * lineSize == realSize) {
                size_t newRealSize = (realSize > dataBase->linesCount * lineSize / 2) 
                                      ? dataBase->linesCount * lineSize 
                                      : realSize * 2;

                uint8_t * newData = (uint8_t*) realloc(dataBuffer->data, newRealSize);
                if (!newData) {
                    fprintf(stderr, ANSI_COLOR_RED "Error at selectLines function: Can't realloc memory for dataBuffer\n" ANSI_COLOR_RESET);
                    free(dataBuffer->data);
                    free(dataBuffer);
                    free(lineData);
                    free(tempTargetData);
                    return NULL;
                }
                dataBuffer->data = newData;
                realSize = newRealSize;
            }
        }
    }

    free(lineData); 
    free(tempTargetData);
    return dataBuffer;
}

// Stream prints

uint8_t _printDataValidation(FILE * stream, DataBase * dataBase) {
    if (!stream) {
        fprintf(stream, ANSI_COLOR_RED "Error: NULL stream\n" ANSI_COLOR_RESET);
        return 0;
    }

    if (!dataBase) {
        fprintf(stream, ANSI_COLOR_RED "Error: NULL base\n" ANSI_COLOR_RESET);
        return 0;
    }
    return 1;
}

uint32_t printBaseHeader(FILE * stream, DataBase * dataBase) {
    if (!_printDataValidation(stream, dataBase)) {
        return 0;
    }

    fprintf(stream, "Colums: %u\n", dataBase->fieldsCount);
    for (int i = 0; i < dataBase->fieldsCount; i++) {
        fprintf(stream, "%d: %s, Type: %s, Size: %u * %lu byte\n", 
        i + 1, 
        dataBase->fieldsData[i].dataName, 
        DataBaseTypesToStr(dataBase->fieldsData[i].dataType), 
        dataBase->fieldsData[i].numberOfElements,
        DataBaseTypesMemorySize(dataBase->fieldsData[i].dataType));
    }
    fprintf(stream, "Lines linesCount: %d\n", dataBase->linesCount);

    return 1;
}

uint32_t printBaseColums(FILE * stream, DataBase * dataBase) {
    if (!_printDataValidation(stream, dataBase)) {
        return 0;
    }

    for (uint32_t k = 0; k < dataBase->fieldsCount; ++k) {
        fprintf(stream, "%.*s\t", NAME_SIZE, dataBase->fieldsData[k].dataName);
    }
    return 1;
}

uint32_t printLine(FILE * stream, DataBase * dataBase, size_t lineSize, uint8_t * lineData) {
    if (!_printDataValidation(stream, dataBase)) {
        return 0;
    }

    size_t mem_index = 0;
    for (uint32_t i = 0; i < dataBase->fieldsCount && mem_index < lineSize; ++i) {
        switch (dataBase->fieldsData[i].dataType)
        {
            case db_char: {
                for (uint32_t t = 0; t < dataBase->fieldsData[i].numberOfElements; ++t) {
                    fprintf(stream, "%c", lineData[mem_index]);
                    mem_index++;
                }
                break;
            }
            case db_double: {
                double doubleValue;
                for (uint32_t t = 0; t < dataBase->fieldsData[i].numberOfElements; ++t) {
                    memcpy(&doubleValue, &lineData[mem_index], sizeof(double));
                    fprintf(stream, "%f ", doubleValue);
                    mem_index += sizeof(double);
                }
                break;
            }
            default: {
                int64_t intValue = 0;
                size_t typeSize = DataBaseTypesMemorySize(dataBase->fieldsData[i].dataType);
                for (uint32_t t = 0; t < dataBase->fieldsData[i].numberOfElements; ++t) {
                    memcpy(&intValue, &lineData[mem_index], typeSize);
                    fprintf(stream, "%ld ", intValue);
                    mem_index += typeSize;
                }
                break;
            }
        }
        fprintf(stream, "\t");
    }
    return 1;
}

// Data Base random Data filler

uint32_t fillRandomData(DataBase * dataBase, int linesCount) {
    srand(time(NULL));
    size_t dataBaseLineSize = getLineSize(dataBase);
    uint32_t writtenLinesCount = 0;
    uint8_t * object = malloc(dataBaseLineSize);

    if (!object) {
        fprintf(stderr, "Error at fillRandomData: can't allocate memory\n");
    }

    for (uint32_t i = 0; i < linesCount; ++i) {
        uint8_t * ptr = object;

        for (uint16_t j = 0; j < dataBase->fieldsCount; ++j) {
            size_t blockSize = DataBaseTypesMemorySize(dataBase->fieldsData[j].dataType);
            uint16_t numElements = dataBase->fieldsData[j].numberOfElements;
            if (ptr + numElements * blockSize > object + dataBaseLineSize) {
                printf(ANSI_COLOR_RED "WARNING: Buffer overflow!\n" ANSI_COLOR_RESET);
                break;
            }

            switch (dataBase->fieldsData[j].dataType) {
                case db_char:
                    for (uint16_t lit = 0; lit < numElements; ++lit) {
                        *ptr++ = 'A' + (rand() % 26);
                    }
                    break;

                case db_double:
                    for (uint16_t lit = 0; lit < numElements; ++lit) {
                        double value = drand48();
                        memcpy(ptr, &value, sizeof(double));
                        ptr += sizeof(double);
                    }
                    break;

                case db_int8:
                case db_int16:
                case db_int32:
                case db_int64:
                    for (uint16_t lit = 0; lit < numElements; ++lit) {
                        uint64_t value = rand() % 65535;
                        if (dataBase->fieldsData[j].dataType == db_int8) {
                            value = value % 3 + 3;
                        }
                        memcpy(ptr, &value, blockSize);
                        ptr += blockSize;
                    }
                    break;

                default:
                    fprintf(stderr, ANSI_COLOR_RED "Error at fillRandomData: unsupported data type\n" ANSI_COLOR_RESET);
                    free(object);
                    exit(EXIT_FAILURE);
            }
        }

        writtenLinesCount += writeLine(dataBase, object);
    }

    free(object);
    updateLinesCount(dataBase);
    return writtenLinesCount;
}

uint32_t fastRandomData(DataBase * dataBase, int linesCount) {
    srand(time(NULL));
    size_t dataBaseLineSize = getLineSize(dataBase);
    uint32_t writtenLinesCount = 0;
    uint8_t * object = malloc(dataBaseLineSize);
    if (!object) {
        fprintf(stderr, "Error at fillRandomData: can't allocate memory\n");
    }

    for (uint32_t i = 0; i < linesCount; ++i) {
        uint8_t *ptr = object;
        for (uint32_t j = 0; j < dataBaseLineSize; ++j) {
            *ptr++ = 'A' + rand() % 26;
        }
        writtenLinesCount += writeLine(dataBase, object);
    }

    free(object);
    updateLinesCount(dataBase);
    return writtenLinesCount;
}