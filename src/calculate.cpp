#include "calculate.hpp"

int calculate(calc *str)
{
    switch (str->operation)
    {
    case '+':
        math_mosee::add(str);
        break;

    case '-':
        math_mosee::sub(str);
        break;

    case '*':
        if (math_mosee::mul(str->a, str->b, &str->result))
            str->err = 4;
        break;

    case '/':
        math_mosee::dic(str);
        break;

    case '!':
        str->result = math_mosee::fac(str->a, &str->err);
        break;

    case '^':
        math_mosee::exp(str);
        break;

    default:
        str->err = 1;
        break;
    }
    return 0;
}
