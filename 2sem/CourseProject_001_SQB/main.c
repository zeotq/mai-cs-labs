#include "SQByte.h"
#include "SQByte.c"
#include "StudentData.h"
#include "StudentData.c"

int main(){
    DataBase * studentsBase =  createBase("database/students.bin", tableStudentsFieldsCount, tableStudentsFields);
    //DataBase * studentsBase = openBase("database/students.bin");
    
    if (studentsBase) {
        printf("Students Data Base created/opened correctly\n");
        fillRandomStudents(studentsBase, 1);
        printBaseHeader(stdout, studentsBase);
        uint8_t * lineData = readLine(studentsBase);
        printLine(stdout, studentsBase, getLineSize(studentsBase), lineData);

        closeBase(&studentsBase);
    }

    return 0;
}