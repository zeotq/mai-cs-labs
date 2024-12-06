class Matrix:
    def __init__(self, 
                 rows: int | None = None, 
                 columns: int | None = None, 
                 matrix: list[list[int]] | None = None, 
                 fill_function: None = None):
        """
        Matrix class

        Args:
            rows (int | None, optional): 
                Count of rows. Defaults to None.
            columns (int | None, optional): 
                Count of columns. Defaults to None.
            matrix (list[list[int]] | None, optional): 
                Create matrix object from list. Defaults to None.
            fill_function (None, optional): 
                Rules how to fill matrix (For example: lambda i, j, m, n: i + j + (m - 1) * i). Defaults to None.
        """

        if isinstance(matrix, list) and isinstance(matrix[0], list) and isinstance(matrix[0][0], int):
            self.matrix = matrix
            self.m = len(matrix)
            self.n = len(matrix[0]) if all([len(matrix[i]) == len(matrix[0]) for i in range(self.m)]) else None
            if self.n is None:
                raise(ValueError, "Incorrct matrix")
        elif isinstance(rows, int) and isinstance(columns, int):
            self.m = rows
            self.n = columns
            if fill_function is None:
                self.matrix = [[0 for j in range(self.n)] for i in range(self.m)]
            else:
                self.matrix = [[fill_function(i, j, self.m, self.n) for j in range(self.n)] for i in range(self.m)]
        else:
            raise(ValueError, "Incorrct inputs")

    def diagonal_fill(self):
        el_num = 1
        for delta in range(self.n):
            if delta:
                for i in range(self.n - delta):
                        self.matrix[i][delta + i] = el_num
                        el_num += 1
            for i in range(self.n - delta - 1, -1, -1):
                self.matrix[delta + i][i] = el_num
                el_num += 1

    def cyclic_shift(self):
        new_matrix = Matrix(self.n, self.m)
        for step in range(min(self.n, self.m)):
            for line in range(step, self.n - step, 1):
                for column in range(step, self.m - step, 1):
                    if line == step and column != (self.m - step - 1):
                        new_matrix.matrix[line][column] = self.matrix[line][column + 1]
                    elif line != (self.n - step - 1) and column == (self.m - step - 1):
                        new_matrix.matrix[line][column] = self.matrix[line + 1][column]
                    elif line == (self.n - step - 1) and column != step:
                        new_matrix.matrix[line][column] = self.matrix[line][column - 1]
                    elif line != step and column == step:
                        new_matrix.matrix[line][column] = self.matrix[line - 1][column]
                    else:
                        new_matrix.matrix[line][column] = self.matrix[line][column]

        self.matrix = new_matrix.matrix


    def cyclic_shift_v2(self):
        new_matrix = Matrix(self.m, self.n)
        for step in range(min(self.n, self.m) // 2):
            for column in range(step, self.n - 1 - step):
                new_matrix.matrix[step][column] = self.matrix[step][column + 1]
                new_matrix.matrix[self.m - 1 - step][self.n - 1 - column] = self.matrix[self.m - 1 - step][self.n - 1 - column - 1]
            for line in range(step, self.m - 1 - step):
                new_matrix.matrix[line + 1][step] = self.matrix[line][step]
                new_matrix.matrix[line][self.n - 1 - step] = self.matrix[line + 1][self.n - 1 - step]
                
        if self.m > self.n and self.n % 2 == 1:
            for line in range(self.n // 2, self.m - self.n // 2):
                new_matrix.matrix[line][self.n // 2] = self.matrix[line][self.n // 2]
        elif self.m < self.n and self.m % 2 == 1:
            for column in range(self.m // 2, self.n - self.m // 2):
                new_matrix.matrix[self.m // 2][column] = self.matrix[self.m // 2][column]
        elif self.m == self.n and self.m % 2 == 1:
            new_matrix.matrix[self.m // 2][self.n // 2] = self.matrix[self.m // 2][self.n // 2]

        self.matrix = new_matrix.matrix


def fill_function(i, j, m, n):
    return (i * m + (j + 1))


def main():
    m = 3  # int(input("Input rows count: "))
    n = 10  # int(input("Input columns count: "))
    mat = Matrix(m, n, fill_function=fill_function)
    print(*mat.matrix, sep="\n", end="\n\n")
    mat.cyclic_shift_v2()
    print(*mat.matrix, sep="\n")


if __name__ == "__main__":
    main()