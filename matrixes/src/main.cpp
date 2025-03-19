#include "s21_matrix_oop.h"

int main(void)
{
    S21Matrix a(3, 3);
    double array[] = {-2, 1, -4, 2, 5, -1, 1, 5, -2};
    a.set_matrix(array, sizeof(array) / sizeof(array[0]));
    std::cout << a.Determinant() << std::endl;
}