// Copyright (c) —добнов ¬ладимир

#ifndef INCLUDE_MATRIX_H_
#define INCLUDE_MATRIX_H_

#include "../TVector/TVector.h"
#include <iostream>

const int MAX_MATRIX_SIZE = 10000;

template<class T>
class TMatrix;
template<class T>
std::istream& operator>>(std::istream& istr, TMatrix<T>& v);
template<class T>
std::ostream& operator<<(std::ostream& ostr, const TMatrix<T>& m);

template<typename T>
class TMatrix : private TVector<TVector<T>> {
  using TVector<TVector<T>>::pMem;
  using TVector<TVector<T>>::_size;
public:
  TMatrix(size_t s) : TVector<TVector<T>>(s) {
      if (s > MAX_MATRIX_SIZE)
          throw std::length_error("Matrix size cannot be greater than MAX_VECTOR_SIZE = " + std::to_string(MAX_VECTOR_SIZE));
      if (s < 0)
          throw std::length_error("Matrix size cannot be less than zero");
      for (size_t i = 0; i < s; i++)
          pMem[i] = TVector<T>(s);
  }
  // почему можно сделать так? ќбъ€снить.
  using TVector<TVector<T>>::operator[];
  using TVector<TVector<T>>::size;

  // сравнение
  bool operator==(const TMatrix& m) const noexcept { return *this == m; }
  bool operator!=(const TMatrix& m) const noexcept { return *this != m; }

  // матрично-скал€рные операции
  TMatrix operator*(const T& val) {
      TMatrix<T> tmp(*this);
      return tmp * val;
  }

  // матрично-векторные операции
  TVector<T> operator*(const TVector<T>& v) {

  }

  // матрично-матричные операции
  TMatrix operator+(const TMatrix& m) {}
  TMatrix operator-(const TMatrix& m) {}
  TMatrix operator*(const TMatrix& m) {}

  // ввод/вывод
  friend std::istream& operator>> <T>(std::istream& istr, TMatrix& v);
  friend std::ostream& operator<< <T>(std::ostream& ostr, const TMatrix& v);
};

#endif  // INCLUDE_MATRIX_H_

template<class T>
std::istream& operator>>(std::istream& istr, TMatrix<T>& m) {
    for (size_t i = 0; i < m._size; i++)
        istr >> m[i];
    return istr;
}

template<class T>
std::ostream& operator<<(std::ostream& ostr, const TMatrix<T>& m) {
    for (size_t i = 0; i < m._size; i++) {
        ostr << m.pMem[i] << '\n';
    }
    return ostr;
}