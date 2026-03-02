#include <iostream>
#include <unistd.h>



struct calc {
    double a;
    double b;
    char operation;
};

calc parcer(int argc, char** argv);

int main(int argc, char** argv){
    calc s1 = parcer(argc, argv);
    //calc s1;
    // run();
    return 0;
}

calc parcer(int argc, char** argv){
    int opt;
    calc s1;
    while ((opt = getopt(argc, argv, "a:b:o:h")) != -1){
        switch (opt) {
            case 'a':
                //преобразование к Double и добавление в структуру
                break;

            case 'b':
                s//преобразование к Double и добавление в структуру
                break;

            case 'o':
                //преобразование к Double и добавление в структуру
                break;
            
            case 'h':
                //преобразование к Double и добавление в структуру
                break;
            
        }
    }




    // std::cout << "argc= " << argc << std::endl;
    // for(int i = 0; i < argc; i++){
    //     std::cout << argv[i] << std::endl;
    // }
    calc s1;
    s1.a = 1;
    s1.b = 3;
    s1.operation = 'r';
    return s1;
}

