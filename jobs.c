#include "headers.h"

int jobs(int x, char **y) {
    int k = 0, r = 0, s = 0;
    for (int i = 1; i < x; i++) {
        if (y[i][0] == '-') {
            for (int j = 1; j < strlen(y[i]); j++) {
                if (y[i][j] == 'r' && !r) {
                    r = 1;
                    k += r;
                } else if (y[i][j] == 's' && !s) {
                    s = 2;
                    k += s;
                } else {
                    printf("jobs: %c: Unrecognized flag", y[i][j]);
                    break;
                }
            }
        } else {
            printf("jobs: too many arguments");
            break;
        }
    }
    // printf("?%d?,%d\n", job_index,k);
    bubbleSort(listed, exit_index + 1);
    if (k == 1) {
        fo(i, exit_index + 1) {
            if (listed[i] && listed[i]->status)
                printf("[%d] %s %s [%d]\n", listed[i]->job_no, listed[i]->status ? "Running" : "Stopped",
                       listed[i]->name, listed[i]->pid);
        }
    } else if (k == 2) {
        fo(i, exit_index + 1) {
            if (listed[i] && !listed[i]->status)
                printf("[%d] %s %s [%d]\n", listed[i]->job_no, listed[i]->status ? "Running" : "Stopped",
                       listed[i]->name, listed[i]->pid);
        }
    } else {
        fo(i, exit_index + 1) {
            if (listed[i])
                printf("[%d] %s %s [%d]\n", listed[i]->job_no, listed[i]->status ? "Running" : "Stopped", listed[i]->name, listed[i]->pid);
        }
    }
}