#include <stdlib.h>
#include <stdio.h>


int main() {
    unsigned long long n;
    unsigned int Dict[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    unsigned int numSys = 10;

    scanf("%lld", &n);    
    while (n > 0)
    {
        Dict[(n % numSys)] += 1;
        n = n / numSys;
    }
    
    int flag = 0;
    for (int i = 0; i < 10; ++i) {
        if (Dict[i]) {
            printf("\e[4;32m%d - %d\n", i, Dict[i]);
        } else {
            flag = 1;
            printf("\e[4;31m%d - %d\n", i, Dict[i]);
        }
    }

    if (flag) {
        printf("\e[4;32mYes!\e[0;0m\n");
    } else {
        printf("\e[4;31mNo!\e[0;0m\n");
    }
    
    return 0;
}