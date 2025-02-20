#include "SQByte.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

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

DataBase * createBase(char * dataBaseFileName, DB_SYS_DATA_SIZE countFields, DataBaseField * fieldsTable) {
    FILE * file = fopen(dataBaseFileName, "wb+");
    DB_SYS_DATA_SIZE linesCount = 0;
    if (!file) {
        perror(ANSI_COLOR_RED "Error at createBase: Can't open file correctly\n" ANSI_COLOR_RESET);
        return NULL;
    }
    fwrite(&countFields, sizeof(DB_SYS_DATA_SIZE), 1, file);
    fwrite(fieldsTable, sizeof(DataBaseField), countFields, file);
    fwrite(&linesCount, sizeof(DB_SYS_DATA_SIZE), 1, file);
    
    DataBase * dataBase = malloc(sizeof(DataBase));
    if (!dataBase) {
        printf(ANSI_COLOR_RED "Error at createBase: can't allocate memory for DataBase" ANSI_COLOR_RESET);
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

    DB_SYS_DATA_SIZE countFields;
    DB_SYS_DATA_SIZE linesCount;
    char name[NAME_SIZE];

    fseek(file, 0L, SEEK_SET);
    fread(&countFields, sizeof(DB_SYS_DATA_SIZE), 1, file);

    DataBaseField * fieldsData = malloc(sizeof(DataBaseField) * countFields);
    if (!fieldsData) {
        printf(ANSI_COLOR_RED "Error at openBase: can't allocate memory for DataBase" ANSI_COLOR_RESET);
        fclose(file);
        return NULL;
    }

    fread(fieldsData, sizeof(DataBaseField), countFields, file);
    fread(&linesCount, sizeof(DB_SYS_DATA_SIZE), 1, file);

    DataBase * dataBase = malloc(sizeof(DataBase));
    if (!dataBase) {
        printf(ANSI_COLOR_RED "Error at openBase: can't allocate memory for DataBase" ANSI_COLOR_RESET);
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

void updateLinesCount(DataBase * dataBase) {
    size_t offset = sizeof(DB_SYS_DATA_SIZE) + dataBase->fieldsCount * sizeof(DataBaseField);
    fseek(dataBase->dataBaseFile, offset, SEEK_SET);
    fwrite(&dataBase->linesCount, sizeof(DB_SYS_DATA_SIZE), 1, dataBase->dataBaseFile);
}

size_t getLineSize(DataBase * dataBase) {
    if (!dataBase) {
        printf(ANSI_COLOR_RED "Error on getLineSize: NULL DataBase\n" ANSI_COLOR_RESET);
        return 0;
    }
    size_t lineSize = 0;
    for (uint32_t i = 0 ; i < dataBase->fieldsCount; ++i) {
        lineSize += DataBaseTypesMemorySize(dataBase->fieldsData[i].dataType) * dataBase->fieldsData[i].dataSize;
    }
    return lineSize;
}

uint32_t writeLine(DataBase * dataBase, uint8_t * data) {
    if (!dataBase || !dataBase->dataBaseFile || !data) {
        printf(ANSI_COLOR_RED "Error: Missing arguments\n" ANSI_COLOR_RESET);
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

    return 1;
}

uint8_t * readLine(DataBase * dataBase) {
    if (!dataBase || !dataBase->dataBaseFile) {
        printf(ANSI_COLOR_RED "Error: Missing arguments\n" ANSI_COLOR_RESET);
        return 0;
    }
    size_t offset = 2 * sizeof(DB_SYS_DATA_SIZE) + dataBase->fieldsCount * sizeof(DataBaseField);
    fseek(dataBase->dataBaseFile, offset, SEEK_SET);
    size_t lineSize = getLineSize(dataBase);
    uint8_t * lineData = malloc(lineSize);
    fread(lineData, lineSize, 1, dataBase->dataBaseFile);
    return lineData;
}

uint32_t printLine(FILE * stream, DataBase * dataBase, size_t lineSize, uint8_t * lineData) {
    size_t mem_index = 0;
    for (uint32_t i = 0; i < dataBase->fieldsCount && mem_index < lineSize; ++i) {
        fprintf(stream, "%s:\t", DataBaseTypesToStr(dataBase->fieldsData[i].dataType));
        switch (dataBase->fieldsData[i].dataType)
        {
            case db_char: {
                for (uint32_t t = 0; t < dataBase->fieldsData[i].dataSize; ++t) {
                    fprintf(stream, "%c", lineData[mem_index]);
                    mem_index++;
                }
                fprintf(stream, "\n");
                break;
            }
            case db_double: {
                double doubleValue;
                for (uint32_t t = 0; t < dataBase->fieldsData[i].dataSize; ++t) {
                    memcpy(&doubleValue, &lineData[mem_index], sizeof(double));
                    fprintf(stream, "%f ", doubleValue);
                    mem_index += sizeof(double);
                }
                fprintf(stream, "\n");
                break;
            }
            default: {
                int64_t intValue = 0;
                size_t typeSize = DataBaseTypesMemorySize(dataBase->fieldsData[i].dataType);
                for (uint32_t t = 0; t < dataBase->fieldsData[i].dataSize; ++t) {
                    memcpy(&intValue, &lineData[mem_index], typeSize);
                    fprintf(stream, "%ld ", intValue);
                    mem_index += typeSize;
                }
                fprintf(stream, "\n");
                break;
            }
        }
    }
}

uint32_t printBaseHeader(FILE * stream, DataBase * dataBase) {
    if (!stream) {
        fprintf(stream, ANSI_COLOR_RED "Error: NULL stream\n" ANSI_COLOR_RESET);
        return 0;
    }

    if (!dataBase) {
        fprintf(stream, ANSI_COLOR_RED "Error: NULL base\n" ANSI_COLOR_RESET);
        return 0;
    }

    fprintf(stream, "Colums: %u\n", dataBase->fieldsCount);
    for (int i = 0; i < dataBase->fieldsCount; i++) {
        fprintf(stream, "%d: %s, Type: %s, Size: %u * %lu byte\n", 
        i + 1, 
        dataBase->fieldsData[i].dataName, 
        DataBaseTypesToStr(dataBase->fieldsData[i].dataType), 
        dataBase->fieldsData[i].dataSize,
        DataBaseTypesMemorySize(dataBase->fieldsData[i].dataType));
    }
    fprintf(stream, "Lines count: %d\n", dataBase->linesCount);

    return 1;
}
