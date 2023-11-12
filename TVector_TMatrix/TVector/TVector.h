#pragma once

const int MAX_VECTOR_SIZE = 100000000;
#include <iostream>
#include <string>
#include <assert.h>

template<class T>
class TVector;
template<class T>
std::istream& operator>>(std::istream& istr, TVector<T>& v);
template<class T>
std::ostream& operator<<(std::ostream& ostr, const TVector<T>& v);

//Iterators

#include <iterator>
template<class T>
class InIterator : public std::iterator<std::input_iterator_tag, T> {
    friend class TVector<T>;
protected:
    T* p;
    InIterator(T* _p) : p(_p) {};
public:
    InIterator& operator=(const InIterator& it) {
        if (this != it) {
            p = it.p;
        }
        return *this;
    }
    bool operator!=(InIterator const& other) const { return p != other.p; }
    bool operator==(InIterator const& other) const { return p == other.p; }
    T& operator*() const { return *p; } //typename Iterator<T>::reference operator*() const;
    InIterator& operator++() { ++p; return *this; }
};

template<class T>
class OutIterator : public std::iterator<std::output_iterator_tag, T> {
    friend class TVector<T>;
protected:
    T* p;
    OutIterator(T* _p) : p(_p) {};
public:
    OutIterator& operator=(const OutIterator& it) {
        if (this != it) {
            p = it.p;
        }
        return *this;
    }
    T& operator*() { return *p; }
    bool operator!=(OutIterator const& other) const { return p != other.p; }
    bool operator==(OutIterator const& other) const { return p == other.p; }
    OutIterator& operator++() { ++p; return *this; }
    OutIterator& operator++(int) {
        OutIterator tmp = *this;
        p++;
        return tmp;
    }
};

template <class T>
class ForwardIterator : public InIterator<T>, public OutIterator<T>, 
    public std::iterator<std::forward_iterator_tag, T> {
    friend class TVector<T>;
protected:
    using OutIterator<T>::p;
    ForwardIterator(T* _p) : InIterator<T>(_p), OutIterator<T>(_p) {};
public:
    ForwardIterator(const ForwardIterator& it) : InIterator<T>(it.p), OutIterator<T>(it.p) {};
    using OutIterator<T>::operator*;
    using OutIterator<T>::operator++;
    using OutIterator<T>::operator==;
    using OutIterator<T>::operator!=;
    
};

template <class T>
class BidirectionalIterator : public ForwardIterator<T>,
    public std::iterator<std::bidirectional_iterator_tag, T> {
    friend class TVector<T>;
    using ForwardIterator<T>::p;
    BidirectionalIterator(T* p) : ForwardIterator<T>(p) {};
public:
    BidirectionalIterator(const BidirectionalIterator& it) : ForwardIterator<T>(it) {};
    using ForwardIterator<T>::operator*;
    using ForwardIterator<T>::operator++;
    using ForwardIterator<T>::operator==;
    using ForwardIterator<T>::operator!=;
    BidirectionalIterator& operator--() { --p; return *this; }
    BidirectionalIterator& operator--(int) {
        BidirectionalIterator tmp(*this);
        p--;
        return tmp;
    }
};

//template<class T>
//class 
//Vector
template<class T>
void swap(TVector<T>& lhs, TVector<T>& rhs) noexcept {
    std::swap(lhs._size, rhs._size);
    std::swap(lhs.pMem, rhs.pMem);
    std::swap(lhs.start_pos, rhs.start_pos);
}
template<class T>
class TVector {
protected:
    size_t _size;
    T* pMem;
    size_t start_pos;
public:
    TVector(int sz = 0, int start = 0) : _size(sz), start_pos(start) {
        if (sz > MAX_VECTOR_SIZE)
            throw std::length_error("Vector size cannot be greater than MAX_VECTOR_SIZE = " + std::to_string(MAX_VECTOR_SIZE));
        if (sz < 0)
            throw std::length_error("Vector size cannot be less than zero");
        if (abs(start) > sz) { throw std::length_error("Vector start must be less then size"); }
        if (sz == 0) { pMem = nullptr; return; }
        if (sz < 0) { start_pos = sz + start; }
        pMem = new T[sz];
    }
    TVector(T* data, int sz, int start = 0) : _size(sz), start_pos(start) {
        // еще один способ ввода исключений
        if (abs(start) > sz) { throw std::length_error("Vector start must be less then size"); }
        if (sz < 0) { start_pos = sz + start; }
        assert(data != nullptr && "TVector constructor requires non-nullptr argument.");
        pMem = new T[sz];
        // дл€ массивов можно использовать std-функции с условием, что вы знаете как они там реализованы!
        std::copy(data, data + sz, pMem);
    }

