#ifndef __COMMANDS_H
#define __COMMANDS_H


int cd0(int x, char **y);

int echo1(int x, char **y);

int pwd2(int x, char **y);

int ls3(int x, char **y);

int pinfo(int x, char **y);

int clear(int x, char **y);

int done(int x, char **y);

int repeat(int x, char **y);

int history(int x, char** y);

int jobs(int x, char** y);

int sig(int x, char** y);

int fg_bg(int x, char** y);

int replay(int x, char **y);

int key(char *fn);

int (*fn[])(int, char **) = {cd0, echo1, pwd2, ls3, pinfo, clear, done, repeat, history, jobs, sig, fg_bg, replay};

int sys_comm(int x, char **y);

#endif