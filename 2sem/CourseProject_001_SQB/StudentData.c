#include "StudentData.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"

// Universal generator
void fillRandomStudents(DataBase * dataBase, int linesCount) {
    srand(time(NULL));
    size_t dataBaseLineSize = getLineSize(dataBase);

    for (uint16_t i = 0; i < linesCount; ++i) {
        uint8_t * object = malloc(dataBaseLineSize);
        uint32_t objectIndex = 0;

        for (uint16_t j = 0; j < dataBase->fieldsCount; ++j) {
            switch (dataBase->fieldsData[j].dataType)
            {
            case db_char:
                for (uint16_t lit = 0; lit < dataBase->fieldsData[j].dataSize; ++lit) {
                    object[objectIndex] = 'A' + rand() % 26;
                    objectIndex += sizeof(char);
                }
                break;

            case db_double:
                for (uint16_t lit = 0; lit < dataBase->fieldsData[j].dataSize; ++lit) {
                    if (objectIndex + sizeof(double) > dataBaseLineSize) {
                        printf(ANSI_COLOR_RED "WARNING: Buffer overflow!\n" ANSI_COLOR_RESET);
                        break;
                    }
                    double doubleValue = (double)(rand() % 1024) / (double)(rand() % 512);
                    memcpy(&object[objectIndex], &doubleValue, sizeof(double));
                    objectIndex += sizeof(double);
                }
                break;
            
            default:
                for (uint16_t lit = 0; lit < dataBase->fieldsData[j].dataSize; ++lit) {
                    size_t blockSize = DataBaseTypesMemorySize(dataBase->fieldsData[j].dataType);
                    if (objectIndex + blockSize > dataBaseLineSize) {
                        printf(ANSI_COLOR_RED "WARNING: Buffer overflow!\n" ANSI_COLOR_RESET);
                        break;
                    }
                    uint64_t defaultValue = rand() % 65535;
                    memcpy(&object[objectIndex], &defaultValue, blockSize);
                    objectIndex += blockSize;
                }
                break;
            }
        }
        dataBase->linesCount += writeLine(dataBase, object);
    }
    updateLinesCount(dataBase);
}