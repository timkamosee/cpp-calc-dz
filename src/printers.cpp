#include "printers.hpp"

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