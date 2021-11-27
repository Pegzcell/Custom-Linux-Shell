#include "headers.h"

int echo1(int x, char **y)
{
    fo(i, x - 1)
    {
        printf("%s ", y[i + 1]);
    }
    br;
}