#include "headers.h"

void swap(bgmap *xp, bgmap *yp) {
    bgmap temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(bgmap *arr[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++)

        // Last i elements are already in place
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] && arr[j + 1] && strcmp(arr[j]->name, arr[j + 1]->name) > 0)
                swap(arr[j], arr[j + 1]);
}

int toint(char *y) {
    int n = 0, digit;
    fo(i, strlen(y)) {
        digit = y[i] - '0';
        if (digit > 9 || digit < 0) {
            printf("%s: not a number\n", y);
            return FAILURE;
        }
        n = n * 10 + digit;
    }
    return n;
}