#include "headers.h"

int main() {
    printf("\e[1;1H\e[2J");
    printf("\x1b[1;5;33mPratham's Shell\x1b[0m\n");
    ptemplate(); //gets uname, hostname
    oldpwd = (char *) calloc(300, 1);
    size_t a_size = 300;
    exit_index = 0;
    job_index = 0;
    hist_index = 0;
    total_hist = 0;
    hist = (char **) calloc(sizeof(char *), MAX_HIST);
    listed = (bgmap **) calloc(sizeof(bgmap *), MAX_JOBS);
    fo(i, MAX_HIST) {
        hist[i] = (char *) calloc(303, 1);
    }
    def_out = dup(STDOUT_FILENO);
    def_in = dup(STDIN_FILENO);
    char *a;
    //
    signal(SIGCHLD, processes);
    signal(SIGINT, ctrl_c);
    signal(SIGTSTP, ctrl_z);
    //
    while (1) {
        dup2(def_out, STDOUT_FILENO);
        dup2(def_in, STDIN_FILENO);
        prompt_write(); //writes prompt
        foreground_process = FAILURE;
        if (getline(&a, &a_size, stdin) == -1) {
            ctrl_d();
        }
        commands(a);
    }
}
