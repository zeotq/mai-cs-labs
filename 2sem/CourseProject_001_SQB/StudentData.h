#ifndef STUDENT_HPP_
#define STUDENT_HPP_

#include "SQByte.h"
#include <stdint.h>

#define tableStudentsFieldsCount 6
#define tableMarksFieldsCount 3

DataBaseField tableStudentsFields[] = {
    {"ID", db_int16, 1},
    {"Sex", db_int8, 1},
    {"Initial", db_char, 2},
    {"2nd_name", db_char, 32},
    {"class_n", db_int8, 1},
    {"class_w", db_char, 1}
};

DataBaseField tableMarksFields[] = {
    {"stud_id", db_int16, 1},
    {"sub_nm", db_char, 32},
    {"sub_mk", db_int8, 32}
};

void fillRandomStudents(DataBase * dataBase, int linesCount); 

#endif