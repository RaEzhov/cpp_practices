#include <iostream>
#include "myStack.h"
#include "dynArray.h"
#include "Mat2D.h"
#include "queue.h"
#include "VecND.h"

template<class T>
VecND<T> operator*(Mat2D<T>& mat, VecND<T>& vec){
    if (mat.cols == vec.size) {
        VecND<T> res(mat.rows);
        for (int i = 0; i < res.size; i++) {
            for (int j = 0; j < mat.cols; j++){
                res[i] += mat[i][j] * vec[j];
            }
        }
        return res;
    } else {
        std::cout << "Error! Sizes of matrix and vector don't match!\n";
        exit(-1);
    }
}


int main() {
    return 0;
}
