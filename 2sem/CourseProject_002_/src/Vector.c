#include "../include/Vector.h"
#include <stdlib.h>

Vector * Vector_create() {
    Vector * result = (Vector *) malloc(sizeof(Vector));
    result->size = 0;
    result->capacity = 1;
    result->data = (T*) malloc(result->capacity * sizeof(T));
}

void Vector_destroy(Vector * vec) {
    free(vec->data);
    free(vec);
}

bool Vectror_empty(Vector * vec) {
    return vec->size == 0;
}

size_t Vector_size(Vector * vec) {
    return vec->size;
}

T* Vector_at(Vector * vec, size_t index) {
    if (index > vec->size) return NULL;
    return vec->data[index];
}

void Vector_pushBack(Vector * vec, T data) {
    if (vec->size >= vec->capacity) {
        vec->capacity *= 2;
        vec->data = (T*)realloc(vec->data, vec->capacity);
    }
    vec->data[vec->size] = data;
}

T Vector_popBack(Vector * vec) {
    if (Vectror_empty(vec)) {
        return;
    }
    return vec->data[vec->size--];
}

bool Vector_equal(Vector * vec_1, Vector * vec_2, bool(*cmp)(T, T)) {
    if (vec_1->size != vec_2->size) {
        return false;
    }
    // To do
    return true;
}