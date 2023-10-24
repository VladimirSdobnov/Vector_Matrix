// Copyright (c) Sdobnov Vladimir

#ifndef INCLUDE_MATRIX_H_
#define INCLUDE_MATRIX_H_

#include "../TVector/TVector.h"
#include <iostream>

const int MAX_MATRIX_SIZE = 10000;

template<typename T>
class TMatrix : private TVector<TVector<T>> {
  using TVector<TVector<T>>::pMem;
  using TVector<TVector<T>>::_size;
public:
  TMatrix(size_t s) : TVector<TVector<T>>(s) {
    for (size_t i = 0; i < s; i++)
      pMem[i] = TVector<T>(s);
  }
  // ������ ����� ������� ���? ���������.
  using TVector<TVector<T>>::operator[];

  // ���������
  bool operator==(const TMatrix& m) const noexcept { return true; }
  bool operator!=(const TMatrix& m) const noexcept { return false; }

  // ��������-��������� ��������
  TMatrix operator*(const T& val) {}

  // ��������-��������� ��������
  TVector<T> operator*(const TVector<T>& v) {}

  // ��������-��������� ��������
  TMatrix operator+(const TMatrix& m) {}
  TMatrix operator-(const TMatrix& m) {}
  TMatrix operator*(const TMatrix& m) {}

  // ����/�����
  friend std::istream& operator>>(std::istream& istr, TMatrix& v) {}
  friend std::ostream& operator<<(std::ostream& ostr, const TMatrix& v) {}
};

#endif  // INCLUDE_MATRIX_H_
