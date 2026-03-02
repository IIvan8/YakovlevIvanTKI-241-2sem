#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <cctype>
#include <locale>

using namespace std;

/**
 * @brief Пользовательский итератор ввода для чтения символов
 * @tparam T Тип вводимых элементов
 */
template<typename T>
class ptin_iterator {
private:
    T current_value;
    bool end_of_stream;
    istream* input_stream;

public:
    using iterator_category = input_iterator_tag;
    using value_type = T;
    using difference_type = ptrdiff_t;
    using pointer = const T*;
    using reference = const T&;

    /**
     * @brief Конструктор по умолчанию (создает end-итератор)
     */
    ptin_iterator() : input_stream(nullptr), end_of_stream(true) {}

    /**
     * @brief Конструктор с потоком ввода
     * @param is Поток для чтения
     */
    explicit ptin_iterator(istream& is) : input_stream(&is), end_of_stream(false) {
        ++(*this);
    }

    /**
     * @brief Оператор разыменования
     * @return Текущее значение
     */
    const T& operator*() const { return current_value; }

    /**
     * @brief Оператор доступа к членам
     * @return Указатель на текущее значение
     */
    const T* operator->() const { return &current_value; }

    /**
     * @brief Префиксный инкремент
     * @return Ссылка на текущий итератор
     */
    ptin_iterator& operator++() {
        if (input_stream && !(*input_stream >> current_value)) {
            end_of_stream = true;
            input_stream = nullptr;
        }
        return *this;
    }

    /**
     * @brief Постфиксный инкремент
     * @return Копия итератора до инкремента
     */
    ptin_iterator operator++(int) {
        ptin_iterator temp = *this;
        ++(*this);
        return temp;
    }

    /**
     * @brief Оператор сравнения на равенство
     * @param other Другой итератор
     * @return true если итераторы равны
     */
    bool operator==(const ptin_iterator& other) const {
        return (end_of_stream && other.end_of_stream) ||
            (input_stream == other.input_stream && end_of_stream == other.end_of_stream);
    }

    /**
     * @brief Оператор сравнения на неравенство
     * @param other Другой итератор
     * @return true если итераторы не равны
     */
    bool operator!=(const ptin_iterator& other) const {
        return !(*this == other);
    }
};

/**
 * @brief Пользовательский итератор вывода для печати символов через пробел
 * @tparam T Тип выводимых элементов
 */
template<typename T>
class ptout_iterator {
private:
    bool first;

public:
    using iterator_category = output_iterator_tag;
    using value_type = void;
    using difference_type = void;
    using pointer = void;
    using reference = void;

    /**
     * @brief Конструктор по умолчанию
     */
    ptout_iterator() : first(true) {}

    /**
     * @brief Оператор присваивания - выводит значение в консоль
     * @param value Значение для вывода
     * @return Ссылка на текущий итератор
     */
    ptout_iterator& operator=(const T& value) {
        if (!first) cout << " ";
        cout << value;
        first = false;
        return *this;
    }

    /**
     * @brief Оператор разыменования
     * @return Ссылка на текущий итератор
     */
    ptout_iterator& operator*() { return *this; }

    /**
     * @brief Префиксный инкремент
     * @return Ссылка на текущий итератор
     */
    ptout_iterator& operator++() { return *this; }

    /**
     * @brief Постфиксный инкремент
     * @return Копия текущего итератора
     */
    ptout_iterator operator++(int) { return *this; }
};

/**
 * @brief Точка входа в программу
 * @return 0 при успешном выполнении
 *
 * Задание 12: Дан набор символов. Вывести все символы из исходного набора
 * в том же порядке, заменяя цифровые символы на символ подчеркивания.
 * Использовать итераторы ptin_iterator, ptout_iterator и алгоритм replace_copy_if.
 */
int main() {
    setlocale(LC_ALL, "Russian");

    cout << "Введите набор символов (для завершения ввода нажмите Ctrl+Z/Ctrl+D):" << endl;

    // Чтение символов с помощью ptin_iterator
    ptin_iterator<char> it(cin);
    ptin_iterator<char> end;

    vector<char> symbols;
    copy(it, end, back_inserter(symbols));

    // Вывод символов с заменой цифр на подчеркивание
    ptout_iterator<char> out;

    replace_copy_if(symbols.begin(), symbols.end(), out,
        [](unsigned char c) { return isdigit(c); },
        '_');

    cout << endl;

    return 0;
}