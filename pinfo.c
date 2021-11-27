#include "headers.h"

int pinfo(int x, char **y) {
    char id[40];
    if (x == 1) {
        sprintf(id, "%d", getpid());
    } else if (x == 2) {
        sprintf(id, "%s", y[1]);
    } else {
        printf("Too many arguments");
        return EXIT_FAILURE;
    }

    char target[30] = "/proc/";
    char exe_target[30];
    char pathname[300] = "";
    strcat(target, id);
    strcpy(exe_target, target);
    strcat(target, "/stat");
    strcat(exe_target, "/exe");
    readlink(exe_target, pathname, 300);
    int fd = open(target, O_RDONLY);
    if (fd < 0) {
        printf("Process not found\n");
        return EXIT_FAILURE;
    }
    char BUFFER[500];
    read(fd, BUFFER, 500);
    char **data = (char **) calloc(500, sizeof(char *));
    int d = 0;
    data[d] = strtok(BUFFER, " ");
    while (data[d++] != NULL) {
        data[d] = strtok(NULL, " ");
    }
    char ground = '?';
    int pid = toint(data[0]);
    if (pid == foreground_process) ground = '+';
    else {
        fo(j, exit_index + 1) {
            if (listed[j] && pid == listed[j]->pid)
                ground = '\0';
                break;
        }
    }
    if (ground == '?')
        ground = strcmp(data[4], data[7]) ? '\0' : '+';
    printf("Pid -- %s\n", data[0]);
    printf("Process Status -- %s%c\n", data[2], ground);
    printf("Virtual Memory -- %s bytes\n", data[22]);
    printf("Executable Path -- %s\n", strlen(pathname) ? make_path(pathname) : "None");
}