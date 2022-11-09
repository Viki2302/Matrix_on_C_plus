#include "s21_matrix_oop.h"

void S21Matrix::print() {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      getMatrix(i, j);
      cout << matrix_[i][j] << " ";
    }
    cout << endl;
  }
  this->getRows();
  this->getCols();
}

void S21Matrix::setRows(int value) {
  if (value <= 0) {
    throw std::length_error("Rows is less or equal 0");
  }
  S21Matrix temp(value, this->cols_);
  int min_rows = this->rows_;
  if (value < this->rows_) {
    min_rows = value;
  }

  for (int i = 0; i < min_rows; i++) {
    for (int j = 0; j < this->cols_; j++) {
      temp.matrix_[i][j] = this->matrix_[i][j];
    }
  }
  *this = temp;
}

void S21Matrix::setCols(int value) {
  if (value <= 0) {
    throw std::length_error("Rows is less or equal 0");
  }
  S21Matrix temp(this->rows_, value);
  if (value < this->cols_) {
    this->cols_ = value;
  }
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      temp.matrix_[i][j] = this->matrix_[i][j];
    }
  }
  *this = temp;
}

int S21Matrix::getRows() { return this->rows_; }

int S21Matrix::getCols() { return this->cols_; }

void S21Matrix::setMatrix(int value, int i, int j) {
  this->matrix_[i][j] = value;
}
int S21Matrix::getMatrix(int i, int j) { return matrix_[i][j]; }

// конструкторы и деструкторы
// Конструктор по умолчанию
S21Matrix::S21Matrix() {
  // matrix_.S21
  this->rows_ = 0;
  this->cols_ = 0;
  this->matrix_ = nullptr;
}

// параметризованный конструктор
S21Matrix::S21Matrix(int rows, int cols) {
  this->rows_ = rows;
  this->cols_ = cols;
  if (rows <= 0 && cols <= 0) {
    throw std::runtime_error("Rows and Columns equal 0!!!!");
  }
  this->SetEmptyMatrix();
}

void S21Matrix::SetEmptyMatrix() {
  if (rows_ >= 0 && cols_ >= 0) {
    this->matrix_ = new double*[rows_]();
    for (int i = 0; i < rows_; i++) {
      this->matrix_[i] = new double[cols_]();
    }
  } else {
    throw("Error!\nInvalid value rows or cols\n");
  }
}

// конструктор копирования
S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  // this->rows_ = other.rows_;
  // this->cols_ = other.cols_;
  this->SetEmptyMatrix();
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

// конструктор перемещения
S21Matrix::S21Matrix(S21Matrix&& other) {
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  this->matrix_ = other.matrix_;

  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

// Деструктор
S21Matrix::~S21Matrix() { this->CleanMatrix(); }

void S21Matrix::CleanMatrix() {
  if ((rows_ > 0 || cols_ > 0) && matrix_ != nullptr) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }

    delete[] matrix_;
    matrix_ = nullptr;
    rows_ = 0;
    cols_ = 0;
  }
}

// некоторые операторы перегружаются
// Присвоение матрице значений другой матрицы
S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  this->IncorrectMatrix();

  if (this != &other) {
    if (this->matrix_ != nullptr) {
      this->CleanMatrix();
    }

    this->cols_ = other.cols_;
    this->rows_ = other.rows_;
    this->SetEmptyMatrix();

    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }

  return *this;
}

// Индексация по элементам матрицы (строка, колонка)
double& S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return this->matrix_[row][col];
}

double& S21Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return this->matrix_[row][col];
}

// Проверка на равенство матриц (eqmatrix)
bool S21Matrix::operator==(const S21Matrix& other) {
  // S21Matrix res(*this);
  return this->EqMatrix(other);
}

// Присвоение сложения (summatrix)
S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

// Сложение двух матриц
S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix res(*this);
  res.SumMatrix(other);
  return res;
}

