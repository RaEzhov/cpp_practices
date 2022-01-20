#include <iostream>

template <class T>
void swap(T& a,T& b){
    T time = a;
    a = b;
    b = time;
}

void conv(char& c){
    if (c >= 'A' && c <= 'Z'){
        return;
    } else if (c >= 'a' && c <= 'z'){
        c -= 32;
    } else{
        c = 127;
    }
}

template<class T>
void bubbleSort(T* arr, int size){
    bool isSorted = false;
    while (!isSorted){
        isSorted = true;
        for (int i = 0; i < size - 1; i++){
            if (arr[i] > arr[i+1]){
                swap(arr[i], arr[i+1]);
                isSorted = false;
            }
        }
    }
}

template<>
void bubbleSort<char>(char* arr, int size){
    bool isSorted = false;
    while (!isSorted) {
        isSorted = true;
        for (int i = 0; i < size - 1; i++){
            char a = arr[i];
            char b = arr[i+1];
            conv(a);
            conv(b);
            if (a > b){
                swap(arr[i], arr[i+1]);
                isSorted = false;
            }
        }
    }
    for (int i = 0; i < size; i++){
        if (!(arr[i] >= 'A' and arr[i] <= 'Z' or arr[i] >= 'a' and arr[i] <= 'z')){
            arr[i] = ' ';
        }
    }
}

template<class T>
void new_delete_practice(){
    int* n = new int;
    std::cout << "Enter amount:\n";
    std::cin >> *n;
    T* arr = new T[*n];
    std::cout << "Enter numbers (characters):\n";
    for (int i = 0; i < *n; i++){
        std::cin >> arr[i];
    }
    bubbleSort(arr, *n);
    std::cout << "Sorted array is: [ ";
    for (int i = 0; i < *n; i++){
        std::cout << arr[i] << ' ';
    }
    std::cout << "]\n";
    delete[] arr;
    delete n;
}

int main() {
    new_delete_practice<char>();
    return 0;
}
