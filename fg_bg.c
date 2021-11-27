#include "headers.h"

int fg_bg(int x, char **y) {
    if (x != 2) {
        printf("Too many arguments");
        return EXIT_FAILURE;
    }
    int jno, pid;
    jno = toint(y[1]);
    if (jno == FAILURE) return EXIT_FAILURE;
    if (jno > job_index) {
        printf("%d: No such job", jno);
        return EXIT_FAILURE;
    }
    fo(i, exit_index +1) {
        if (listed[i] && listed[i]->job_no == jno) {
            pid = listed[i]->pid;
            if (kill(pid, SIGCONT) < 0) {
                perror("fg/bg");
            }
            if (!strcmp(y[0], "bg")) {
                printf("%d\n", pid);
                setpgid(pid, pid);
            } else {
                foreground_process = pid;
                if(listed[i]->job_no == job_index) job_index--;
                free(listed[i]);
                listed[i] = NULL;
                waitpid(pid, NULL, WUNTRACED);
            }
            return 0;
        }
    }
    printf("%d: No such job", jno);
    return EXIT_FAILURE;
}