#ifndef VECND_H
#define VECND_H
#include <vector>
template <class T>
class VecND {
public:
    VecND(int n) {
        v_size = n;
        vector.resize(v_size);
    }
    VecND(const VecND &arg) {
        v_size = arg.size;
        vector.resize(v_size);
        for (int i = 0; i < v_size; i++) {
            vector[i] = arg.vector[i];
        }
    }
    VecND &operator=(const VecND &arg) {
        v_size = arg.size;
        vector.resize(v_size);
        for (int i = 0; i < v_size; i++) {
            vector[i] = arg.vector[i];
        }
        return *this;
    }
    T &operator[](int ind) {
        if (ind < v_size) {
            return vector[ind];
        } else {
            std::cout << "Error! Out-of-bounds index!\n";
            exit(-1);
        }
    }
    void print() {
        if (v_size == 1) {
            std::cout << "( " << vector[0] << " )\n";
        } else {
            std::cout << "/ " << vector[0] << " \\\n";
            for (int i = 1; i < v_size - 1; i++) {
                std::cout << "| " << vector[i] << " |\n";
            }
            std::cout << "\\ " << vector[v_size - 1] << " /\n";
        }
    }

    int size(){
        return size;
    }

    void input() {
        for (int i = 0; i < v_size; i++) {
            std::cin >> vector[i];
        }
    }
private:
    std::vector<T> vector;
    int v_size;
};

#endif//VECND_H
