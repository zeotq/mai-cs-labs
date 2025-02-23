#ifndef STUDENT_HPP_
#define STUDENT_HPP_

#include "SQByte.h"
#include <stdint.h>

#define tableStudentsFieldsCount 5

DataBaseField tableStudentsFields[] = {
    {"ID", db_int16, 1},
    {"Sex", db_int8, 1},
    {"Initial", db_char, 2},
    {"2nd_name", db_char, 16},
    {"marks", db_int8, 8}
};

#endif