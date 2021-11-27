#include "headers.h"

int sig(int x, char **y) {
    int jno, ssig, pid;
    if (x == 3) {
        jno = toint(y[1]);
        if (jno == FAILURE) return EXIT_FAILURE;
        ssig = toint(y[2]);
        if (ssig == FAILURE) return EXIT_FAILURE;
    } else {
        printf("sig: Incorrect arguments");
        return EXIT_FAILURE;
    }
    if (jno > job_index) {
        printf("%d: No such job", jno);
        return EXIT_FAILURE;
    }
    fo(i, exit_index + 1) {
        if (listed[i] && listed[i]->job_no == jno) {
            pid = listed[i]->pid;
            if (kill(pid, ssig) < 0) {
                perror("sig:");
            }
            return 0;
        }
    }
    printf("%d: No such job", jno);
    return EXIT_FAILURE;
}
