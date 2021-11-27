#include "headers.h"

int sys_comm(int x, char **y) {
    int forkReturn = fork();
    int check, valid;
    if (forkReturn == 0) {
        // Child process
        if (y[x - 1][0] == '&')
            y[x - 1] = NULL;
        y[x] = NULL;
        if (execvp(y[0], y) == -1) {
            printf("%s: process_name not found\n", y[0]);
            return EXIT_FAILURE;
        }
        exit(0);
    } else {
        // Parent process
        char ground = y[x - 1][0];
        int status_fork;
        strcpy(process_name, "");
        fo(i, x - 1) {
            strcat(process_name, y[i]);
            strcat(process_name, " ");
        }
        if (ground == '&') {
            printf("%d\n", forkReturn);
            setpgid(forkReturn, forkReturn);
            if (!listed[exit_index]) listed[exit_index] = (bgmap *) malloc(sizeof(bgmap));
            listed[exit_index]->job_no = ++job_index;
            listed[exit_index]->pid = forkReturn;
            listed[exit_index]->name = (char *) malloc(100);
            strcpy(listed[exit_index]->name, process_name);
            listed[exit_index]->status = 1;
            exit_index = (exit_index + 1) % MAX_VAL;

        } else {
            strcat(process_name, y[x - 1]);
            strcat(process_name, " ");
            foreground_process = forkReturn;
            waitpid(forkReturn, NULL, WUNTRACED);
        }
    }
}