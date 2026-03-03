#include <iostream>
#include <unistd.h>
#include <cerrno>


struct calc {
    long long a;
    long long b;
    char operation;
    int err = 0;    //1 - incorrect input
                    //2 - Переполнение типа
};                  //3 - деление на 0

void print_struct(calc str){//удалить
    std::cout << "a = " << str.a << " b = " << str.b << " op " << str.operation;
}

int run(int argc, char** argv);
calc parcer(int argc, char** argv);//эта функция парсит аргументы запуска программы преобразует через to_double() и добовляет из в озвращаемую структуру

int main(int argc, char** argv){
    run(argc, argv);
}

int run(int argc, char** argv){
    calc s1 = parcer(argc, argv);
    check(s1);
    
    //print_struct(s1);
    return 0;
}



int check(calc str){
    if (errno == ERANGE){
        str.err = 2;//Переполнение типа
    }
    if (str.operation == '/' && str.b == 0){
        str.err = 3;//3 - деление на 0
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

