#include <stdio.h>
#include <math.h>

struct Userdata
{
    const char * name;
    int age;
    float growth, weight;
};


int main() {
    const char buffer[10];
    struct Userdata user1;
    user1.name = buffer;
    void *p = &user1;

    //  scanf("%s\n%d\n%f\n%f", &buffer, &user1.age, &user1.growth, &user1.weight);
    //  printf("%s\n%d\n%f\n%f\n", user1.name, user1.age, user1.growth, user1.weight);

    scanf("%s\n%d\n%f\n%f", *(const char **)p, p + 8, p + 12, p + 16);
    printf("%s\n%d\n%f\n%f\n", user1.name, user1.age, user1.growth, user1.weight);

    return 0;
}