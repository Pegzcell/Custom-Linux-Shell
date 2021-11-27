#include "headers.h"

int ptemplate() {
    /*uname = getenv("USER");
    hname = getenv("HOSTNAME");
    printf("%s----%s",uname,hname);*/
    gethostname(hname, sizeof(hname));
    getlogin_r(uname, sizeof(uname));
    strcat(pt, "<");
    strcat(pt, uname);
    strcat(pt, "@");
    strcat(pt, hname);
    strcat(pt, ":");
    getcwd(tilde, sizeof(tilde));
    /* to get tilde:
    char cwd[300];
    getcwd(cwd, 300);
    int marker = 0;
    fo(i, strlen(f)) {
        if (f[i] == '/') {
            marker = i + 1;
        }
    }
    f[marker] = '\0';
    chdir(f);
    getcwd(tilde, sizeof(tilde));*/
    TILDE_LEN = strlen(tilde);
}

int prompt_write() {
    char *cwd = (char *) malloc(300);
    char prompt[300];
    //char cwd_2[300];
    strcpy(prompt, pt);
    getcwd(cwd, 300);
    strcat(prompt, make_path(cwd));
    /*if (strlen(cwd) > TILDE_LEN) {
        strcpy(cwd_2, cwd);
        cwd_2[TILDE_LEN] = '\0';
        if (!strcmp(tilde, cwd_2)) {
            cwd = cwd + TILDE_LEN;
            strcat(prompt, "~");
            strcat(prompt, cwd);
        } else {
            strcat(prompt, cwd);
        }
    } else if (!strcmp(tilde, cwd)) {
        strcat(prompt, "~");
    } else {
        strcat(prompt, cwd);
    }*/
    strcat(prompt, ">");
    printf("\n%s%s%s", "\x1b[1;31m", prompt, "\x1b[0m");
}
