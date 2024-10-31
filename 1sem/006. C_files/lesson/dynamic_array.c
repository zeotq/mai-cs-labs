#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t allocated = 15;
    char *name = malloc(sizeof(char) * allocated);
    if (name == NULL) {
        fprintf(stderr, "Ошибка выделения памяти.\n");
        return 1;
    }

    size_t i = 0;
    while (scanf("%c", &name[i]) == 1)  // Проверяем, что успешно считали символ
    {
        if (name[i] == '\n') { // Останавливаем считывание при новой строке
            break;
        }
        ++i;
        if (i >= allocated) {
            allocated *= 2;
            char *temp = realloc(name, allocated * sizeof(char));
            if (temp == NULL) {  // Проверка на успешное выделение
                fprintf(stderr, "Ошибка расширения памяти.\n");
                free(name);
                return 1;
            }
            name = temp;
        }
    }
    name[i] = '\0'; // Завершаем строку нулевым символом
    printf("Hello: %s\n", name);
    free(name);

    return 0;
}
