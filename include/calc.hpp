#ifndef CALC_HPP
#define CALC_HPP

struct calc
{
    long long a;
    long long b;
    char operation = 0;
    int err = 0; // 1 - incorrect input      4 - переполнение после вычсления
    long long result; // 2 - Переполнение типа    5 - вызов справки
}; // 3 - деление на 0

#endif // 3 - деление на 0