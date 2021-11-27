#include "headers.h"

int cd0(int x, char **y)
{
    char cwd[300];
    getcwd(cwd, 300);
    if (x == 1){
        chdir(tilde);
        strcpy(oldpwd,cwd);
    }
    else if (x == 2)
    {
        if (!strcmp(y[1], "~"))
        {
            chdir(tilde);
            strcpy(oldpwd,cwd);
        }
        else if (!strcmp(y[1], "-"))
        {
            if (oldpwd[0]!='\0')
            {
                chdir(oldpwd);
                strcpy(oldpwd,cwd);
            }
            else
            {
                printf("cd: OLDPWD not set\n");
            }
        }
        else
            if(!chdir(y[1])){
                strcpy(oldpwd,cwd);
            }
            else{
            printf("cd: %s: No such file or directory\n", y[1]);
        }
    }
    else
    {
        printf("cd: too many arguments\n");
    }
}