// Присвоение разности (submatrix)
S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

// Вычитание одной матрицы из другой
S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix res(*this);
  res.SubMatrix(other);
  return res;
}

// Умножение матриц и умножение матрицы на число
S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix res(*this);
  res.MulMatrix(other);
  return res;
}

// Присвоение умножения (mulmatrix/MulNumber)
S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

// Умножение матриц и умножение матрицы на число
S21Matrix S21Matrix::operator*(double number) {
  S21Matrix res(*this);
  res.MulNumber(number);
  return res;
}

// Присвоение умножения (mulmatrix/MulNumber)
S21Matrix& S21Matrix::operator*=(double number) {
  MulNumber(number);
  return *this;
}

// операций над матрицами
// Проверяет матрицы на равенство между собой
bool S21Matrix::EqMatrix(const S21Matrix& other) {
  IncorrectMatrix();

  if (rows_ == other.rows_ && cols_ == other.cols_) {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 0.0000001) {
          return false;
        }
      }
    }
  } else {
    throw std::range_error("Error!\nIncorrect matrix_");
  }

  return true;
}

// Прибавляет вторую матрицы к текущей
void S21Matrix::SumMatrix(const S21Matrix& other) {
  IncorrectMatrix();

  if (rows_ > 0 && other.rows_ > 0 && cols_ > 0 && other.cols_ > 0) {
    if ((rows_ == other.rows_) && (cols_ == other.cols_)) {
      for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
          this->matrix_[i][j] = other.matrix_[i][j] + this->matrix_[i][j];
        }
      }

    } else {
      throw(std::range_error("Error!\nIncorrect matrix_"));
    }
  } else {
    throw(std::range_error("Error!\nIncorrect matrix_"));
  }
}

// Вычитает из текущей матрицы другую
void S21Matrix::SubMatrix(const S21Matrix& other) {
  IncorrectMatrix();

  if (rows_ > 0 && other.rows_ > 0 && cols_ > 0 && other.cols_ > 0) {
    if ((this->cols_ == other.rows_)) {
      for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
          this->matrix_[i][j] = this->matrix_[i][j] - other.matrix_[i][j];
        }
      }

    } else {
      throw(std::range_error("Error!\nIncorrect matrix_"));
    }
  } else {
    throw(std::range_error("Error!\nIncorrect matrix_"));
  }
}

// Умножает текущую матрицу на число
void S21Matrix::MulNumber(const double num) {
  IncorrectMatrix();

  if (rows_ > 0 && cols_ > 0) {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] = matrix_[i][j] * num;
      }
    }

  } else {
    throw(std::range_error("Error!\nIncorrect matrix_"));
  }
}

// Умножает текущую матрицу на вторую
void S21Matrix::MulMatrix(const S21Matrix& other) {
  IncorrectMatrix();

  if (rows_ > 0 && other.rows_ > 0 && cols_ > 0 && other.cols_ > 0) {
    if ((cols_ == other.rows_)) {
      S21Matrix result(rows_, other.cols_);
      for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < other.cols_; j++) {
          for (int k = 0; k < cols_; k++) {
            result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
          }
        }
      }
      *this = result;

    } else {
      throw(std::range_error("Error!\nIncorrect matrix_"));
    }
  } else {
    throw(std::range_error("Error!\nIncorrect matrix_"));
  }
}

// Создает новую транспонированную матрицу из текущей и возвращает ее
S21Matrix S21Matrix::Transpose() {
  IncorrectMatrix();

  if (rows_ > 0 && cols_ > 0) {
    S21Matrix result(cols_, rows_);
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        result.matrix_[j][i] += this->matrix_[i][j];
      }
    }
  } else {
    throw(std::range_error("Error!\nIncorrect matrix_"));
  }

  return *this;
}

