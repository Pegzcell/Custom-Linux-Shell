#include "headers.h"

char *make_path(char *text) {
    char *text_2 = (char *) calloc(300, 1);
    char *path = (char *) calloc(300, 1);
    if (strlen(text) > TILDE_LEN) {
        strcpy(text_2, text);
        text_2[TILDE_LEN] = '\0';
        if (!strcmp(tilde, text_2)) {
            text = text + TILDE_LEN;
            strcat(path, "~");
            strcat(path, text);
        } else {
            strcat(path, text);
        }
    } else if (!strcmp(tilde, text)) {
        strcat(path, "~");
    } else {
        strcat(path, text);
    }
    return path;
}