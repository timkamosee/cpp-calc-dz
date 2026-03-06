#include "calc.hpp"
#include "parcer.hpp"
#include "printers.hpp"
#include "check.hpp"
#include <iomanip>


#include <unistd.h>

#include "mosee_math.hpp"



int calculate(calc *str);
int printres(calc *str);

int run(int argc, char **argv);


int main(int argc, char **argv)
{
    run(argc, argv);
}

int run(int argc, char **argv)
{
    calc s1 = parcer(argc, argv);
    check(&s1);
    if (s1.err == 0)
        calculate(&s1);
    printres(&s1);

    return 0;
}



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




