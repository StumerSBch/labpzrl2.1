#include <iostream>
#include "Vector.h"

int main() {
    // Тест конструктора с массивом
    double arr[] = {1.1, 2.2, 3.3};
    Vector vec(arr, 3);

    std::cout << "Исходный вектор: ";
    for (auto it = vec.begin(); it != vec.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";

    // pushBack
    vec.pushBack(4.4);
    std::cout << "После pushBack(4.4): ";
    for (size_t i = 0; i < vec.size(); ++i)
        std::cout << vec[i] << " ";
    std::cout << "\n";

    // pushFront
    vec.pushFront(0.0);
    std::cout << "После pushFront(0.0): ";
    for (auto v : vec)
        std::cout << v << " ";
    std::cout << "\n";

    // insert
    vec.insert(9.9, 2);
    std::cout << "После insert(9.9, 2): ";
    for (const auto& val : vec)
        std::cout << val << " ";
    std::cout << "\n";

    // erase
    vec.erase(2, 2);
    std::cout << "После erase(2, 2): ";
    for (auto it = vec.begin(); it != vec.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";

    // popBack и popFront
    vec.popBack();
    vec.popFront();
    std::cout << "После popBack и popFront: ";
    for (auto val : vec)
        std::cout << val << " ";
    std::cout << "\n";

    // Поиск
    long long found = vec.find(2.2);
    std::cout << "Поиск 2.2: " << (found != -1 ? "Найдено" : "Не найдено") << "\n";

    // shrinkToFit
    vec.shrinkToFit();
    std::cout << "После shrinkToFit: size = " << vec.size() << ", capacity = " << vec.capacity() << "\n";

    return 0;
}