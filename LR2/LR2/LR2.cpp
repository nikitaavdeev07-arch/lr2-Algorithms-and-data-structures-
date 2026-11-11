// LR2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <utility>
#include <chrono>

using namespace std;
using namespace chrono;

// Шаблонный класс Pair<T1, T2>
// Хранит два значения произвольных типов

template <typename T1, typename T2>
class Pair {
private:
    T1 first_;   // первое значение
    T2 second_;  // второе значение

public:
    // Конструктор по умолчанию: O(1)
    Pair() : first_(), second_() {}

    // Конструктор с параметрами: O(1)
    Pair(const T1& first, const T2& second)
        : first_(first), second_(second) {}

    // Конструктор копирования (неявный): O(1)
    Pair(const Pair&) = default;

    // Геттеры: O(1)
    T1 getFirst()  const { return first_; }
    T2 getSecond() const { return second_; }

    // Сеттеры: O(1)
    void setFirst(const T1& value) { first_ = value; }
    void setSecond(const T2& value) { second_ = value; }

    void print() const {
        cout << "(" << first_ << ", " << second_ << ")";
    }
};

int main() {
    setlocale(LC_ALL, "ru");

    // --- int + string ---
    Pair<int, string> p1(42, "ответ");
    cout << "p1 = "; p1.print(); cout << endl;

    p1.setFirst(100);
    p1.setSecond("изменено");
    cout << "p1 после сеттеров = "; p1.print(); cout << endl;
    cout << "getFirst = " << p1.getFirst()
        << ", getSecond = " << p1.getSecond() << "\n\n";

    // --- double + char ---
    Pair<double, char> p2(3.14, 'A');
    cout << "p2 = "; p2.print(); cout << endl;
    p2.setFirst(2.71);
    p2.setSecond('Z');
    cout << "p2 после сеттеров = "; p2.print(); cout << "\n\n";

    // --- вложенные шаблоны: Pair<string, Pair<int,int>> ---
    Pair<int, int> inner(1, 2);
    Pair<string, Pair<int, int>> p3("точка", inner);
    cout << "p3 = (" << p3.getFirst() << ", ("
        << p3.getSecond().getFirst() << ", "
        << p3.getSecond().getSecond() << "))\n\n";

    // --- сравнение с std::pair по производительности ---
    const int N = 1'000'000;

    auto t1 = high_resolution_clock::now();
    Pair<int, int> sumMine{ 0,0 };
    for (int i = 0; i < N; ++i) {
        Pair<int, int> p(i, i);
        sumMine.setFirst(sumMine.getFirst() + p.getFirst());
        sumMine.setSecond(sumMine.getSecond() + p.getSecond());
    }
    auto t2 = high_resolution_clock::now();

    auto t3 = high_resolution_clock::now();
    std::pair<int, int> sumStd{ 0,0 };
    for (int i = 0; i < N; ++i) {
        std::pair<int, int> p(i, i);
        sumStd.first += p.first;
        sumStd.second += p.second;
    }
    auto t4 = high_resolution_clock::now();

    auto msMine = duration_cast<microseconds>(t2 - t1).count();
    auto msStd = duration_cast<microseconds>(t4 - t3).count();

    cout << "=== Сравнение с std::pair (N = " << N << ") ===\n";
    cout << "Pair<T1,T2> : " << msMine << " мкс\n";
    cout << "std::pair   : " << msStd << " мкс\n";

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
