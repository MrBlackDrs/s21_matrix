#ifndef S21_MATRIX_OOP
#define S21_MATRIX_OOP

#include <cmath>
#include <iostream>

class S21Matrix {
 private:
  // Attributes
  int rows_, cols_;
  double **matrix_;
  // Methods
  void InitMatrix(int rows, int cols);
  void CopyMatrix(const S21Matrix &other);
  double Determinant2x2();
  S21Matrix Calc_submatrix(int ind_i, int ind_j);

 public:
  // creation and deletion
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other);
  ~S21Matrix();

  // setter getter (rows, coloumns)
  int GetRows();
  int GetCols();
  void SetRows(int new_rows);
  void SetCols(int new_cols);
  double &operator()(int rows, int cols);
  S21Matrix &operator=(S21Matrix &other);
  S21Matrix &operator=(S21Matrix &&other);

  // own functions
  void SetValue(double val, int i, int j);
  double GetValue(int i, int j);
  void PrintMatrix();

  // Methods
  bool EqMatrix(const S21Matrix &other);
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  // Overload
  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator*(const double num);
  bool operator==(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(double num);
  friend S21Matrix operator*(double num, const S21Matrix &other);
};

// input
void InputMatrix(S21Matrix &matrix, int a, int b);

#endif