S21Matrix S21Matrix::Minor(int index_row, int index_column) {
  S21Matrix Result(rows_ - 1, cols_ - 1);
  int res_i = 0;
  for (int i = 0; i < Result.rows_; ++i) {
    if (i == index_row) {
      res_i = 1;
    }
    int res_j = 0;
    for (int j = 0; j < Result.cols_; ++j) {
      if (j == index_column) {
        res_j = 1;
      }
      Result.matrix_[i][j] = this->matrix_[i + res_i][j + res_j];
    }
  }
  return Result;
}

// Вычисляет матрицу алгебраических дополнений текущей матрицы и возвращает
S21Matrix S21Matrix::CalcComplements() {
  // S21Matrix mat(*this);
  S21Matrix determ(rows_ - 1, cols_ - 1);
  S21Matrix result(rows_, cols_);
  IncorrectMatrix();

  if (!matrix_ && rows_ < 1 && cols_ < 1) {
    throw(std::range_error("Error!\nIncorrect matrix_"));
  }
  if (rows_ != cols_) {
    throw(std::range_error("Error!\nIncorrect matrix_"));
  } else {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        determ = this->Minor(i, j);
        result.matrix_[i][j] = pow(-1, i + j) * determ.Determinant();
      }
    }
  }

  return result;
}

// Вычисляет и возвращает определитель текущей матрицы
double S21Matrix::Determinant() {
  IncorrectMatrix();

  // S21Matrix minor(this->rows_ - 1, this->cols_ -1);
  S21Matrix Result(rows_ - 1, cols_ - 1);

  double result = 0.0;
  if (rows_ > 0 && cols_ > 0) {
    if (rows_ != cols_) {
      throw(std::range_error("Error!\nIncorrect matrix_"));
    } else if (rows_ == 1) {
      result = this->matrix_[0][0];
    } else if (rows_ == 2 && cols_ == 2) {
      result = this->matrix_[0][0] * this->matrix_[1][1] -
               this->matrix_[0][1] * this->matrix_[1][0];
    } else {
      for (int j = 0; j < rows_; ++j) {
        Result = this->Minor(0, j);
        Result.Determinant();
        result += pow(-1, j) * this->matrix_[0][j] * Result.Determinant();
      }
    }
  } else {
    throw(std::range_error(std::range_error("Error!\nIncorrect matrix_")));
  }

  return result;
}

// Вычисляет и возвращает обратную матрицу
S21Matrix S21Matrix::InverseMatrix() {
  IncorrectMatrix();

  S21Matrix result(rows_, cols_);
  double determin = 0.0;
  if (rows_ > 0 && cols_ > 0) {
    if (rows_ != cols_) {
      throw(std::range_error("Error!\nIncorrect matrix_"));
    } else if (rows_ == 1) {
      result.matrix_[0][0] = matrix_[0][0];
    } else {
      determin = this->Determinant();
      result = this->CalcComplements();
      result = result.Transpose();
      result.MulNumber((1.0 / determin));
      // result *= 1.0 / determin;
    }
  } else {
    throw(std::range_error("Error!\nIncorrect matrix_"));
  }

  return result;
}

void S21Matrix::IncorrectMatrix() const {
  if (this->matrix_ == nullptr || this->rows_ < 0 || this->cols_ < 0) {
    throw(std::range_error("Error!\nIncorrect matrix_"));
  }
}

// int main() {

//     S21Matrix x(3, 3);
//     S21Matrix y(3, 3);

//     y.setMatrix(2, 0, 0);
//     y.setMatrix(5, 0, 1);
//     y.setMatrix(7, 0, 2);
//     y.setMatrix(6, 1, 0);
//     y.setMatrix(3, 1, 1);
//     y.setMatrix(4, 1, 2);
//     y.setMatrix(5, 2, 0);
//     y.setMatrix(-2, 2, 1);
//     y.setMatrix(-3, 2, 2);
//     y.print();
//     x= y.CalcComplements();
//     //cout << d << " ";
//     x.print();

//   return 0;
// }