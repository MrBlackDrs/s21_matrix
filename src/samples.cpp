#include "s21_matrix_oop.h"

using namespace std;

int main() {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);
  S21Matrix C;
  // операции над одной матрицей
  cout << "Введите первую матрицу" << endl;
  InputMatrix(A, 2, 2);

  cout << "Умножение матрицы на 5" << endl;
  C = A * 5;
  C.PrintMatrix();

  cout << "Определитель матрицы" << endl;
  cout << A.Determinant() << endl;

  cout << "Транспонирование матрицы" << endl;
  C = A.Transpose();
  C.PrintMatrix();

  cout << "Обратная матрица" << endl;
  C = A.InverseMatrix();
  C.PrintMatrix();

  // операции над 2 матрицами
  cout << "Введите вторую матрицу" << endl;
  InputMatrix(B, 2, 2);

  cout << "Сложение матриц" << endl;
  C = A + B;
  C.PrintMatrix();
  cout << "Вычитание матриц" << endl;
  C = A - B;
  C.PrintMatrix();
  cout << "Умножение матриц" << endl;
  C = A * B;
  C.PrintMatrix();

  return 0;
}