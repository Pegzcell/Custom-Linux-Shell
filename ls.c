#include "headers.h"

char months[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

int f_0(char *y) {
    DIR *dirp = opendir(y);
    if (dirp) {
        struct dirent *ent;
        while ((ent = readdir(dirp)) != NULL) {
            if ((ent->d_name)[0] != '.')
                printf("%s ", ent->d_name);
        }
        closedir(dirp);
        br;
    } else {
        /* could not open directory */
        perror(y);
        return EXIT_FAILURE;
    }
}

int f_a(char *y) {
    DIR *dirp = opendir(y);
    if (dirp) {
        struct dirent *ent;
        while ((ent = readdir(dirp)) != NULL) {
            printf("%s ", ent->d_name);
        }
        closedir(dirp);
        br;
    } else {
        /* could not open directory */
        perror(y);
        return EXIT_FAILURE;
    }
}

int f_l(char *y) {
    DIR *dirp = opendir(y);
    struct dirent *ent;
    char name_ent[300] = "";
    struct stat sb_ent;
    struct passwd result_usr;
    struct group result_grp;
    struct tm tm_ent;

    int c = 0, mask = 400;
    char t, perm[3] = "rwx";
    if (dirp) {
        while ((ent = readdir(dirp)) != NULL) {
            if ((ent->d_name)[0] != '.') {
                strcpy(name_ent, y);
                strcat(name_ent, "/");
                strcat(name_ent, ent->d_name);
                if (!stat(name_ent, &sb_ent)) {
                    // ********************************************* ls -l
                    c += sb_ent.st_blocks;
                    // ftype
                    switch (ent->d_type) {
                        case DT_REG:
                            t = '-';
                            break;
                        case DT_DIR:
                            t = 'd';
                            break;
                        case DT_CHR:
                            t = 'c';
                            break;
                        case DT_BLK:
                            t = 'b';
                            break;
                        case DT_SOCK:
                            t = 's';
                            break;
                        case DT_FIFO:
                            t = 'p';
                            break;
                        case DT_LNK:
                            t = 'l';
                            break;
                        case DT_UNKNOWN:
                            t = '?';
                            break;
                    }
                    printf("%c", t);

                    // permissions
                    mask = 0400;
                    fo(i, 3) {
                        fo(j, 3) {
                            printf("%c", (sb_ent.st_mode & mask) ? perm[j] : '-');
                            mask /= 2;
                        }
                    }
                    // rest
                    result_usr = *(getpwuid(sb_ent.st_uid));
                    result_grp = *(getgrgid(sb_ent.st_gid));
                    tm_ent = *(localtime(&(sb_ent.st_mtim.tv_sec)));
                    printf("%2ld %s %s %9ld %s %2d ", sb_ent.st_nlink, result_usr.pw_name, result_grp.gr_name,
                           sb_ent.st_size, months[tm_ent.tm_mon], tm_ent.tm_mday);
                    if (difftime(time(NULL), sb_ent.st_mtim.tv_sec) > 182 * 24 * 3600)
                        printf("%5d ", 1900 + tm_ent.tm_year);
                    else
                        printf("%02d:%02d ", tm_ent.tm_min, tm_ent.tm_hour);
                    printf("%s\n", ent->d_name);
                    // ********************************************* ls -l
                } else {
                    perror(name_ent);
                    return EXIT_FAILURE;
                }
            }
        }
        printf("total %d\n", c / 2);
        closedir(dirp);

    } else {
        /* could not open directory */
        perror(y);
        return EXIT_FAILURE;
    }
}

int f_al(char *y) {
    DIR *dirp = opendir(y);
    struct dirent *ent;
    char name_ent[300] = "";
    struct stat sb_ent;
    struct passwd result_usr;
    struct group result_grp;
    struct tm tm_ent;

    int c = 0, mask = 400;
    char t, perm[3] = "rwx";
    if (dirp) {
        while ((ent = readdir(dirp)) != NULL) {
            strcpy(name_ent, y);
            strcat(name_ent, "/");
            strcat(name_ent, ent->d_name);
            if (!stat(name_ent, &sb_ent)) {
                // ********************************************* ls -l
                c += sb_ent.st_blocks;
                // ftype
                switch (ent->d_type) {
                    case DT_REG:
                        t = '-';
                        break;
                    case DT_DIR:
                        t = 'd';
                        break;
                    case DT_CHR:
                        t = 'c';
                        break;
                    case DT_BLK:
                        t = 'b';
                        break;
                    case DT_SOCK:
                        t = 's';
                        break;
                    case DT_FIFO:
                        t = 'p';
                        break;
                    case DT_LNK:
                        t = 'l';
                        break;
                    case DT_UNKNOWN:
                        t = '?';
                        break;
                }
                printf("%c", t);

                // permissions
                mask = 0400;
                fo(i, 3) {
                    fo(j, 3) {
                        printf("%c", (sb_ent.st_mode & mask) ? perm[j] : '-');
                        mask /= 2;
                    }
                }
                // rest
                result_usr = *(getpwuid(sb_ent.st_uid));
                result_grp = *(getgrgid(sb_ent.st_gid));
                tm_ent = *(localtime(&(sb_ent.st_mtim.tv_sec)));
                printf("%2ld %s %s %9ld %s %2d ", sb_ent.st_nlink, result_usr.pw_name, result_grp.gr_name,
                       sb_ent.st_size, months[tm_ent.tm_mon], tm_ent.tm_mday);
                if (difftime(time(NULL), sb_ent.st_mtim.tv_sec) > 182 * 24 * 3600)
                    printf("%5d ", 1900 + tm_ent.tm_year);
                else
                    printf("%02d:%02d ", tm_ent.tm_min, tm_ent.tm_hour);
                printf("%s\n", ent->d_name);
                // ********************************************* ls -l
            } else {
                perror(name_ent);
                return EXIT_FAILURE;
            }
        }
        printf("total %d\n", c / 2);
        closedir(dirp);
    } else {
        /* could not open directory */
        perror(y);
        return EXIT_FAILURE;
    }
}

int (*func_ls[])(char *) = {f_0, f_a, f_l, f_al};

int ls3(int x, char **y) {
    int k = 0, a = 0, l = 0, number_of_dir = 0;
    char **target_dir = (char **) calloc(100, sizeof(char *));
    for (int i = 1; i < x; i++) {
        if (y[i][0] == '-') {
            for (int j = 1; j < strlen(y[i]); j++) {
                if (y[i][j] == 'a' && !a) {
                    a = 1;
                    k += a;
                } else if (y[i][j] == 'l' && !l) {
                    l = 2;
                    k += l;
                } else {
                    printf("ls: Unrecognized flag");
                    return EXIT_FAILURE;
                }
            }
        } else {
            target_dir[number_of_dir++] = y[i];
        }
    }
    if (number_of_dir == 0) {
        target_dir[number_of_dir++] = ".";
    }
    DIR *dirp;
    struct stat sb;
    fo(i, number_of_dir) {
        if (!stat(target_dir[i], &sb)) {
            if (number_of_dir > 1)
                printf("\n%s:\n", target_dir[i]);
            if (S_ISDIR(sb.st_mode)) {
                (func_ls[k])(target_dir[i]);
            } else {
                printf("%s\n", target_dir[i]);
            }
        } else {
            perror(target_dir[i]);
            return EXIT_FAILURE;
        }
    }
}
