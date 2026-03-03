#include <iostream>
#include <unistd.h>
#include <cerrno>
#include <limits.h> 
#include <getopt.h>
#include <iomanip>
#define CALC_STRUCT_DEFINED
#include "mosee_math.hpp"

struct calc {
    long long a;
    long long b;
    char operation;
    int err = 0;      //1 - incorrect input      4 - переполнение после выисления 
    long long result; //2 - Переполнение типа
};                    //3 - деление на 0

int calculate(calc* str);
int printres(calc* str);
int check(calc* str);
int run(int argc, char** argv);
calc parcer(int argc, char** argv);//эта функция парсит аргументы запуска программы преобразует через to_double() и добовляет из в озвращаемую структуру

int main(int argc, char** argv){
    run(argc, argv);
}

int run(int argc, char** argv){
    calc s1 = parcer(argc, argv);
    check(&s1);
    if(s1.err == 0)calculate(&s1);
    printres(&s1);

    return 0;
}

long long to_ll(char* str){
    char* endptr = nullptr;
    long long out = strtoll(str, &endptr, 10); //10 (последний аргумент) это система счисления
    return out;
}

void print_struct(calc* str){//удалить
    std::cout << "a = " << str->a << " b = " << str->b << " op " << str->operation;
}




int printres(calc* str){
    if ( str->err == 1) {
        std::cout << "Некорректный ввод\n";
    } else if ( str->err == 2) {
        std::cout << "Переполнение ввода\n";
    } else if ( str->err == 3) {
        std::cout << "Деление на 0 запрещено\n";
    } else if (str->err == 4) {
        std::cout << "Переполнение после вычисления\n";
    } else if (str->err == 5) {
        std::cout << "Calculator — command line utility

Usage:
  calculator -a <number> -b <number> -o <operation>
  calculator -h

Options:
  -a <number>        First integer value
  -b <number>        Second integer value
  -o <operation>     Operation to perform
  -h                 Show this help message

Available operations:
  add        Addition
  sub        Subtraction
  mul        Multiplication
  div        Division
  pow        Power (iterative)
  fact       Factorial (recursive, uses -a only)

Notes:
  • Division by zero is checked.
  • All operations check for overflow.
  • Factorial ignores -b parameter.\n";
    } else {
        std::cout << std::fixed << str->result << "\n";
    }
    return 0;
}


int calculate(calc* str){
    switch (str->operation) {
        case '+':
            math_mosee::add(str);
            break;

        case '-':
            math_mosee::sub(str);
            break;

        case '*':
            if(math_mosee::mul(str->a, str->b, &str->result))str->err = 4;
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
            //code error
            break;
    }
    return 0;
}


int check(calc* str){
    if (errno == ERANGE){
        str->err = 2;//Переполнение типа
    }
    if (str->operation == '/' && str->b == 0){
        str->err = 3;//3 - деление на 0
    }
    return 0;
}

calc parcer(int argc, char** argv){
    int opt;
    calc s1;
    int option_index = 0;
    opterr = 0;
    int has_a = 0;
    int has_b = 0;
    int has_o = 0;
    int has_h = 0;
    static struct option long_options[] = {
        {"arga",  1, 0, 'a'},
        {"argb",  1, 0, 'b'},
        {"operation",  1, 0, 'o'},
        {"help", 0,       0, 'h'},
        {0, 0, 0, 0}
    };
    while ((opt = getopt_long(argc, argv, "a:b:o:h", long_options, &option_index)) != -1 && errno != ERANGE){
        switch (opt) {
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
            
                s1.err = 1;// incorrect input
                break;
        }
    }
    if (!((has_a == 1 && has_b == 1 && has_o == 1) ^ (has_h == 1))){
            s1.err = 1;
        }
    return s1;
}

