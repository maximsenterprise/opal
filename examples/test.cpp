#include "iostream"
#include <string>

template <typename T>

void println(T &val) {

    std::cout << val << std::endl;
}

std::string readline() {
    std::string out;

    std::cin >> out;

    return out;
}

int main() {
    std::string in = readline();
    println(in);
    return 0;
}
