#ifndef QUEUE_H
#define QUEUE_H
#include <vector>
template <class T>
class queue{
public:
    queue(){
        arr.resize(0);
    }
    queue(int size){
        arr.resize(size);
    }
    queue(const queue& arg){
        arr.resize(arg.arr.size());
        for (int i = 0; i < arr.size(); i++){
            arr[i] = arg.arr[i];
        }
    }
    bool isEmpty(){
        return arr.empty();
    }
    void push(T element){
        arr.push_back(element);
    }
    T pop(){
        if (arr.empty()){
            std::cout << "Error! Queue is empty!\n";
            exit(-1);
        }
        T res = arr[0];
        arr.erase(arr.begin());
        return res;
    }
    T front(){
        if (arr.empty()){
            std::cout << "Error! Queue is empty!\n";
            exit(-1);
        }
        return arr[0];
    }
    T back() {
        if (arr.empty()){
            std::cout << "Error! Queue is empty!\n";
            exit(-1);
        }
        return arr[arr.size() - 1];
    }

private:
    std::vector<T> arr;
};

#endif//QUEUE_H
