#include <iostream>
#include <unistd.h>
#include <cerrno>


struct calc {
    long long a;
    long long b;
    char operation;
};

void print_struct(calc str){//удалить
    std::cout << "a = " << str.a << " b = " << str.b << " op " << str.operation;
}

calc parcer(int argc, char** argv);//эта функция парсит аргументы запуска программы преобразует через to_double() и добовляет из в озвращаемую структуру

int main(int argc, char** argv){
    calc s1 = parcer(argc, argv);
    if (errno == ERANGE){
        std::cout << "Переполнение типа\n";
        return 0;
    }
    print_struct(s1);
    return 0;
}

long long to_ll(char* str){
    char** endptr;
    long long out = strtoll(str, endptr, 10); //10 (последний аргумент) это система счисления
    return out;
}

calc parcer(int argc, char** argv){
    int opt;
    calc s1;

    opterr = 0;
    while ((opt = getopt(argc, argv, "a:b:o:h")) != -1){
        switch (opt) {
            case 'a':
                s1.a = to_ll(optarg);
                break;

            case 'b':
                s1.b = to_ll(optarg);
                break;

            case 'o':
                s1.operation = optarg[0];
                break;
            
            case 'h':
                //help()
                std::cout << "help calc\n"
                break;

            case '?':
                std::cout << "Incorrect input\n" << optarg;
                //help()
                break;
            
        }
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

