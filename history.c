#include "headers.h"

int history(int x, char** y) {
    int t, digit;
    if (x == 1)
        t = 20;
    else if (x == 2) {
        t = toint(y[1]);
        if (t == FAILURE) return EXIT_FAILURE;
    } else {
        printf("Too many arguments");
        return EXIT_FAILURE;
    }
    t = t > total_hist ? total_hist : t;
    int ii = hist_index - t >=0 ? hist_index - t : hist_index - t +20;
    fo(i, t) {
        printf("%s\n", hist[ii]);
        ii = (ii + 1) % MAX_VAL;
    }
}