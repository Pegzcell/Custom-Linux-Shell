#ifndef __HEADERS_H
#define __HEADERS_H

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdlib.h>
#include <dirent.h>
#include <signal.h>
#include <sys/stat.h>
#include <grp.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>

int TILDE_LEN, exit_index, job_index, total_hist, hist_index, foreground_process, def_in, def_out;

#define br printf("\n")
#define fo(i, n) for (int i = 0; i < n; i++)
#define Fo(i, k, n) for (int i = k; k < n ? i < n : i > n; k < n ? i += 1 : i -= 1)

char uname[20], hname[300], pt[300], tilde[300], process_name[300];
char *oldpwd;

typedef struct bg_map {
    int job_no;
    int pid;
    char *name;
    int status;
} bgmap;

#define MAX_VAL 20
#define MAX_HIST 20
#define MAX_JOBS 100
#define FAILURE -999

bgmap **listed;
char **hist;

int toint(char *y);

void bubbleSort(bgmap *arr[], int n);

int ptemplate();

int prompt_write();

char *make_path(char *text);

int commands(char *a);

int execute(char *a);

void processes(int signo), ctrl_c(int signo), ctrl_z(int signo), ctrl_d();

#endif