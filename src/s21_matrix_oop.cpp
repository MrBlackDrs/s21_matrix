#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() { InitMatrix(1, 1); }

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows > 0 && cols > 0)
    InitMatrix(rows, cols);
  else {
    rows_ = 0;
    cols_ = 0;
    matrix_ = nullptr;
    throw std::invalid_argument("\n rows and colomns must be positive\n");
  }
}

S21Matrix::S21Matrix(const S21Matrix &other) {
  InitMatrix(other.rows_, other.cols_);
  CopyMatrix(other);
}

S21Matrix::S21Matrix(S21Matrix &&other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
  matrix_ = nullptr;
  rows_ = 0;
  cols_ = 0;
}

void S21Matrix::InitMatrix(int rows, int cols) {
  // проверить строчки и столбцы
  rows_ = rows;
  cols_ = cols;
  matrix_ = new double *[rows_]();
  for (int i = 0; i < rows; ++i) {
    matrix_[i] = new double[cols_]();
  }
}

void S21Matrix::CopyMatrix(const S21Matrix &other) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

int S21Matrix::GetRows() { return rows_; }

int S21Matrix::GetCols() { return cols_; }

void S21Matrix::SetValue(double val, int i, int j) { matrix_[i][j] = val; }

double S21Matrix::GetValue(int i, int j) {
  if (matrix_ && i < rows_ && j < cols_)
    return matrix_[i][j];
  else
    throw std::range_error("\nlist index out of range\n");
}

void S21Matrix::SetRows(int new_rows) {
  S21Matrix mutated(new_rows, cols_);
  int stop_index = fmin(mutated.rows_, rows_);
  for (int i = 0; i < stop_index; i++) {
    for (int j = 0; j < cols_; j++) {
      mutated.matrix_[i][j] = matrix_[i][j];
    }
  }
  this->~S21Matrix();
  *this = mutated;
}

void S21Matrix::SetCols(int new_cols) {
  S21Matrix mutated(rows_, new_cols);
  int stop_index = fmin(new_cols, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < stop_index; j++) {
      mutated.matrix_[i][j] = matrix_[i][j];
    }
  }
  this->~S21Matrix();
  *this = mutated;
}

double &S21Matrix::operator()(int rows, int cols) {
  if (rows < rows_ && cols < cols_)
    return matrix_[rows][cols];
  else
    throw std::invalid_argument("\nIndex out of range\n");  // error
}

S21Matrix &S21Matrix::operator=(S21Matrix &other) {
  if (this == &other) return *this;
  delete[] matrix_;
  InitMatrix(other.rows_, other.cols_);
  CopyMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) {
  if (this != &other) delete[] matrix_;
  // *this = other;
  // other.matrix_ = nullptr;
  // return *this;
  matrix_ = other.matrix_;
  cols_ = other.cols_;
  rows_ = other.rows_;
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
  return *this;
}

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool code = true;
  if (cols_ != other.cols_ || rows_ != other.rows_) {
    code = false;
  } else {
    for (int i = 0; i < rows_ && code; i++) {
      for (int j = 0; j < cols_ && code; j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) >= 1e-6) {
          code = false;
        }
      }
    }
  }
  return code;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (cols_ != other.cols_ || rows_ != other.rows_)
    throw std::logic_error("\nIncomparable dimensions of matrix\n");
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (cols_ != other.cols_ || rows_ != other.rows_)
    throw std::logic_error("\nIncomparable dimensions of matrix\n");
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "\nColoumns of first matrix must be equal to rows of another matrix\n");
  }
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++)
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
    }
  }
  *this = std::move(result);
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

double S21Matrix::Determinant2x2() {
  if (rows_ == 2 && cols_ == 2)
    return matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1];
  else
    throw std::logic_error("\nIncorrect use of det2x2\n");
}

S21Matrix S21Matrix::Calc_submatrix(int ind_i, int ind_j) {
  S21Matrix result(rows_ - 1, cols_ - 1);
  for (int i = 0, k = 0; i < rows_; i++) {
    if (i == ind_i) continue;
    for (int j = 0, m = 0; j < cols_; j++) {
      if (j == ind_j) continue;
      result.matrix_[k][m] = matrix_[i][j];
      m++;
    }
    k++;
  }
  return result;
}

double S21Matrix::Determinant() {
  double result = 0;
  double buf = 0;
  bool code = true;

  // проверка на квадратную матрицу
  if (rows_ != cols_) {
    code = false;
    throw std::invalid_argument("\nMatrix must be square!\n");
  }

  // проверка на матрицу из 1 элемента
  if (rows_ == 1 && cols_ == 1) {
    result = matrix_[0][0];
  }

  else if (code) {
    if (rows_ == 2 && cols_ == 2) {
      return Determinant2x2();
    }
    for (int i = 0; i < cols_; i++) {
      S21Matrix minor;
      minor = Calc_submatrix(0, i);
      buf = minor.Determinant();
      minor.~S21Matrix();
      result += (i % 2 == 0 ? 1 : -1) * matrix_[0][i] * buf;
    }
  }

  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  // проверка на матрицу из 1 элемента, для нее не существует дополнения
  if (rows_ == 1 && cols_ == 1)
    throw std::invalid_argument(
        "\nCan not calculate Complements for single matrix\n");
  // проверка на квадратную матрицу
  if (rows_ != cols_) {
    throw std::invalid_argument("\nMatrix must be square!\n");
  }
  S21Matrix result(rows_, cols_);
  S21Matrix minor(rows_ - 1, cols_ - 1);
  double buf = 0;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      minor = Calc_submatrix(i, j);
      buf = minor.Determinant();
      result.matrix_[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * buf;
      buf = 0;
    }
  }
  minor.~S21Matrix();
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  // проверка на квадратную матрицу
  if (rows_ != cols_) {
    throw std::invalid_argument("\nMatrix must be square!\n");
  }

  S21Matrix result(rows_, cols_);
  // проверка на матрицу из 1 элемента, для нее обртаная: 1/А
  if (rows_ == 1 && cols_ == 1) {
    if (matrix_[0][0] != 0.0)
      result.matrix_[0][0] = 1 / matrix_[0][0];
    else
      throw std::runtime_error("\nDivision by zero\n");
  } else {
    double det = Determinant();
    if (det != 0.0) {
      S21Matrix buf1(rows_, cols_);
      S21Matrix buf2(rows_, cols_);
      buf1 = CalcComplements();
      buf2 = buf1.Transpose();
      buf2.MulNumber((1 / det));
      result = std::move(buf2);
      buf1.~S21Matrix();
    } else
      throw std::runtime_error("\nDivision by zero\n");
  }
  return result;
}

// input output
void InputMatrix(S21Matrix& matrix, int a, int b) {
  double val;
  for (int i = 0; i < a; i++) {
    std::cout<<"row "<<i+1<<": ";
    for (int j = 0; j < b; j++) {
      std::cin >> val;
      matrix.SetValue(val, i, j);
    }
    // std::cout<<std::endl;
  }
}

void S21Matrix::PrintMatrix() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      std::cout.precision(7);
      std::cout<< matrix_[i][j] << " ";
    }
    std::cout << "\n";
  }
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

bool S21Matrix::operator==(const S21Matrix &other) { return EqMatrix(other); }

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(double num) {
  MulNumber(num);
  return *this;
}

S21Matrix operator*(double num, const S21Matrix &other) {
  S21Matrix result(other);
  result.MulNumber(num);
  return result;
}