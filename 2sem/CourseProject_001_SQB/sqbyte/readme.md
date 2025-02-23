# SQByte Lib

## About
SQByte is a simple database that stores all data in binary files.

## Structs

### DataBaseField
This `typedef struct` describes database columns in the following format:
|Name|Type|Description|
|-|-|-|
dataName|char[NAME_SIZE]|Unique column name
dataType|DB_SYS_DATA (uint8_t)|SQByte-supported type from `DataBaseTypes`
dataSize|DB_SYS_DATA (uint8_t)|Number of elements

#### You can define database fields as shown in the example below:

```C
DataBaseField tableMarksFields[] = {
    {"stud_id", db_int16, 1},
    {"sub_nm", db_char, 32},
    {"sub_mk", db_int8, 32}
};
```

### DataBase
The main library structure, used as an interface to read, write, update, and delete data from the database.

```C
FILE * dataBaseFile; // Binary database file  
DB_SYS_DATA fieldsCount;
DB_SYS_DATA linesCount; // Number of filled database rows  
DataBaseField * fieldsData;
void * dataBaseData; // Not used currently | SEEK value to the first row  
```

### DataBaseCondition
```C
char columnName[NAME_SIZE]; // Name of the column to check condition
int (*check)(const size_t dataLen, const void *data); /* Function checks the condition for the data in the column. 
Must returns non-0 if the condition is true.
dataLen is the count of one-type elements in the cell
```

### DataBaseResponse
Standart responce to the select request
```C
size_t linesCount; // Count of returned lines
uint8_t * data; // Row returned data. Use getLineSize() to parse this.
```

## Credits
Author - Egor Kudriavtsev (aka zeotq)
