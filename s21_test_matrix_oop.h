#ifndef SRC_S21_TEST_MATRIX_H_
#define SRC_S21_TEST_MATRIX_H_

#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

class Test : public ::testing::Test {
 protected:
  S21Matrix *x;
  S21Matrix *t1;
  S21Matrix *t2;
  S21Matrix *t3;
  S21Matrix *t4;

 public:
  Test() { /* init protected members here */
  }
  ~Test() { /* free protected members here */
  }

  void SetUp() {
    // cout << "SetUp..." << endl;
    t1 = new S21Matrix(2, 2);
    t2 = new S21Matrix(2, 2);
    t3 = new S21Matrix(3, 2);
    t4 = new S21Matrix(3, 3);

    (*t1)(0, 0) = 1;
    (*t1)(0, 1) = 2;
    (*t1)(1, 0) = 3;
    (*t1)(1, 1) = 4;

    (*t2)(0, 0) = 2;
    (*t2)(0, 1) = 2;
    (*t2)(1, 0) = 2;
    (*t2)(1, 1) = 2;

    (*t3)(0, 0) = 2;
    (*t3)(0, 1) = 2;
    (*t3)(1, 0) = 2;
    (*t3)(1, 1) = 2;
    (*t3)(2, 0) = 2;
    (*t3)(2, 1) = 2;

    (*t4)(0, 0) = 2;
    (*t4)(0, 1) = 5;
    (*t4)(0, 2) = 7;
    (*t4)(1, 0) = 6;
    (*t4)(1, 1) = 3;
    (*t4)(1, 2) = 4;
    (*t4)(2, 0) = 5;
    (*t4)(2, 1) = -2;
    (*t4)(2, 2) = -5;
  }

  void TearDown() {
    // cout << "TearDown..." << endl;
    delete t1;
    delete t2;
    delete t3;
    delete t4;
  }
};

#endif  // SRC_S21_TEST_MATRIX_H_
