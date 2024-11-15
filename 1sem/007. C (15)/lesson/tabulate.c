#include <stdio.h>
#include <math.h>

int fact(int n) {
    if(n <= 1)
        return 1;
    return n*fact(n - 1);
}

long long int fackt(int n) {
    if(n <= 1)
        return 1;
    return n*fackt(n - 1);
}

int sqr(int n) {
    return n * n;
}

void tabulate(int(*p_f)(int), int a, int b) {
    for(int i = a; i <= b; ++i) {
        printf("%d\t%d\n", i, p_f(i));
    }
}

void tabulate2(long long int(*p_f)(int), int a, int b) {
    for(int i = a; i <= b; ++i) {
        printf("%d\t%lld\n", i, p_f(i));
    }
}

int main() {
    tabulate(sqr, 1, 10);

    tabulate(fact, 1, 25);
    tabulate2(fackt, 1, 25);

    return 0;
}