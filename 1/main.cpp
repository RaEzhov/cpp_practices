#include <iostream>
#include <cmath>

uint64_t factorial(int n){
    if (n == 0 || n == 1){
        return 1;
    }
    return factorial(n-1) * n;
}

void squareEquation(int a, int b, int c){
    if (a == 0){
        if (b == 0) {
            if (c == 0) {
                std::cout << "R\n";
            } else {
                std::cout << "No solutions\n";
            }
        } else {
            std::cout << "x = " << c/(-b) << '\n';
        }
    } else {
        int d;
        d = b * b - 4 * a * c;
        if (d < 0){
            std::cout << "No solutions\n";
        } else if (d == 0){
            std::cout << "x = " << -b/(2*a) << '\n';
        } else {
            double x1 = (-b - sqrt(d)) / (2 * a);
            double x2 = (-b + sqrt(d)) / (2 * a);
            std::cout << "x1 = " << x1 << "\nx2 = " << x2 << '\n';
        }
    }
}

void primeNumbers(int a, int b){
    auto arr = new bool[b];
    for (int i = 0; i < b; i++){
        arr[i] = true;
    }
    for (int i = 2; i < b; i++){
        if (arr[i]){
            for (int j = 2 * i; j < b; j+=i){
                arr[j] = false;
            }
        }
    }
    for (int i = a+1; i < b; i++){
        if (arr[i]){
            std::cout << i << ' ';
        }
    }
    std::cout << '\n';
    delete[] arr;
}

void binary(int num){
    if (num != 0){
        binary(num / 2);
        std::cout << num % 2;
    }
}

double geomProg(double a, double q, int e){
    double precision = pow(0.1, e);
    double s = 1;
    double q_pow = pow(q, 2);
    while (a*q_pow >= precision){
        s += q_pow;
        q_pow *= q*q;
    }
    return s * a;
}

bool isLatinLetter(char c){
    return c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z';
}

int main() {
    std::cout << factorial(5) << std::endl;
    squareEquation(1,2,-1);
    primeNumbers(1, 100);
    binary(10);std::cout << '\n';
    std::cout << geomProg(0.8, 0.3, 3);
    std::cout << isLatinLetter('a');
    return 0;
}
