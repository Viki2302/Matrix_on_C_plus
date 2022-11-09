CC=gcc
# CPPFLAGS=-Wall -Wextra -Werror -Wno-unused -pedantic -std=c++17 -lstdc++
CXXFLAGS=-Wall -Wextra -Werror -Wno-unused -pedantic -std=c++17
GTESTFLAGS=-lgtest_main -lgtest

NAME=s21_matrix_oop.a
HEADER=s21_matrix_oop.h
SRC=s21_matrix_oop.cc
OBJ=$(patsubst %.cc, %.o, $(SRC))

OS = $(shell uname)

.PHONY: all s21_matrix_oop test gcov_report re clean m

all: $(NAME)

build: $(NAME)

$(NAME) : $(OBJ) $(HEADER)
	ar rcs $(NAME) $?
%.o : %.c $(HEADER)
	$(CC) $(CXXFLAGS) -c $< -o $@

s21_test_matrix_oop.a : $(patsubst %.cc, %.o, s21_test_matrix_oop.cc) s21_test_matrix_oop.h
	ar rcs s21_test_matrix_oop.a $?
%.o : %.cc s21_test_matrix_oop.h
	$(CC) $(CXXFLAGS) -c $< -o $@

test: build s21_test_matrix_oop.a
	$(CC) $(GTESTFLAGS) $(CXXFLAGS) -lstdc++ s21_test_matrix_oop.a s21_test_matrix_oop.cc s21_matrix_oop.a s21_matrix_oop.cc -o TEST
	./TEST

re: clean build

clean:
	rm -rf *.o *.gch *.out *.a MATRIX_OOP TEST
