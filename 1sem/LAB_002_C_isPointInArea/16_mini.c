#include <stdio.h>
#include <math.h>


double Const1 = 10, Const2 = 20;


int isPointInArea(double i, double j) {
    if (i + j + Const1 <= 0 && i + j + Const2 >= 0) {
        return 1;
    }
    return 0;
}

double min(double a, double b) {
    if(a > b) {
        return b;
    }
    return a;
}

double max(double a, double b) {
    if(a > b) {
        return a;
    }
    return b;
}

int mod(int a, int b) {
    if(a >= 0) {
        return a % b;
    }
    return a % b + b;
}

int sign(double a) {
    if(a >= 0) {
        return 1;
    }
    return -1;
}

int main() {
    double i = -30, j = -4, l = 12;
    int k = 0, max_k = 50, count = 0;
    
    while (k <= max_k) {
        if (isPointInArea(i, j)) {
            printf("Hit %d! ", count);
            count += 1;
        } else {
            printf("Miss! ");
        }
        printf("Step: %d, pos_i = %f, pos_j = %f, l = %f\n", k, i, j, l);

        if (k == max_k) {
            break;
        }

        double iOld = i, jOld = j;
        i = fabs(iOld - l) + min(mod(jOld, 10), mod(l + k, 10)) - 20;       
        j = mod(max(k - iOld, min(jOld, max(iOld - l, jOld - l))), 30);
        l = mod(pow(l, 2), 20) - mod(max(iOld, jOld), k + 1);
        k += 1;
    }

    if (count == 0) {
        printf("Missed due to formula!\n");
    }

    printf("The end! Total hits: %d, Step: %d, EXIT: pos_i = %f, pos_j = %f, l = %f\n", count, k, i, j, l);
    
    return 0;
}