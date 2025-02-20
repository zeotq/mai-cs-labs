#ifndef SQBYTE_HPP_
#define SQBYTE_HPP_

#include <stdint.h>
#include <stdio.h>

#define NAME_SIZE 8
#define WRONG_TYPE_SIZE 1U

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef uint8_t DB_SYS_DATA_SIZE;

typedef enum {
    db_int8,
    db_int16,
    db_int32,
    db_int64,
    db_double,
    db_char,
    db_unknown
} DataBaseTypes;

typedef struct DataBaseField {
    char dataName[NAME_SIZE];
    DB_SYS_DATA_SIZE dataType;
    DB_SYS_DATA_SIZE dataSize;
} DataBaseField;

typedef struct DataBase {
    FILE * dataBaseFile;
    DB_SYS_DATA_SIZE fieldsCount;
    DB_SYS_DATA_SIZE linesCount; 
    DataBaseField * fieldsData;
    void * dataBaseData;
} DataBase;

// DataBase types convertation
const char *DataBaseTypesToStr(DataBaseTypes type);
const size_t DataBaseTypesMemorySize(DataBaseTypes type);

DataBase * createBase(char * dataBaseFileName, DB_SYS_DATA_SIZE countFields, DataBaseField * fieldsTable);
DataBase * openBase(char * dataBaseFileName);
void closeBase(DataBase ** dataBase);

void updateLinesCount(DataBase * dataBase);

size_t getLineSize(DataBase * dataBase);

// Returns the count of total written lines, 0 if there are errors
uint32_t writeLine(DataBase * dataBase, uint8_t * data);

// Returns readed data, 0 if there are errors
uint8_t * readLine(DataBase * dataBase);

uint32_t printLine(FILE * stream, DataBase * dataBase, size_t lineSize, uint8_t * lineData);

// Returns 1 if all printed to stream, 0 if there are errors
uint32_t printBaseHeader(FILE * stream, DataBase * dataBase);

// int printBaseLines(FILE * stream, FILE * baseFile);
#endif