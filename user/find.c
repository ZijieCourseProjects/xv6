//
// Created by Eric Zhao on 20/10/2021.
//

#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "../user/user.h"
#include "../kernel/fs.h"

void find(const char *loc, const char *name) {
    printf("Now at :%s\n", loc);
    char buf[500], *p;
    int fd;
    struct dirent dr;
    struct stat st;

    if ((fd = open(loc, 0)) < 0) {
        printf("Cant open path: %s\n", loc);
        return;
    }

    if (fstat(fd, &st) < 0) {
        printf("Cant stat path: %s", loc);
        return;
    }

    if (strlen(loc) + 1 + DIRSIZ + 1 > sizeof buf) {
        printf("find: path too long\n");
        return;
    }

    strcpy(buf, loc);
    p = buf + strlen(buf);
    *p++ = '/';
    while (read(fd, &dr, sizeof(dr)) == sizeof(dr)) {
        if (!strcmp(dr.name, ".") || !strcmp(dr.name, "..") || dr.inum == 0) {
            continue;
        }

        memmove(p, dr.name, DIRSIZ);
        p[DIRSIZ] = 0;

        if (stat(buf, &st) < 0) {
            printf("ls: cannot stat %s\n", buf);
            continue;
        }

        switch (st.type) {
            case T_FILE:
                if (strcmp(dr.name, name) == 0) {
                    printf("%s\n", buf);
                }
                break;
            case T_DIR:
                printf("rec start at %s\n", buf);
                find(buf, name);
        }
    }
    close(fd);
}

int main(int argc, const char *argv[]) {
    if (argc != 3) {
        printf("find [location] [name]\n");
        exit(0);
    }
    find(argv[1], argv[2]);
    exit(0);
}


