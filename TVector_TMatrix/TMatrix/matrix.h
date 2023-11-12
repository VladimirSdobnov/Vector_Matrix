// Copyright (c) Sdobnov Vladimir

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
template<class T>
class UpTrianglTMatrix;


template<typename T>
class TMatrix : public TVector<TVector<T>> {
protected:
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
  using TVector<TVector<T>>::at;
  using TVector<TVector<T>>::size;

  // сравнение
  bool operator==(const TMatrix& m) const noexcept {
      if (_size != m._size) { return false; }
      for (int i = 0; i < _size; i++) {
          if (pMem[i] != m.pMem[i]) { return false; }
      }
      return true;
  }
  bool operator!=(const TMatrix& m) const noexcept { return !(*this == m); }

  // матрично-скал€рные операции
  TMatrix operator*(const T& val) {
      TMatrix<T> tmp(*this);
      for (int i = 0; i < _size; i++) {
          tmp[i] = tmp[i] * val;
      }
      return tmp;
  }

  // матрично-векторные операции
  TVector<T> operator*(const TVector<T>& v) {
      TVector<T> tmp(_size);
      for (int i = 0; i < _size; i++) {
          tmp[i] = pMem[i] * v;
      }
      return tmp;
  }

  // матрично-матричные операции
  TMatrix operator+(const TMatrix& m) {
      if (m._size != _size) { throw std::logic_error("Not equl size, operation not defined"); }
      TMatrix<T> tmp(*this);
      for (int i = 0; i < _size; i++) {
          tmp[i] = tmp[i] + m[i];
      }
      return tmp;
  }
  TMatrix operator-(const TMatrix& m) {
      if (m._size != _size) { throw std::logic_error("Not equl size, operation not defined"); }
      TMatrix<T> tmp(*this);
      for (int i = 0; i < _size; i++) {
          tmp[i] = tmp[i] - m[i];
      }
      return tmp;
  }
  TMatrix operator*(const TMatrix& m) {
      if (m._size != _size) { throw std::logic_error("Not equl size, operation not defined"); }
      TMatrix<T> tmp(_size);
      for (int i = 0; i < m._size; i++) {
          TVector<T> vec;
          for (int j = 0; j < m._size; j++) {
              if (i < m[j].start()) { break; }
              vec.append(m[j][i]);
          }
          if (m._size != m[i].size() || (i == m._size - 1 && m[i - 1].size() != _size)) {
              vec.set_start(m[i].size() - 1);
          }
          tmp[i] = vec;
      }
      TMatrix<T> res(_size);
      for (int i = 0; i < _size; i++) {
          TVector<T> vec;
          for (int j = 0; j < _size; j++) {
              if (j > pMem[i].size() - 1) { break; }
              vec.append(pMem[i] * tmp[j]);
          }
          res[i] = vec;
      }
      return res;
  }

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

template<class T>
class UpTrianglTMatrix : public TMatrix<T> {
    using TMatrix<T>::pMem;
    using TMatrix<T>::_size;
public:
    UpTrianglTMatrix(size_t s) : TMatrix<T>(s) {
        for (size_t i = 0; i < s; i++)
            pMem[i] = TVector<T>(s, i);
    }
    using TMatrix<T>::operator[];
    using TMatrix<T>::at;
    using TMatrix<T>::size;
    using TMatrix<T>::operator=;

    bool operator==(const UpTrianglTMatrix& m) const noexcept {
        if (_size != m._size) { return false; }
        for (int i = 0; i < _size; i++) {
            for (int j = i; j < _size; j++) {
                if (m[i][j] != pMem[i][j]) { return false; }
            }
        }
        return true;
    }
    bool operator!=(const UpTrianglTMatrix& m) const noexcept {
        return !(*this == m);
    }

    friend std::ostream& operator<< <T>(std::ostream& ostr, const TMatrix<T>& v);
};

template<class T>
class DownTrianglTMatrix : public TMatrix<T> {
    using TMatrix<T>::pMem;
    using TMatrix<T>::_size;
public:
    DownTrianglTMatrix(size_t s) : TMatrix<T>(s) {
        for (size_t i = 0; i < s; i++)
            pMem[i] = TVector<T>(i + 1);
    }
    using TMatrix<T>::operator[];
    using TMatrix<T>::at;
    using TMatrix<T>::size;
    using TMatrix<T>::operator=;

    bool operator==(const DownTrianglTMatrix& m) const noexcept {
        if (_size != m._size) { return false; }
        for (int i = 0; i < _size; i++) {
            for (int j = 0; j <= i; j++) {
                if (m[i][j] != pMem[i][j]) { return false; }
            }
        }
        return true;
    }
    bool operator!=(const DownTrianglTMatrix& m) const noexcept {
        return !(*this == m);
    }

    friend std::ostream& operator<< <T>(std::ostream& ostr, const TMatrix<T>& v);
};