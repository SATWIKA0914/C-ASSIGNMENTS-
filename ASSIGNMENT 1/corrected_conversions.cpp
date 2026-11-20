#include <iostream>
int main() {
    int a{7};
    int b{2};
    double integerDivision{static_cast<double>(a / b)};
    double realDivision{static_cast<double>(a) / static_cast<double>(b)};
    char ch{static_cast<char>('A' + 2)};
    bool flag{true};
    std::cout << integerDivision << ' ' << realDivision << '\n';
    std::cout << ch << ' ' << static_cast<int>(ch) + 1 << '\n';
    std::cout << std::boolalpha << flag << '\n';
    return 0;
}
