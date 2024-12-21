#include <stdio.h>
#include <math.h>

int len(int n, int base) {
    if(n < 0)
        n *= -1;
    int cnt = 0;
    while (n > 0)
    {
        n  /= base;
        ++cnt;
    }
    return cnt;
}

int getAt(int n, int i, int base ) {
    int l = len(n, base);
    return n % (int)pow(base, l - i) / (int)(pow(base, l - i - 1));
}

int setAt(int n, int i, int d, int base) {
    int l = len(n, base);
    int dOld = getAt(n, i, base);

    return (n - dOld * pow(base, l - i - 1)) + d * pow(base, l - i - 1);
}

int isPalindrom(int n, int base) {
    int l = 0;
    int r = len(n, base) - 1;

    while (l < r)
    {
        if(getAt(n, l, base) != getAt(n, r, base))
            return 0;
        ++l;
        --r;
    }
    return 1;
    
}

int main() {
    int n = 12321;
    printf("%d\n", isPalindrom(n, 10));

    return 0;
}