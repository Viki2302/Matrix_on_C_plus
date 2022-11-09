#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <iostream>
// #include <stdio.h>
// #include <stdlib.h>
#include <math.h>

using std::cout;
using std::endl;

class S21Matrix {
 private:
  // Атрибуты
  int rows_, cols_;  // Строки и столбцы
  double** matrix_;  // Указатель на память, где размещена матрица

  S21Matrix Minor(int index_row, int index_column);

  void IncorrectMatrix() const;
  void SetEmptyMatrix();
  void CleanMatrix();

 public:
  void print();

  void setRows(int value);
  int getRows();

  void setCols(int value);
  int getCols();

  void setMatrix(int value, int i, int j);
  int getMatrix(int i, int j);

  // конструкторы и деструкторы
  S21Matrix();  // Конструктор по умолчанию
  S21Matrix(int rows_, int cols_);  // параметризованный конструктор
  S21Matrix(const S21Matrix& other);  // конструктор копирования
  S21Matrix(S21Matrix&& other);  // конструктор перемещения
  ~S21Matrix();                  // Деструктор

  // некоторые операторы перегружаются
  S21Matrix& operator=(
      const S21Matrix& other);  // Присвоение матрице значений другой матрицы
  double& operator()(
      int row, int col);  // Индексация по элементам матрицы (строка, колонка)
  double& operator()(int row, int col) const;
  bool operator==(
      const S21Matrix& other);  // Проверка на равенство матриц (eq_matrix)
  S21Matrix& operator+=(
      const S21Matrix& other);  // Присвоение сложения (sum_matrix)
  S21Matrix operator+(const S21Matrix& other);  // Сложение двух матриц
  S21Matrix& operator-=(
      const S21Matrix& other);  // Присвоение разности (sub_matrix)
  S21Matrix operator-(
      const S21Matrix& other);  // Вычитание одной матрицы из другой
  S21Matrix operator*(
      const S21Matrix& other);  // Умножение матриц и умножение матрицы на число
  S21Matrix& operator*=(
      const S21Matrix& other);  // Присвоение умножения (mul_matrix/mul_number)
  S21Matrix operator*(
      double number);  // Умножение матриц и умножение матрицы на число
  S21Matrix& operator*=(
      double number);  // Присвоение умножения (mul_matrix/mul_number)

  // операций над матрицами
  bool EqMatrix(
      const S21Matrix& other);  // Проверяет матрицы на равенство между собой
  void SumMatrix(
      const S21Matrix& other);  // Прибавляет вторую матрицы к текущей
  void SubMatrix(const S21Matrix& other);  // Вычитает из текущей матрицы другую
  void MulNumber(const double num);  // Умножает текущую матрицу на число
  void MulMatrix(const S21Matrix& other);  // Умножает текущую матрицу на вторую
  S21Matrix Transpose();  // Создает новую транспонированную матрицу из текущей
                          // и возвращает ее
  S21Matrix CalcComplements();  // Вычисляет матрицу алгебраических дополнений
                                // текущей матрицы и возвращает ее
  double Determinant();  // Вычисляет и возвращает определитель текущей матрицы
  S21Matrix InverseMatrix();  // Вычисляет и возвращает обратную матрицу
};

#endif  // SRC_S21_MATRIX_H_
