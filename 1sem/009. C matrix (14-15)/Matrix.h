#ifndef MATRIX
#define MATRIX

typedef int T;
typedef unsigned int uint;

typedef struct Matrix_ {
  T * data;
  uint n, m;

  int transposed;
  uint (*getN)(struct Matrix_ *);
  uint (*getM)(struct Matrix_ *);
} Matrix;

Matrix * Matrix_constructor(uint n, uint m, T*baseElement);
void Matrix_destructor(Matrix ** matrix);

T * Matrix_at(Matrix * matrix, uint i, uint j);
void Matrix_transpose(Matrix * matrix);
void Matrix_diagonales_replace(Matrix * matrix);

Matrix * Matrix_mult(Matrix * m1, Matrix * m2);
Matrix * Matrix_copy(Matrix * original);
void Matrix_fill_random(Matrix * matrix);
void Matrix_fill_from_console(Matrix * matrix);
void Matrix_cyclic_shift(Matrix * matrix);

#endif