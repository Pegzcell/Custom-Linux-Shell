#include "headers.h"

void processes(int signo) {
    if (foreground_process != FAILURE) return;
    int status, save = FAILURE;
    int pid = waitpid(-1, &status, WNOHANG | WCONTINUED | WUNTRACED);
    char BUFFER[300];
    if (pid <= 0) {
        return;
    }
    fo(i, exit_index + 1)
        if (listed[i] && listed[i]->pid == pid) {
            save = i;
            break;
        }
    if (save == FAILURE)
        return;
    if (WIFCONTINUED(status)) {
        printf("\n[continued]\n");
        listed[save]->status = 1;
    } else if (WIFSTOPPED(status)) {
        printf("\n[stopped]\n");
        listed[save]->status = 0;
    } else {
        sprintf(BUFFER, "\n[%swith pid %d exited %s]\n", listed[save]->name, pid,
                WIFEXITED(status) ? "normally" : "abnormally");
        if (listed[save]->job_no == job_index) job_index--;
        free(listed[save]);
        listed[save] = NULL;
        write(1, BUFFER, strlen(BUFFER));
    }
}

void ctrl_c(int signo) {
    if (foreground_process != FAILURE)
        if (kill(foreground_process, SIGINT) < 0)
            perror("ctrl c");
}

void ctrl_z(int signo) {
    if (foreground_process != FAILURE) {
        if (!listed[exit_index]) listed[exit_index] = (bgmap *) malloc(sizeof(bgmap));
        listed[exit_index]->job_no = ++job_index;
        listed[exit_index]->pid = foreground_process;
        listed[exit_index]->name = (char *) malloc(100);
        strcpy(listed[exit_index]->name, process_name);
        listed[exit_index]->status = 0;
        exit_index = (exit_index + 1) % MAX_VAL;
        //        if (setpgid(foreground_process, foreground_process) < 0)
        //        perror("Setpgid");
        if (kill(foreground_process, SIGTSTP) < 0)
            perror("ctrl z");
        else
            printf("\nStopped %sand pushed it to background\n", process_name);
    }
}

void ctrl_d() {
    fo(i, job_index) {
        if (listed[i] && !listed[i]->status) {
            kill(listed[i]->pid, SIGKILL);
        }
    }
    br;
    exit(0);
}
