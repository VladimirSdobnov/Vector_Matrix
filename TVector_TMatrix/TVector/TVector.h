#pragma once

const int MAX_VECTOR_SIZE = 100000000;
#include <iostream>

template<typename T>
class TVector {
protected:
    size_t _size;
    T* pMem;
public:
    TVector(size_t sz = 1) : _size(sz) {
        if (sz == 0)
            throw std::length_error("Vector size should be greater than zero");
        if (sz > MAX_VECTOR_SIZE)
            throw std::length_error("Vector size cannot be greater than MAX_VECTOR_SIZE = ", MAX_VECTOR_SIZE);
        pMem = new T[sz]();
    }

    TVector(T* data, size_t sz) : _size(sz) {
        // ��� ���� ������ ����� ����������
        assert(data != nullptr && "TVector constructor requires non-nullptr argument.");
        pMem = new T[sz];
        // ��� �������� ����� ������������ std-������� � ��������, ��� �� ������ ��� ��� ��� �����������!
        std::copy(data, data + sz, pMem);
    }

    TVector(const TVector& v);

    TVector(TVector&& v) noexcept;

    ~TVector();

    TVector& operator=(const TVector& v);

    TVector& operator=(TVector&& v) noexcept;

    size_t size() const noexcept;

    // ����������
    T& operator[](size_t ind);
    const T& operator[](size_t ind) const;

    // ���������� � ��������� - �������� � ��� ������� � ��������� ��� ����� ������
    T& at(size_t ind);
    const T& at(size_t ind) const;

    // ���������
    bool operator==(const TVector& v) const noexcept;
    bool operator!=(const TVector& v) const noexcept;

    TVector operator+(double val);
    TVector operator-(double val);
    TVector operator*(double val);

    TVector operator+(T val);
    TVector operator-(T val);
    TVector operator*(T val);

    TVector operator+(const TVector& v);
    TVector operator-(const TVector& v);

    // �������� � noexcept(noexcept(T())) - ��������� ���������� ��� �����
    T operator*(const TVector& v) noexcept(noexcept(T()));

    friend void swap(TVector& lhs, TVector& rhs) noexcept;

    // ����/�����
    friend istream& operator>>(istream& istr, TVector& v);
    friend ostream& operator<<(ostream& ostr, const TVector& v);
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
