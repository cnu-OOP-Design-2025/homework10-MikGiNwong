#pragma once

#include <initializer_list>
#include <cstddef>


template<typename T>
class MyVector {
    T* data;            // 동적 배열을 가리키는 포인터
    size_t cap;         // 현재 할당된 배열 크기
    size_t length;      // 실제 저장된 요소 개수    
public:

    MyVector(std::initializer_list<T> init) {
        length = init.size();
        cap = length;
        data = new T[cap];
        size_t i = 0;
        for (const auto& val : init) {
            data[i++] = val;
        }
    }

    MyVector(): data(nullptr), length(0), cap(0) {}
    ~MyVector() { delete[] data; }

    void push_back(const T& val){
        if(cap == length){
            cap *= 2;
            T* new_data = new T[cap];
            for(int i = 0; i < length; i++){
                new_data[i] = data[i];
            }
            delete[] data;
            data = new_data;
        };
        data[length++] = val;
    };   // Vector 마지막에 항목을 추가하는 함수 구현, 필요시 벡터 크기 증가
    void pop_back(){
        length--;
    };                // Vector의 마지막 항목을 제거하는 함수 구현
    size_t size() const{
        return length;
    };            // Vecotr에 있는 항목 개수(length)를 리턴하는 함수 구현
    T& operator[](int i){
        return data[i];
    };          // [] 연산자 구현

    bool operator==(const MyVector& other) const{
        if(length != other.length){
            return false;
        }
        for(int i = 0; i < length; i++){
            if(data[i] != other.data[i]){
                return false;
            }
        }
        return true;
    };

    bool operator!=(const MyVector& other) const{
        if(length != other.length){
            return true;
        }
        for(int i = 0; i < length; i++){
            if(data[i] != other.data[i]){
                return true;
            }
        }
        return false;
    };

    bool operator<(const MyVector& other) const{
        int min_len = (length < other.length) ? length : other.length;
        for(int i = 0; i < min_len; i++){
            if(data[i] > other.data[i]) return false;
            if(data[i] < other.data[i]) return true;
        }
        return length < other.length;
    };

    bool operator>(const MyVector& other) const{
        int min_len = (length < other.length) ? length : other.length;
        for(int i = 0; i < min_len; i++){
            if(data[i] < other.data[i]) return false;
            if(data[i] > other.data[i]) return true;
        }
        return length > other.length;
    };

    bool operator<=(const MyVector& other) const{
        int min_len = (length < other.length) ? length : other.length;
        for(int i = 0; i < min_len; i++){
            if(data[i] > other.data[i]) return false;
            if(data[i] < other.data[i]) return true;
        }
        return length <= other.length;
    };

    bool operator>=(const MyVector& other) const{
        int min_len = (length < other.length) ? length : other.length;
        for(int i = 0; i < min_len; i++){
            if(data[i] < other.data[i]) return false;
            if(data[i] > other.data[i]) return true;
        }
        return length >= other.length;
    };


    // Vector에 대한 반복자
    class Iterator {
        T* ptr;         // 항목에 대한 포인터
    public:
        Iterator(T* p = nullptr): ptr(p) {}

        T& operator*(){
            return *ptr;
        }; // 역참조 연산자 구현 

        Iterator& operator++(){
            ptr++;
            return *this;
        };   //전위 증가 연산자 구현
        Iterator& operator--(){
            ptr--;
            return *this;
        };   //전위 감소 연산자 구현
        Iterator operator+(int n) const {
            return Iterator(ptr + n);            
        };   // 산술 연산자 구현
        Iterator operator-(int n) const {
            return Iterator(ptr - n);
        };   // 산술 연산자 구현

        bool operator==(const Iterator& other) const {
            return ptr == other.ptr;
        };
        bool operator!=(const Iterator& other) const {
            return ptr != other.ptr;
        };

        int operator-(const Iterator& other) const {
            return ptr - other.ptr; 
        };
    };

    // 첫번째 항목에 대한 iterator 리턴 함수 구현
    Iterator begin() {
        return data;
    };
    // 마지막 항목에 대한 iterator 리턴 함수 구현 
    Iterator end() {
        return begin() + size();
    };


    // insert: 지정 위치에 요소 삽입 함수 구현
    Iterator insert(Iterator pos, const T& value){
        Iterator last = end();
        while(last != pos){
            *last = *(last - 1);
            --last;
        }
        *pos = value;
        length++;
        return pos;
    };

    // erase: 지정 위치 요소 제거 함수 구현
    Iterator erase(Iterator pos){
        while(pos != (end() - 1)){
            *pos = *(pos + 1);
            ++pos;
        }
        length--;
        return pos;
    };

    // clear: 모든 요소 제거 함수 구현 (size = 0 초기화)
    void clear() {
        length = 0;
    };

    // at: 범위 체크 후, i번째 항목 접근 함수 구현
    T& at(size_t i){
        if(i >= 0 && i < length){
            return data[i];
        }
        throw std::out_of_range("Index out of range");
    }; 

    // front/back
    T& front() {
        return data[0];
    };    // 첫번째 항목 리턴 함수 구현
    T& back() {
        return data[length - 1];
    };     // 마지막 항목 리턴 함수 구현

    // capacity
    size_t capacity() const {
        return cap;
    };   // cap 값 리턴하는 함수 구현

    // empty
    bool empty() const {
        return length == 0;
    };    // 현재 vector가 empty인지 확인하는 함수 구현

};