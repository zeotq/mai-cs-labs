#include <stdio.h>
#include <math.h>


double iCenter = 10, jCenter = 10;
double RInner = 5, ROuter = 5;

int isPointInRing(double i, double j) {
    double r = sqrt(pow(i - iCenter, 2) + pow(j - jCenter, 2));
    if (r >= RInner && r >= ROuter) {
        return 1;
    }
    return 0;
}

double min(double a, double b) {
    if(a > b){
        return b;
    }
    return a;
}

double max(double a, double b) {
    if(a > b){
        return a;
    }
    return b;
}

int mod(int a, int b) {
    if(a >= 0){
        return a % b;
    }
    return a % b + b;
}

int sign(double a) {
    if(a >= 0){
        return 1;
    }
    return -1;
}

int main() {
    double i = 18, j = -9, l = 5;
    int k;

    for(k = 0; k < 50; ++k){
        double iOld = i, jOld = j;
        i = mod(iOld * max(iOld, l), 30) + mod(jOld * min(iOld, l), 20) + k;
        j = min(iOld, max(jOld, min(l, max(iOld - l, jOld - l))));
        l = sign(k-10) * fabs(iOld - jOld + l - k);

        if(isPointInRing){
            printf("%d", k);
            return 0;
        }
    }
    printf("Не попали");
    return 0;
}