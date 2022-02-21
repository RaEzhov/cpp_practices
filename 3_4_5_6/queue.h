#ifndef QUEUE_H
#define QUEUE_H
#include <vector>
template <class T>
class Queue{
public:
    Queue(){
        arr.resize(0);
    }
    Queue(int size){
        arr.resize(size);
    }
    Queue(const Queue& arg){
        arr.resize(arg.arr.size());
        for (int i = 0; i < arr.size(); i++){
            arr[i] = arg.arr[i];
        }
    }
    bool isEmpty() const{
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
    T front() const{
        if (arr.empty()){
            std::cout << "Error! Queue is empty!\n";
            exit(-1);
        }
        return arr[0];
    }
    T back()const{
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
