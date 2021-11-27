#include "headers.h"

int pwd2(int x, char **y)
{
    char cwd[300];
    getcwd(cwd, 300);
    printf("%s\n", cwd);
}