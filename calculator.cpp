#include <iostream>
#include <unistd.h>
#include <cerrno>
#include <limits.h> 


struct calc {
    long long a;
    long long b;
    char operation;
    int err = 0;    //1 - incorrect input      4 - переполнение после выисления 
    double result = 0.0;  //2 - Переполнение типа
};                  //3 - деление на 0

long long to_ll(char* str){
    char** endptr;
    long long out = strtoll(str, endptr, 10); //10 (последний аргумент) это система счисления
    return out;
}

void print_struct(calc* str){//удалить
    std::cout << "a = " << str->a << " b = " << str->b << " op " << str->operation;
}

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
    calculate(&s1);
    printres(&s1);
    //print_struct(s1);
    return 0;
}

int printres(calc* str){
    if (str->err == 4) {
        std::cout << "переполнение после выисления";
    } else {
        std::cout << "Result = {" << str->result << "}\n";
    }
    return 0;
}

//сделать из этого head-only библиотеку >>
int mosee_add(calc* str){
    print_struct(str);
    if (LLONG_MAX - str->b <= str->a){
        str->err = 4;//4 - переполнение после выисления
    } else {
        std::cout << str->a << "=" << str->b << "==" << (double)str->a + (double)str->b ;
    str->result = (double)str->a + (double)str->b;}
    //str->result = (double)300;
    return 0;
}

int calculate(calc* str){
    switch (str->operation) {
        case '+':
            mosee_add(str);
            break;

        case '-':
            //code
            break;

        case '*':
            //code
            break;

        case '/':
            //code
            break;

        case '!':
            //code
            break;

        case '^':
            //code
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

    opterr = 0;
    int has_a = 0;
    int has_b = 0;
    int has_o = 0;
    int has_h = 0;
    while ((opt = getopt(argc, argv, "a:b:o:h")) != -1 && errno != ERANGE){
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
                
                std::cout << "help calc\n";
                has_h++;
                break;

            case '?':
            std::cout << "/unclown flag\n";
                s1.err = 1;// incorrect input
                break;
            
        }
        
    }
    if (!((has_a == 1 && has_b == 1 && has_o == 1) ^ has_h == 1)){
            s1.err = 1;// incorrect input
            std::cout << "// incorrect input\n";
        }


    

    // std::cout << "argc= " << argc << std::endl;
    // for(int i = 0; i < argc; i++){
    //     std::cout << argv[i] << std::endl;
    // }
    // calc s1;
    // s1.a = 1;
    // s1.b = 3;
    // s1.operation = 'r';
    return s1;
}

