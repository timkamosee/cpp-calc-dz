#include <cerrno>
#include <getopt.h>
#include <iomanip>
#include <iostream>
#include <limits.h>
#include <unistd.h>

#include "mosee_math.hpp"

#ifndef CALC_STRUCT_DEFINED
#define CALC_STRUCT_DEFINED

struct calc
{
    long long a;
    long long b;
    char operation = 0;
    int err = 0; // 1 - incorrect input      4 - переполнение после вычсления
    long long result; // 2 - Переполнение типа    5 - вызов справки
}; // 3 - деление на 0

#endif // 3 - деление на 0

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

long long to_ll(char *str)
{
    char *endptr = nullptr;
    long long out = strtoll(str, &endptr, 10); // 10 (последний аргумент) это система счисления
    return out;
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
        printf("Calculator — command line utility\n"
               "\n"
               "Usage:\n"
               "  calculator -a <number> -b <number> -o <operation>\n"
               "  calculator -h\n"
               "\n"
               "Options:\n"
               "  -a <number>        First integer value\n"
               "  -b <number>        Second integer value\n"
               "  -o <operation>     Operation to perform\n"
               "  -h                 Show this help message\n"
               "\n"
               "Available operations:\n"
               "  add        Addition\n"
               "  sub        Subtraction\n"
               "  mul        Multiplication\n"
               "  div        Division\n"
               "  pow        Power (iterative)\n"
               "  fact       Factorial (recursive, uses -a only)\n"
               "\n"
               "Notes:\n"
               "  Division by zero is checked.\n"
               "  All operations check for overflow.\n"
               "  Factorial ignores -b parameter.\n");
    }
    else
    {
        std::cout << std::fixed << str->result << "\n";
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

calc parcer(int argc, char **argv)
{
    int opt;
    calc s1;
    int option_index = 0;
    opterr = 0;
    int has_a = 0;
    int has_b = 0;
    int has_o = 0;
    int has_h = 0;
    static struct option long_options[] = {{"arga", 1, 0, 'a'},
                                           {"argb", 1, 0, 'b'},
                                           {"operation", 1, 0, 'o'},
                                           {"help", 0, 0, 'h'},
                                           {0, 0, 0, 0}};
    while ((opt = getopt_long(argc, argv, "a:b:o:h", long_options, &option_index)) != -1 &&
           errno != ERANGE)
    {
        switch (opt)
        {
        case 'a':
            s1.a = to_ll(optarg);
            has_a++;
            break;

        case 'b':
            s1.b = to_ll(optarg);
            has_b++;
            break;

        case 'o':
            s1.operation = optarg[0];
            has_o++;
            break;

        case 'h':

            s1.err = 5;
            has_h++;
            break;

        case '?':

            s1.err = 1; // incorrect input
            break;
        }
    }
    if (!((has_a == 1 && has_b == 1 && has_o == 1 && has_h == 0) ||
          (has_a == 1 && has_b == 0 && has_o == 1 && has_h == 0 && (s1.operation == '!')) ||
          (has_a == 0 && has_b == 0 && has_o == 0 && has_h == 1)))
    {
        s1.err = 1;
    }
    return s1;
}
