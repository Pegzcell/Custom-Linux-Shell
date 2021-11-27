#include "headers.h"
#include "commands.h"

int key(char *fn) {
    int r;
    if (!strcmp(fn, "cd"))
        r = 0;
    else if (!strcmp(fn, "echo"))
        r = 1;
    else if (!strcmp(fn, "pwd"))
        r = 2;
    else if (!strcmp(fn, "ls"))
        r = 3;
    else if (!strcmp(fn, "pinfo"))
        r = 4;
    else if (!strcmp(fn, "clear"))
        r = 5;
    else if (!strcmp(fn, "exit"))
        r = 6;
    else if (!strcmp(fn, "repeat"))
        r = 7;
    else if (!strcmp(fn, "history"))
        r = 8;
    else if (!strcmp(fn, "jobs"))
        r = 9;
    else if (!strcmp(fn, "sig"))
        r = 10;
    else if (!strcmp(fn, "fg") || !strcmp(fn, "bg"))
        r = 11;
    else if (!strcmp(fn, "replay"))
        r = 12;
    else
        r = -1;
    return r;
}

int clear(int x, char **y) {
    printf("\e[1;1H\e[2J");
    printf("\x1b[1;5;33mPratham's Shell\x1b[0m\n");
}

int done(int x, char **y) {
    printf("\e[1;1H\e[2J");
    exit(0);
}

int repeat(int x, char **y) {
    int iter, r;
    if (x > 2) {
        iter = toint(y[1]);
        if (iter == FAILURE) return EXIT_FAILURE;
        x -= 2;
        y = &y[2];
        r = key(y[0]);
        fo(i, iter) {
            if (r != -1)
                fn[r](x, y);
            else
                sys_comm(x, y);
        }
    } else {
        printf("Too few arguments\n");
        return EXIT_FAILURE;
    }
}

int replay(int x, char **y) {
    int iter, r;
    char **sleep_intruction = (char**)calloc(3, sizeof(char *));
    int interval, period, times;
    if (x >= 6) {
        if (!strcmp(y[1], "-command")) {
            if (!strcmp(y[x - 4], "-interval")) {
                interval = toint(y[x - 3]);
                if (interval == FAILURE) return EXIT_FAILURE;
                if (!strcmp(y[x - 2], "-period")) {
                    period = toint(y[x - 1]);
                    if (period == FAILURE) return EXIT_FAILURE;
                    times = period / interval;
                    sleep_intruction[0] = (char*)calloc(10,1);
                    sleep_intruction[1] = (char*)calloc(10,1);
                    strcpy(sleep_intruction[0],"sleep");
                    sprintf(sleep_intruction[1], "%d", interval);
                    y[x - 4] = NULL;
                    y = &y[2];
                    x -= 6;
                    r = key(y[0]);
                    fo(i, times) {
                        sys_comm(2, sleep_intruction);
                        if (r != -1)
                            fn[r](x, y);
                        else
                            sys_comm(x, y);
                    }
                    sprintf(sleep_intruction[1], "%d", period % interval);
                    sys_comm(2, sleep_intruction);
                    return 0;
                }
            }
        }
        printf("Incorrect arguments\n");
        return EXIT_FAILURE;
    } else {
        printf("Too few arguments\n");
        return EXIT_FAILURE;
    }
}

int execute(char *command) {
    char **tokens = (char **) calloc(20, sizeof(char *));
    int x = 0;
    char delimiters[] = " \t\n\v\f\r";
    tokens[x] = strtok(command, delimiters);
    while (tokens[x++] != NULL) {
        tokens[x] = strtok(NULL, delimiters);
    }
    int r = key(tokens[0]);
    if (r != -1)
        fn[r](x - 1, tokens);
    else
        sys_comm(x - 1, tokens);
}

int io(char *command) {
    char *todo = (char *) calloc(100, 1);
    char *input_file = (char *) calloc(100, 1);
    char *output_file = (char *) calloc(100, 1);
    strcpy(todo, command);
    int in_red = 0, out_red = 0, append_flag = 0;

    fo(i, strlen(command)) {
        if (command[i] == '<') {
            strcpy(input_file, command);
            in_red = i;
            todo[i] = '\0';
            input_file += i + 1;
        } else if (command[i] == '>') {
            strcpy(output_file, command);
            out_red = i;
            if (!in_red) {
                todo[i] = '\0';
            } else {
                input_file[i - in_red - 1] = '\0';
            }
            output_file += i + 1;
            if (output_file[0] == '>') {
                append_flag = 1;
                output_file += 1;
            }
            break;
        }
    }
    // printf("-%s-%s-%s-%d-%d\n", todo, input_file, output_file, in_red, out_red);
    int new_in, new_out;
    if (out_red) {
        output_file = strtok(output_file, " ");
        if (append_flag) {
            new_out = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        } else {
            new_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        }
        if (new_out < 0) {
            perror("Output output_file");
            return EXIT_FAILURE;
        }
        dup2(new_out, STDOUT_FILENO);
    }
    if (in_red) {
        input_file = strtok(input_file, " ");
        new_in = open(input_file, O_RDONLY);
        if (new_in < 0) {
            perror("Input file");
            return EXIT_FAILURE;
        }
        dup2(new_in, STDIN_FILENO);
    }
    execute(todo);
}

int piping(char *command) {
    char **parts = (char **) calloc(20, sizeof(char *));
    int x = 0;
    char delimiters[] = "|";
    parts[x] = strtok(command, delimiters);
    while (parts[x++] != NULL) {
        parts[x] = strtok(NULL, delimiters);
    }
    int pipefd[2], i = 0;
    char BUFFER[PIPE_BUF];
    while (i < x - 2) {
        if (pipe(pipefd) < 0) {
            perror("pipe");
            return EXIT_FAILURE;
        }
        dup2(pipefd[1], STDOUT_FILENO);
        io(parts[i]);
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        // scanf("%s--",BUFFER);
        // close(pipefd[0]);
        // dup2(def_out,STDOUT_FILENO);
        // printf("%d-%s\n",x,BUFFER);
        i++;
    }
    dup2(def_out, STDOUT_FILENO);
    io(parts[i]);
}

int commands(char *a) {
    a[strcspn(a, "\n")] = '\0'; //removes trailing newline
    char **commands = (char **) calloc(100, sizeof(char *));
    int to = (hist_index - 1) >= 0 ? hist_index - 1 : hist_index - 1 + MAX_HIST;
    if (strcmp(hist[to], a) && strcmp(a, "")) {
        strcpy(hist[hist_index], a);
        hist_index = (hist_index + 1) % MAX_VAL;
        if (total_hist != MAX_VAL)
            total_hist += 1;
    }
    int x = 0;
    commands[x] = strtok(a, ";");
    while (commands[x++] != NULL) {
        commands[x] = strtok(NULL, ";");
    }
    fo(i, x - 1) {
        piping(commands[i]);
        //io(commands[i]);
        //execute(commands[i]);
    }
}
