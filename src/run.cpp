#include "run.hpp"

int run(int argc, char **argv)
{
    calc s1 = parcer(argc, argv);
    check(&s1);
    if (s1.err == 0)
        calculate(&s1);
    printres(&s1);

    return 0;
}