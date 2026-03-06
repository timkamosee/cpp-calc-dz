#include "calc.hpp"


#include <iomanip>

#include <limits.h>
#include <unistd.h>

#include "mosee_math.hpp"



int calculate(calc *str);
int printres(calc *str);
int check(calc *str);
int run(int argc, char **argv);
calc parcer(int argc, char **argv); // эта функция парсит аргументы запуска программы преобразует
                                    // через to_double() и добовляет из в озвращаемую структуру

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

int printres(calc *str)
{
    if (str->err == 1)
    {
        printf("Некорректный ввод\n");
    }
    else if (str->err == 2)
    {
        printf("Переполнение ввода\n");
    }
    else if (str->err == 3)
    {
        printf("Деление на 0 запрещено\n");
    }
    else if (str->err == 6)
    {
        printf("Нельзя найти факториал отрицательного числа\n");
    }
    else if (str->err == 4)
    {
        printf("Переполнение после вычисления\n");
    }
    else if (str->err == 5)
    {
printf(
"Calculator — command line utility\n"
"\n"
"Usage:\n"
"  calculator -a <number> -b <number> [operation]\n"
"  calculator -a <number> --fact\n"
"  calculator -h | --help\n"
"\n"
"Arguments:\n"
"  -a, --arga <number>    First integer value\n"
"  -b, --argb <number>    Second integer value\n"
"\n"
"Operations (choose one):\n"
"      --add              Addition\n"
"      --sub              Subtraction\n"
"      --mul              Multiplication\n"
"      --div              Division\n"
"      --pow              Power (a^b, iterative)\n"
"      --fact             Factorial (recursive, uses only -a)\n"
"\n"
"Options:\n"
"  -h, --help             Show this help message\n"
"\n"
"Examples:\n"
"  calculator -a 5 -b 3 --add\n"
"  calculator -a 10 -b 2 --mul\n"
"  calculator -a 2 -b 10 --pow\n"
"  calculator -a 5 --fact\n"
"\n"
"Notes:\n"
"  Division by zero is checked.\n"
"  All operations check for integer overflow.\n"
"  Factorial ignores the -b argument.\n"
);
    }
    else
    {
        //std::cout << std::fixed << str->result << "\n";
        printf("%lld\n", str->result);
    }
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


