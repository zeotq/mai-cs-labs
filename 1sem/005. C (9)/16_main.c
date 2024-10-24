#include <stdio.h>
#include <math.h>


typedef struct {
    int index;      // Номер точки
    int isGood;     // Удовлетворяет ли точка условию
    float x;        // Координата X
    float y;        // Координата Y
    float l;        // Параметр L
} point;

int isPointInArea(double i, double j) {
    if ((i + j + 10 <= 0) && (i + j + 20 >= 0)) {
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

point (*points())[51] {
    double i = -30, j = -4, l = 12;
    int k = 0;
    static int max_k = 51;
    static point shoots_log[51];

    while (k < max_k) {
        shoots_log[k].index = k; shoots_log[k].x = i; shoots_log[k].y = j;  shoots_log[k].l = l;
        shoots_log[k].isGood = isPointInArea(i, j);

        if (k == max_k) {
            break;
        }

        double iOld = i, jOld = j;
        i = fabs(iOld - l) + min(mod(jOld, 10), mod(l + k, 10)) - 20;       
        j = mod(max(k - iOld, min(jOld, max(iOld - l, jOld - l))), 30);
        l = mod(pow(l, 2), 20) - mod(max(iOld, jOld), k + 1);
        k += 1;
    }
    return &shoots_log;
}

int main() {
    point (*log)[51] = points();
    int hits_counter = 0;
    for (int i = 0; i < 51; i ++) {
        if ((*log)[i].isGood == 1) {
            printf("\e[3;32mHit %d ", hits_counter + 1);
            hits_counter += 1;
        } else {
            printf("\e[3;31mMiss ");
        }
        printf("on step %d, pos_i = %f, pos_j = %f, l = %f\n\e[0m", (*log)[i].index, (*log)[i].x, (*log)[i].y, (*log)[i].l);
    } 

    if  (hits_counter != 0) {
        printf("\e[1;32mThe end! Total hits: %d\n\e[0m" , hits_counter);
    } else {
        printf("\e[1;33mMissed due to formula!\n\e[0m");
    }
    
    return 0;
}