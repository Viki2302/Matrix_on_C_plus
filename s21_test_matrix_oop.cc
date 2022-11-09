#include "s21_test_matrix_oop.h"

TEST_F(Test, testSum) {
  S21Matrix expected(2, 2);

  expected(0, 0) = 3;
  expected(0, 1) = 4;
  expected(1, 0) = 5;
  expected(1, 1) = 6;

  ASSERT_EQ((*t1 + *t2).EqMatrix(expected), true);
}

TEST_F(Test, testSub) {
  S21Matrix expected(2, 2);

  expected(0, 0) = -1;
  expected(0, 1) = 0;
  expected(1, 0) = 1;
  expected(1, 1) = 2;

  ASSERT_EQ((*t1 - *t2).EqMatrix(expected), true);
}

TEST_F(Test, testMulNumber) {
  S21Matrix expected(2, 2);

  expected(0, 0) = 4;
  expected(0, 1) = 8;
  expected(1, 0) = 12;
  expected(1, 1) = 16;

  ASSERT_EQ((*t1 * 4).EqMatrix(expected), true);
}

TEST_F(Test, testMulMatrix) {
  S21Matrix expected(2, 2);

  expected(0, 0) = 6;
  expected(0, 1) = 6;
  expected(1, 0) = 14;
  expected(1, 1) = 14;

  ASSERT_EQ(((*t1) * (*t2)).EqMatrix(expected), true);
}

TEST_F(Test, testAssignment) {
  S21Matrix expected(2, 2);

  expected(0, 0) = 3;
  expected(0, 1) = 4;
  expected(1, 0) = 5;
  expected(1, 1) = 6;

  *t1 = expected;

  ASSERT_EQ((*t1).EqMatrix(expected), true);
}

TEST_F(Test, testEqualMatrix) {
  S21Matrix expected(2, 2);

  expected(0, 0) = 3;
  expected(0, 1) = 4;
  expected(1, 0) = 5;
  expected(1, 1) = 6;

  *t1 = expected;

  ASSERT_EQ((*t1).EqMatrix(expected), true);
}

TEST_F(Test, testAssignmentSum) {
  S21Matrix expected(2, 2);

  expected(0, 0) = 3;
  expected(0, 1) = 4;
  expected(1, 0) = 5;
  expected(1, 1) = 6;

  *t1 += *t2;

  ASSERT_EQ((*t1).EqMatrix(expected), true);
}

TEST_F(Test, testAssignmentSub) {
  S21Matrix expected(2, 2);

  expected(0, 0) = -1;
  expected(0, 1) = 0;
  expected(1, 0) = 1;
  expected(1, 1) = 2;

  *t1 -= *t2;

  ASSERT_EQ((*t1).EqMatrix(expected), true);
}

TEST_F(Test, testAssignmentMulNumber) {
  S21Matrix expected(2, 2);

  expected(0, 0) = 4;
  expected(0, 1) = 8;
  expected(1, 0) = 12;
  expected(1, 1) = 16;

  *t1 *= 4;

  ASSERT_EQ((*t1).EqMatrix(expected), true);
}

TEST_F(Test, testAssignmentMulMatrix) {
  S21Matrix expected(2, 2);

  expected(0, 0) = 6;
  expected(0, 1) = 6;
  expected(1, 0) = 14;
  expected(1, 1) = 14;

  *t1 *= *t2;
  t1->print();

  ASSERT_EQ((*t1).EqMatrix(expected), true);
}

TEST_F(Test, testAssignmentGetRows) { ASSERT_EQ((*t1).getRows(), 2); }

TEST_F(Test, testAssignmentGetCols) { ASSERT_EQ((*t1).getCols(), 2); }

TEST_F(Test, testAssignmentSetRows) { ASSERT_EQ((*t1).getRows(), 2); }

TEST_F(Test, testAssignmentSetCols) { ASSERT_EQ((*t1).getCols(), 2); }

TEST_F(Test, testIndexElements) { ASSERT_EQ((*t1)(1, 1), 4); }

TEST_F(Test, testAssignmentTranspose) {
  S21Matrix expected(2, 2);

  t3->Transpose();

  ASSERT_EQ((*t3).getRows(), 3);
  ASSERT_EQ((*t3).getCols(), 2);
}

TEST_F(Test, testAssignmentDeterminant) { ASSERT_EQ(t1->Determinant(), -2); }
//
TEST_F(Test, testAssignmentInverseMatrix) {
  S21Matrix expected(3, 3);
  expected(0, 0) = 1;
  expected(0, 1) = -38;
  expected(0, 2) = 27;
  expected(1, 0) = -1;
  expected(1, 1) = 41;
  expected(1, 2) = -29;
  expected(2, 0) = 1;
  expected(2, 1) = -34;
  expected(2, 2) = 24;
  ASSERT_EQ((*t4).EqMatrix(expected), false);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
