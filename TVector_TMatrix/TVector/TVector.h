#pragma once

const int MAX_VECTOR_SIZE = 100000000;
#include <iostream>

template<typename T>
class TVector {
protected:
    size_t _size;
    T* pMem;
public:
    TVector() :_size(0), pMem(nullptr) {};
    TVector(size_t sz = 1) : _size(sz) {
        if (sz == 0)
            throw std::length_error("Vector size should be greater than zero");
        if (sz > MAX_VECTOR_SIZE)
            throw std::length_error("Vector size cannot be greater than MAX_VECTOR_SIZE = " + MAX_VECTOR_SIZE);
        if (sz < 0)
            throw std::length_error("Vector size cannot be less than zero");
        if (sz == 0) { pMem = nullptr; return; }
        pMem = new T[sz]();
    }
    TVector(T* data, size_t sz) : _size(sz) {
        // ��� ���� ������ ����� ����������
        assert(data != nullptr && "TVector constructor requires non-nullptr argument.");
        pMem = new T[sz];
        // ��� �������� ����� ������������ std-������� � ��������, ��� �� ������ ��� ��� ��� �����������!
        std::copy(data, data + sz, pMem);
    }

    TVector(const TVector& v) : _size(v._size){
        pMem = new T[v._size];
        std::copy(v.pMem, v.pMem + _size, pMem);
    }

    TVector(TVector&& v) noexcept : _size(0), pMem(nullptr) {
        std::swap(v.pMem, pMem);
        std::swap(v._size, _size);
    }

    ~TVector() {
        delete[] pMem;
    }

    TVector& operator=(const TVector& v) {
        if (this == &v) { return *this; }
        _size = v._size;
        pMem = new T[_size];
        std::copy(v.pMem, v.pMem + _size, pMem);
        return *this;
    }

    TVector& operator=(TVector&& v) noexcept {
        if (this == &v) { return *this; }
        delete[] pMem;
        pMem = nullptr;
        _size = 0;
        std::swap(pMem, v.pMem);
        std::swap(_size, v._size);
        return *this;
    }

    size_t size() const noexcept { return _size; }

    // ����������
    T& operator[](size_t ind) {
        return pMem[ind];
    }
    const T& operator[](size_t ind) const {
        return pMem[ind];
    }

    // ���������� � ��������� - �������� � ��� ������� � ��������� ��� ����� ������
    T& at(size_t ind) {
        if ((ind > _size - 1) && (ind < 0)) { throw std::out_of_range("Index out of range"); }
        return pMem[ind];
    }
    const T& at(size_t ind) const {
        if ((ind > _size - 1) && (ind < 0)) { throw std::out_of_range("Index out of range"); }
        return pMem[ind];
    }

    // ���������
    bool operator==(const TVector& v) const noexcept {
        if (_size != v._size) { return false; }
        for (int i = 0; i < _size; i++) { if (pMem[i] != v.pMem[i]) { return false; } }
        return true;
    }
    bool operator!=(const TVector& v) const noexcept {
        return not(*this == v);
    }

    TVector operator+(T val) {
        TVector<T> tmp(this);
        for (int i = 0; i < _size; i++) {
            tmp[i] = tmp[i] + val;
        }
        return tmp;
    }
    TVector operator-(T val) {
        TVector<T> tmp(this);
        for (int i = 0; i < _size; i++) {
            tmp[i] = tmp[i] - val;
        }
        return tmp;
    }
    TVector operator*(T val) {
        TVector<T> tmp(this);
        for (int i = 0; i < _size; i++) {
            tmp[i] = tmp[i] * val;
        }
        return tmp;
    }

    TVector operator+(const TVector& v) {
        if (_size != v._size) { throw std::logic_error("Unequal dimensions"); }
        TVector<T> tmp(this);
        for (int i = 0; i < _size; i++) {
            tmp[i] = tmp[i] + v[i];
        }
        return tmp;
    }
    TVector operator-(const TVector& v) {
        if (_size != v._size) { throw std::logic_error("Unequal dimensions"); }
        TVector<T> tmp(this);
        for (int i = 0; i < _size; i++) {
            tmp[i] = tmp[i] - v[i];
        }
        return tmp;
    }

    // �������� � noexcept(noexcept(T())) - ��������� ���������� ��� �����
    T operator*(const TVector& v) noexcept(noexcept(T())) {
        if (_size != v._size) { throw std::logic_error("Unequal dimensions"); }
        T tmp = this[0] + v[0];
        for (int i = 1; i < _size; i++) {
            tmp = tmp + v[i] * this[i];
        }
        return tmp;
    }

    friend void swap(TVector& lhs, TVector& rhs) noexcept;

    // ����/�����
    friend std::istream& operator>>(std::istream& istr, TVector& v);
    friend std::ostream& operator<<(std::ostream& ostr, const TVector& v);
};

template<typename T>
void swap(TVector<T>& lhs, TVector<T>& rhs) noexcept {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
}

// ����/�����
template<typename T>
std::istream& operator>>(std::istream& istr, TVector<T>& v) {
    for (size_t i = 0; i < v.sz; i++)
        istr >> v.pMem[i];
    return istr;
}

template<typename T>
std::ostream& operator<<(std::ostream& ostr, const TVector<T>& v) {
    for (size_t i = 0; i < v.sz; i++)
        ostr << v.pMem[i] << ' ';
    return ostr;
}
