#include "check.hpp"

int check(calc *str)
{
    if (str->operation == '/' && str->a == LLONG_MIN && str->b == -1)
    {
        str->err = 4;
    }
    if (str->operation == '!' && str->a < 0)
        str->err = 6;
    if (errno == ERANGE)
    {
        str->err = 2; // Переполнение типа
    }
    if (str->operation == '/' && str->b == 0)
    {
        str->err = 3; // 3 - деление на 0
    }
    return 0;
}
