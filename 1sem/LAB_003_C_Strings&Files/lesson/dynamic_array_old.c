#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t allocated = 15;
    char * name = malloc(sizeof(char) * allocated);

    size_t i = 0;
    while (scanf("%c", &name[i]) > 0)
    {
        if (name[i] == '\n') { // Останавливаем считывание при новой строке
            break;
        }
        ++i;
        if (i >= allocated) {
            allocated *= 2;
            name = realloc(name, allocated);
        }
    }
    name[i] = 0;
    printf("Hellow: %s\n", name);
    free(name);

    return 0;
}