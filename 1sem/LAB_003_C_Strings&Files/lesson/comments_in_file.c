#include <stdlib.h>
#include <stdio.h>

int isSpace(char c) {
  return (c == ' ') || (c == '\t') || (c == '\n'); // Проверяем закончилась ли строка
}

int main(int argc, char * argv[]) {
    // Проверка ввода
    if(argc < 3) {
        printf("Error: 2 file names were expected, but were received %d\n", argc - 1);
        exit(-1);
    }

    const char * inputFileName = argv[1];
    const char * outputFileName = argv[2];

    FILE * file = fopen(inputFileName, "r");
    FILE * outFile = fopen(outputFileName, "w");

    if(file == NULL) {
        printf("Error: cant open file %s\n", inputFileName);
        exit(1);
     }

    if(outFile == NULL) {
        printf("Error: cant open outFile %s\n", outputFileName);
        exit(1);
    }

    size_t counter = 0;
    int inComment = 0;

    char c = 0, cPrev = 0;
    while (!feof(file))
    {
        cPrev = c;
        c = fgetc(file);

        if(!inComment && c == '/' && cPrev == '/') {
            fputc('/', outFile);
            inComment = 1;
        } else if (inComment && isSpace(c) && !isSpace(cPrev) && cPrev != '/') {
            ++counter;
            if (c == '\n') {
                inComment = 0;
                fputc('\n', outFile);
            }
        } else if (inComment && isSpace(c) && isSpace(cPrev))  {
            fputc(' ', outFile);
        }

        if(inComment) {
            fputc(c, outFile);
        }
    }

    printf("Words in %s: %zu\n", inputFileName, counter);
    fclose(file);
    fclose(outFile);

    return 0;
}