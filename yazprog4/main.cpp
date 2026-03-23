#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>
#include <iterator>

using namespace std;
using namespace std::placeholders;

struct less_abs : public function<bool(int, int)> {
    bool operator()(int a, int b) const {
        return abs(a) < abs(b);
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    int K;
    vector<int> V;

    cout << "Введите целое число K (> 0): ";
    cin >> K;

    if (K <= 0) {
        cout << "Ошибка: K должно быть больше 0" << endl;
        return 1;
    }

    cout << "Введите целые числа через пробел (Ctrl+Z для завершения ввода): ";
    copy(istream_iterator<int>(cin), istream_iterator<int>(), back_inserter(V));

    if (V.empty()) {
        cout << "Вектор пуст. Завершение программы." << endl;
        return 0;
    }

    cout << "Исходный вектор: ";
    copy(V.begin(), V.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    auto new_end = remove_if(V.begin(), V.end(),
        bind(less_abs(), _1, K));

    V.erase(new_end, V.end());

    cout << "Размер преобразованного вектора: " << V.size() << endl;

    cout << "Элементы преобразованного вектора: ";
    if (V.empty()) {
        cout << "вектор пуст";
    }
    else {
        copy(V.begin(), V.end(), ostream_iterator<int>(cout, " "));
    }
    cout << endl;

    return 0;
}