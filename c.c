#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Should be 1 argument");
        return -1;
    }
    int index, spaces;
    index = atoi(argv[1]);
    spaces = (2 * index - 1) / 2; // кол-во пробелов перед вершиной
    for (int string = 0; string < index; string++) { // идем по строкам сверху вниз
        for (int i = 0; i < spaces; i++) // пробелы в начале строки
            printf(" ");
        for (int i = 0; i < string + 1; i++) // звездочки
            printf("* ");
        printf("\n");
        spaces--; // для шахматного порядка, на строке ниже будет на 1 пробел меньше
    }
    return 0;
}