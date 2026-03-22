#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>

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

    int n;
    cout << "Введите количество элементов вектора: ";
    cin >> n;

    cout << "Введите " << n << " целых чисел через пробел: ";
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        V.push_back(x);
    }

    cout << "Исходный вектор: ";
    for (int val : V) {
        cout << val << " ";
    }
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
        for (int val : V) {
            cout << val << " ";
        }
    }
    cout << endl;

    return 0;
}