#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>

int main()
{
    setlocale(LC_ALL, "RUSSIAN");

    std::cout << "Введите количество элементов, кратное 4: ";

    std::list<int> L;
    std::copy(
        std::istream_iterator<int>(std::cin),
        std::istream_iterator<int>(),
        std::back_inserter(L)
    );

    if (L.size() % 4 != 0)
    {
        std::cout << "Ошибка: количество элементов должно быть кратно 4\n";
        return 0;
    }

    auto mid = L.begin();
    std::advance(mid, L.size() / 2); 


    for (auto i = L.begin(); i != mid; )
    {
        L.erase(i++); 
        if (i != mid) ++i; 
    }

    std::cout << "Результат: ";
    std::copy(L.begin(), L.end(),
        std::ostream_iterator<int>(std::cout, " "));

    return 0;
}