#include <stdio.h>
#include "math.c"

double sum(double a, double b) {
    return a + b;
}

double divide(double a, double b) {
    return a / b;
}

double mult(double a, double b);
/* 
Объявили функцию, определенную в math.c
math.c можно не подключать, но придётся 
компилировать параллельно файл и файл зависимость
для линковки таблиц имен
*/

int main() {
    int n;
    double m;

    scanf("%d,%lf", &n, &m);

    printf("Hello world!\n");
    printf("%d\n", n);
    printf("%f\n", m);
    printf("sum of %d and %f = %f\n", n, m, sum(n, m));
    printf("%d / %f = %f\n", n, m, divide(n, m));
    printf("%d * %f = %f\n", n, m, mult(n, m));

    if(n > m){
        printf("n>m\n");
    } else if(m > n){
        printf("m>n\n");
    } else{
        printf("n=m\n");
    }

    printf("%d * %f = %f\n", n, m, mult(n, m));

    return 0;
}