    TVector(const TVector& v) : _size(v._size), start_pos(v.start_pos){
        pMem = new T[v._size];
        std::copy(v.pMem, v.pMem + _size, pMem);
    }

    TVector(TVector&& v) noexcept : _size(0), pMem(nullptr), start_pos(0) {
        std::swap(v.pMem, pMem);
        std::swap(v._size, _size);
        std::swap(v.start_pos, start_pos);
    }

    ~TVector() {
        delete[] pMem;
        pMem = nullptr;
    }


    InIterator<T> begin_in() { return InIterator<T>(pMem + start_pos); }
    InIterator<T> end_in() { return InIterator<T>(pMem + _size); }
    InIterator<T> begin_in() const { return InIterator<const T>(pMem + start_pos); }
    InIterator<T> end_in() const { return InIterator<const T>(pMem + _size); }

    OutIterator<T> begin_out() { return OutIterator<T>(pMem + start_pos); }
    OutIterator<T> end_out() { return OutIterator<T>(pMem + _size); }
    OutIterator<T> begin_out() const { return OutIterator<const T>(pMem + start_pos); }
    OutIterator<T> end_out() const { return OutIterator<const T>(pMem + _size); }

    ForwardIterator<T> begin_forward() { return ForwardIterator<T>(pMem + start_pos); }
    ForwardIterator<T> end_forward() { return ForwardIterator<T>(pMem + _size); }
    ForwardIterator<T> begin_forward() const { return ForwardIterator<const T>(pMem + start_pos); }
    ForwardIterator<T> end_forward() const { return ForwardIterator<const T>(pMem + _size); }

    BidirectionalIterator<T> begin() { return BidirectionalIterator<T>(pMem + start_pos); }
    BidirectionalIterator<T> end() { return BidirectionalIterator<T>(pMem + _size); }
    BidirectionalIterator<T> begin() const { return BidirectionalIterator<const T>(pMem + start_pos); }
    BidirectionalIterator<T> end() const { return BidirectionalIterator<const T>(pMem + _size); }





    TVector& operator=(const TVector& v) {
        if (this == &v) { return *this; }
        _size = v._size;
        pMem = new T[_size];
        start_pos = v.start_pos;
        std::copy(v.pMem, v.pMem + _size, pMem);
        return *this;
    }

    TVector& operator=(TVector&& v) noexcept {
        if (this == &v) { return *this; }
        delete[] pMem;
        pMem = nullptr;
        _size = 0;
        start_pos = 0;
        swap<T>(*this, v);
        return *this;
    }

    size_t size() const noexcept { return _size; }
    size_t start() const noexcept { return start_pos; }
    void set_start(int x) {
        if (x < 0 || x >= _size) { throw std::length_error("Wrong start"); }
        start_pos = x;
    }
    // индексаци€
    T& operator[](size_t ind) {
        return pMem[ind];
    }
    T& operator[](ForwardIterator<T> it) {
        return *it;
    }
    const T& operator[](ForwardIterator<T> it) const {
        return *it;
    }
    const T& operator[](size_t ind) const {
        return pMem[ind];
    }

    // индексаци€ с контролем - почитать в чЄм разница и объ€снить при сдаче работы
    T& at(int ind) {
        if ((ind > _size - 1) || (ind < 0) || ind < start_pos) { throw std::out_of_range("Index out of range"); }
        return pMem[ind];
    }
    const T& at(int ind) const {
        if ((ind > _size - 1) || (ind < 0) || ind < start_pos) { throw std::out_of_range("Index out of range"); }
        return pMem[ind];
    }

