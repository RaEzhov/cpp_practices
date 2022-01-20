#ifndef MYSTACK_H
#define MYSTACK_H

#include "dynArray.h"

template<class T>
class MyStack{
public:
    void push(T n){
        if (top_s < capacity){
            p_st->set(top_s,n);
            top_s++;
        } else {
            p_st->append(n);
        }
    }
    T pop(){
        if(isEmpty()){
            std::cout << "Error, stack is empty\n0 was returned\n";
            return 0;
        }else {
            top_s--;
            return p_st->get(top_s);
        }
    }
    T top(){
        if(isEmpty()){
            std::cout << "Error, stack is empty\n0 was returned\n";
            return 0;
        }else {
            return p_st->get(top_s-1);
        }
    }
    bool isEmpty(){
        return !(bool)top_s;
    }
    MyStack<T>(){
        p_st = new DynArray<T>(10);
        capacity = p_st->capacity;
        top_s = 0;
    }
    ~MyStack<T>(){
        delete p_st;
    }
private:
    DynArray<T>* p_st;
    int capacity;
    int top_s;
};

#endif//MYSTACK_H
