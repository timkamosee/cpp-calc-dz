#include "parcer.hpp"


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
                                           {"help", 0, 0, 'h'},
                                           {"add", 0, 0, 1},
                                           {"sub", 0, 0, 2},
                                           {"mul", 0, 0, 3},
                                           {"div", 0, 0, 4},
                                           {"pow", 0, 0, 5},
                                           {"fact", 0, 0, 6},
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

        case 'h':

            s1.err = 5;
            has_h++;
            break;

        case 1:

            s1.operation = '+';
            has_o++;
            break;

        case 2:

            s1.operation = '-';
            has_o++;
            break;

        case 3:

            s1.operation = '*';
            has_o++;
            break;

        case 4:

            s1.operation = '/';
            has_o++;
            break;

        case 5:

            s1.operation = '^';
            has_o++;
            break;

        case 6:

            s1.operation = '!';
            has_o++;
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

long long to_ll(char *str)
{
    char *endptr = nullptr;
    long long out = strtoll(str, &endptr, 10); // 10 (последний аргумент) это система счисления
    return out;
}