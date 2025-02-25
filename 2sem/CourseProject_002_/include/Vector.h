#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <stdint.h>
#include <stdbool.h>

typedef uint32_t T;

typedef struct Vector {
    T * data;
    size_t size;
    size_t capacity;
} Vector;

Vector * Vector_create();
void Vector_destroy(Vector *);
bool Vectror_empty(Vector *);
size_t Vector_size(Vector *);
T* Vector_at(Vector *, size_t);
void Vector_pushBack(Vector *, T);
T Vector_popBack(Vector *);
bool Vector_equal(Vector *, Vector *, bool(*cmp)(T, T));

#endif