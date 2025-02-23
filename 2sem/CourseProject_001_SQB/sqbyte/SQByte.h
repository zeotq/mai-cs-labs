#ifndef SQBYTE_HPP_
#define SQBYTE_HPP_

#include <stdint.h>
#include <stdio.h>

#define SQBYTE_VERSION_MAJOR 1
#define SQBYTE_VERSION_MINOR 0
#define SQBYTE_VERSION_PATCH 0

#define NAME_SIZE 8
#define WRONG_TYPE_SIZE 1U

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef uint32_t DB_SYS_DATA;

typedef enum {
    db_int8,
    db_int16,
    db_int32,
    db_int64,
    db_double,
    db_char,
    db_unknown
} DataBaseTypes;

typedef struct {
    char dataName[NAME_SIZE];
    DB_SYS_DATA dataType;
    DB_SYS_DATA numberOfElements;
} DataBaseField;

typedef struct {
    FILE * dataBaseFile;
    DB_SYS_DATA fieldsCount;
    DB_SYS_DATA linesCount; 
    DataBaseField * fieldsData;
    void * dataBaseData;
} DataBase;

typedef struct {
    char columnName[NAME_SIZE];
    int (*check)(const size_t dataLen, const void *data);
} DataBaseCondition;

typedef struct {
    size_t linesCount;
    uint8_t * data;
} DataBaseResponse;


// Data types convertation

const char * DataBaseTypesToStr(DataBaseTypes type);
const size_t DataBaseTypesMemorySize(DataBaseTypes type);
DataBaseField * getSouceFieldsTable(DataBase * dataBase);

// Database connection processing

DataBase * createBase(char * dataBaseFileName, DB_SYS_DATA countFields, DataBaseField * fieldsTable);
DataBase * openBase(char * dataBaseFileName);
void closeBase(DataBase ** dataBase);

// Database size and offset information

size_t getHeaderSize(DataBase * dataBase);
size_t getLineSize(DataBase * dataBase);
size_t getColumnOffset(DataBase * dataBase, char * columnName);
size_t getColumnDataType(DataBase * dataBase, char * columnName);
size_t getColumnNumberOfElements(DataBase * dataBase, char * columnName);
// Database header information processing

void updateLinesCount(DataBase * dataBase);

// Database processing a single row

uint8_t writeLine(DataBase * dataBase, uint8_t * data);
uint8_t * readLine(DataBase * dataBase, uint32_t lineNumber);

// Database processing of all data

DataBaseResponse * selectLines(DataBase * dataBase, DataBaseCondition condition);
// uint32_t deleteLines(DataBase * dataBase, DataBaseCondition condition);
// uint32_t updateLines(DataBase * dataBase, DataBaseCondition condition);

// Stream prints

uint32_t printBaseHeader(FILE * stream, DataBase * dataBase);
uint32_t printBaseColums(FILE * stream, DataBase * dataBase);
uint32_t printLine(FILE * stream, DataBase * dataBase, size_t lineSize, uint8_t * lineData);

// Data Base random Data filler

uint32_t fillRandomData(DataBase * dataBase, int linesCount);
uint32_t fastRandomData(DataBase * DataBase, int linesCount);

#endif