#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

class Quadrat {
protected:
    unsigned** matrix;
    int row;
    int col;
    int side;
public:
    Quadrat(int);
    ~Quadrat();
};

class Magic : public Quadrat {
public:
    Magic(int n) : Quadrat(n) {};
    void print();
    void test();
    void bashe();
private:
    int length();
    int move(int);
    bool check_line(int, int);
    bool check_diagonal();
};

// конструктор квадрата
Quadrat::Quadrat(int n) { 
    side = n;
    matrix = new unsigned* [side];
    for (row = 0; row < side; row++)
        matrix[row] = new unsigned[side];
    for (row = 0; row < side; row++)
        for (col = 0; col < side; col++)
            matrix[row][col] = 0;
}

// деструктор квадрата
Quadrat::~Quadrat() {
    for (row = 0; row < side; row++)
        delete[] matrix[row];
    delete[] matrix;
}

// макс кол-во цифр в ячейке таблицы
int Magic::length() {
    int area;
    int len = 0;
    area = (side * side);
    while (area > 0) {
        area /= 10;
        len++;
    }
    return(len);
}

// вывод матрицы
void Magic::print() {
    int len = 0;
    putchar('\n');
    len = length();
    for (row = 0; row < side; row++) {
        for (col = 0; col < side; col++)
            printf("%0*d ", len, matrix[row][col]);
        putchar('\n');
    }
    putchar('\n');
}

// проверка ячейки (выходит ли за пределы)
int Magic::move(int k) {
    if (k < 0)
        return(k + side);
    if (k > (side - 1))
        return(k - side);
    return k;
}

// террасы Баше с нижней строки справа налево
void Magic::bashe() {
    int i;
    int j;
    int area = (side * side);
    int z = 1;
    row = (side / 2);
    col = (side - (side / 2)) - 2;
    matrix[row][col] = z;
    while (z < area)
    {
        i = move(row + 1);
        j = move(col - 1);
        if (matrix[i][j] > 0)
        {
            i = move(row);
            j = move(col - 2);
        }
        row = i; col = j;
        ++z;
        matrix[row][col] = z;
    }
}

// тесты
bool Magic::check_line(int i, int j) {
    int s, temp;
    bool result = true;
    for (i = 0; i < side; i++) {
        s = 0;
        for (j = 0; j < side; j++)
            s += matrix[i][j];
        if ((i != 0) && ((temp == s) == 0)) return 0;
        temp = s;
    }
    return result;
}

bool Magic::check_diagonal() {
    int s[2] = { 0 };
    int loc = (side - 1); 
    for (row = col = 0; row < side; row++, col++, loc--) {
        s[0] += matrix[row][col];
        s[1] += matrix[row][loc];
    }
    return(s[0] == s[1]);
} 

void Magic::test() {
    if (check_line(row, col) && check_line(col, row) && check_diagonal())
        cout << "Magic test passed" << endl;
    else
        cout << "Magic test failed" << endl;
}

// основная ф-ция
int main(int argc, char* argv[]) {
    int n;
    n = atoi(argv[1]);
    if ((n % 2) == 0) {
        cout << "Not an odd number!" << endl;
        return -1;
    }
    n = (n < 0) ? -n : n;
    Magic mag(n);
    mag.bashe();
    mag.print();
    mag.test();
    return 0;
}