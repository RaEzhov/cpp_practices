#ifndef DYNARRAY_H
#define DYNARRAY_H
#include <vector>

template <class T>
class DynArray{
public:
    DynArray(int a){
        vec.resize(a);
        length = a;
        countOfArrays++;
    }
    DynArray(const DynArray& arr){
        vec.resize(arr.length);
        length = arr.length;
        for (int i = 0; i < length; i++){
            vec[i] = arr.vec[i];
        }
        countOfArrays++;
    }
    ~DynArray(){
        countOfArrays--;
    }
    void set(int pos, T n) {
        if (pos <= length) {
            vec.insert(vec.begin() + pos, n);
        } else {
            std::cout << "Error! Out-of-bounds index!\n";
            exit(-1);
        }
    }
    void append(T n){
        vec.push_back(n);
    }
    T get(int n){
        if (n < length){
            return vec[n];
        } else {
            std::cout << "Error! Out-of-bounds index!\n";
            exit(-1);
        }
    }
    DynArray& operator=(const DynArray& arr) {
        vec.resize(arr.length);
        for (int i = 0; i < arr.length; i++) {
            vec[i] = arr.vec[i];
        }
        length = arr.length;
        return (*this);
    }
    T& operator[](int n){
        if (n <= length) {
            return vec[n];
        }
        std::cout<<"Error! Out-of-bounds index!\n";
        exit(-1);
    }
    DynArray operator+(const DynArray& r){
        DynArray tmp(length + r.length);
        tmp.length = length + r.length;
        int ind = 0;
        for (int i = 0; i < length; i++){
            tmp.vec[ind++] = vec[i];
        }
        for (int i = 0; i < length; i++){
            tmp.vec[ind++] = r.vec[i];
        }
        return tmp;
    }
    void operator>>(int n){
        for (int i = 0; i < n; i++){
            shift(vec, true);
        }
    }
    void operator<<(int n){
        for (int i = 0; i < n; i++){
            shift(vec, false);
        }
    }
    void print(){
        std::cout << "[ ";
        for (int i = 0; i < length - 1; i++){
            std::cout << vec[i] << ", ";
        }
        std::cout << vec[length-1] << " ]\n";
    }
private:
    std::vector<T> vec;
    int length;
    static long countOfArrays;

    void shift(std::vector<T> arr, bool dir) { // dir == true => right shift
        if (dir) {
            vec.insert(vec.begin(), vec[vec.size()-1]);
            vec.pop_back();
        } else {
            vec.insert(vec.end(), vec[0]);
            vec.erase(vec.begin());
        }
    }
};

template<class T>
long DynArray<T>::countOfArrays = 0;

#endif//DYNARRAY_H
