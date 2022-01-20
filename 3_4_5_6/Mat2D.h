#ifndef MAT2D_H
#define MAT2D_H
#include <vector>
#include <cmath>

template <class T>
class Mat2D{
public:
    Mat2D(int n, int m) {
        rows = n;
        cols = m;
        matrix.resize(rows);
        for (int i = 0; i < rows; i++){
            matrix[i].resize(cols);
        }
    }
    Mat2D(const Mat2D& mat) {
        rows = mat.rows;
        cols = mat.cols;
        matrix.resize(rows);
        for (int i = 0; i < rows; i++){
            matrix[i].resize(cols);
            for (int j = 0; j < cols; j++){
                matrix[i][j] = mat.matrix[i][j];
            }
        }
    }
    std::vector<T>& operator[](int ind) {
        if (ind < rows) {
            return matrix[ind];
        } else {
            std::cout << "Error! Out-of-bounds index!\n";
            exit(-1);
        }
    }
    void print() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; ++j) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    Mat2D<T>& operator=(const Mat2D<T>& mat) {
        rows = mat.rows;
        cols = mat.cols;
        matrix.resize(rows);
        for (int i = 0; i < rows; i++) {
            matrix[i].resize(cols);
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = mat.matrix[i][j];
            }
        }
        return *this;
    }
    void input() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cin >> matrix[i][j];
            }
        }
    }
    Mat2D<T> operator+(const Mat2D<T> &mat2) {
        if (rows == mat2.rows and cols == mat2.cols) {
            Mat2D<T> tmp(rows, cols);
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    tmp.matrix[i][j] = matrix[i][j] + mat2.matrix[i][j];
                }
            }
            return tmp;
        } else {
            std::cout << "Error! Addition of matrices of different sizes is impossible!\n";
            exit(-1);
        }
    }
    Mat2D<T> operator*(const Mat2D<T> &mat2) {
        if (cols == mat2.rows) {
            Mat2D<T> tmp(rows, mat2.cols);
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < mat2.cols; j++) {
                    T value = 0;
                    for (int k = 0; k < cols; k++) {
                        value += matrix[i][k] * mat2.matrix[k][j];
                    }
                    tmp.matrix[i][j] = value;
                }
            }
            return tmp;
        } else {
            std::cout << "Error! Incorrect matrix sizes for multiplication!\n";
            exit(-1);
        }
    }

    Mat2D<T> operator/(T num) {
        Mat2D<T> tmp = *this;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                tmp[i][j] /= num;
            }
        }
        return tmp;
    }

    Mat2D<T> transposition() {
        Mat2D<T> tmp(cols, rows);
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                tmp[j][i] = matrix[i][j];
            }
        }
        return tmp;
    }

    T determinant() {
        if (rows != cols){
            std::cout << "Error! Matrix is not square!\n";
            exit(-1);
        }
        if (cols == 1){
            return matrix[0][0];
        }
        if (cols == 2){
            return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        }
        T res = 0;
        for (int i = 0; i < rows; i++) {
            Mat2D<T> tmp(rows - 1, cols - 1);
            int tmpR = 0, tmpC = 0;
            for (int r = 0; r < rows; r++) {
                if (r == i){
                    continue;
                }
                tmpC = 0;
                for (int c = 1; c < cols; c++){
                    tmp[tmpR][tmpC] = matrix[r][c];
                    tmpC++;
                }
                tmpR++;
            }
            res += matrix[i][0] * tmp.determinant() * pow(-1,i);
        }
        return res;
    }

    Mat2D<T> inverse() {
        T det = this->determinant();
        if (det <= (T)0.0000001 and det >= (T)(-0.00000001)) {
            std::cout << "Error! Determinant is zero!\n";
            exit(-1);
        }
        Mat2D<T> alliedMatrix(rows, cols);
        Mat2D<T> tmp(rows - 1, cols - 1);
        int tmpRows = 0, tmpCols = 0;
        for (int rowsAllied = 0; rowsAllied < rows; rowsAllied++) {
            for (int colsAllied = 0; colsAllied < cols; colsAllied++) {
                tmpRows = 0;
                for (int i = 0; i < rows; i++) {
                    if (i == rowsAllied) {
                        continue;
                    }
                    tmpCols = 0;
                    for (int j = 0; j < cols; j++) {
                        if (j == colsAllied) {
                            continue;
                        }
                        tmp[tmpRows][tmpCols] = matrix[i][j];
                        tmpCols++;
                    }
                    tmpRows++;
                }
                alliedMatrix[rowsAllied][colsAllied] = tmp.determinant() * pow(-1, rowsAllied+colsAllied);
            }
        }
        Mat2D<T> transposed = alliedMatrix.transposition();
        return transposed / det;
    }

private:
    std::vector<std::vector<T>> matrix;
    int rows, cols;
};
#endif//MAT2D_H