    // сравнение
    bool operator==(const TVector& v) const noexcept {
        if (_size != v._size || start_pos != v.start_pos) { return false; }
        for (int i = start_pos; i < _size; i++) { if (pMem[i] != v.pMem[i]) { return false; } }
        return true;
    }
    bool operator!=(const TVector& v) const noexcept {
        return !(*this == v);
    }

    TVector operator+(T val) {
        TVector<T> tmp(*this);
        for (int i = start_pos; i < _size; i++) {
            tmp[i] = tmp[i] + val;
        }
        return tmp;
    }
    TVector operator-(T val) {
        TVector<T> tmp(*this);
        for (int i = start_pos; i < _size; i++) {
            tmp[i] = tmp[i] - val;
        }
        return tmp;
    }
    TVector operator*(T val) {
        TVector<T> tmp(*this);
        for (int i = 0; i < _size; i++) {
            tmp[i] = tmp[i] * val;
        }
        return tmp;
    }

    TVector operator+(const TVector& v) {
        if (_size != v._size || start_pos != v.start_pos) { throw std::logic_error("Unequal dimensions"); }
        TVector<T> tmp(*this);
        for (int i = start_pos; i < _size; i++) {
            tmp[i] = tmp[i] + v[i];
        }
        return tmp;
    }
    TVector operator-(const TVector& v) {
        if (_size != v._size || start_pos != v.start_pos) { throw std::logic_error("Unequal dimensions"); }
        TVector<T> tmp(*this);
        for (int i = start_pos; i < _size; i++) {
            tmp[i] = tmp[i] - v[i];
        }
        return tmp;
    }

    // почитать о noexcept(noexcept(T())) - объ€снить назначение при сдаче
    T operator*(const TVector& v) noexcept(T()) {
        int sz = std::min(_size, v._size);
        int start = std::max(start_pos, v.start_pos);
        //if (sz < start) { throw std::logic_error("Wrong size"); }
        if (pMem == nullptr || v.pMem == nullptr) { throw std::logic_error("Null sized vector"); }
        T tmp = (*this)[start] * v[start];
        for (int i = start + 1; i < sz; i++) {
            tmp = tmp + v[i] * (*this)[i];
        }
        return tmp;
    }

    void append(const T& elem) {
        TVector<T> tmp(_size + 1);
        std::copy(begin_in(), end_in(), tmp.pMem);
        tmp[_size] = elem;
        *this = tmp;
    }

    friend void swap <T>(TVector& lhs, TVector& rhs) noexcept;

    // ввод/вывод
    friend std::istream& operator>> <T>(std::istream& istr, TVector& v);
    friend std::ostream& operator<< <T>(std::ostream& ostr, const TVector& v);
};



// ввод/вывод
template<class T>
std::istream& operator>>(std::istream& istr, TVector<T>& v) {
    for (size_t i = 0; i < v._size; i++)
        istr >> v[i];
    return istr;
}

template<class T>
std::ostream& operator<<(std::ostream& ostr, const TVector<T>& v) {
    std::string pass(v.start_pos * 2, ' ');
    ostr << pass;
    for (size_t i = v.start(); i < v._size; i++) {
        ostr << v.pMem[i] << ' ';
    }
    return ostr;
}

template<class T>
void fill(ForwardIterator<T> first, ForwardIterator<T> last, const T& val) {
    for (auto elem = first; elem != last; elem++) {
        *elem = val;
    }
}

template<class T>
size_t count(ForwardIterator<T> begin, ForwardIterator<T> end, const T& elem) {
    size_t count = 0;
    while (begin != end) {
        if (*begin == elem) count++;
        begin++;
    }
    return count;
}

template <class T>
ForwardIterator<T>& find(ForwardIterator<T> begin, ForwardIterator<T> end, const T& elem) {
    while (begin != end) {
        if (*begin == elem) return begin;
        begin++;
    }
    throw std::bad_alloc();
}

