//
// Created by Eric Zhao on 21/10/2021.
//


#include "../kernel/types.h"
#include "../user/user.h"
#include "../kernel/param.h"
#include "../kernel/fcntl.h"

void run(char *env[]) {
    if (fork() == 0) {
        exec(env[0], env);
        fprintf(2, "exec failed\n");
        exit(0);
    }
    wait(0);
}

void xargs(int argcToCall, const char *argvToCall[]) {
    char argToPass[MAXARG][64];
    char *ptrArg[MAXARG];
    char buf;
    int indexArg = argcToCall;

    for (int p = 0; p < argcToCall; p++) {
        strcpy(argToPass[p], argvToCall[p + 1]);
    }

    for (int i = 0; i < MAXARG; i++) {
        ptrArg[i] = argToPass[i];
    }

    char *p = argToPass[indexArg];
    while (read(0, &buf, 1)) {
        switch (buf) {
            case '\n':
                *p = '\0';
                ptrArg[indexArg + 1] = 0;

                run(ptrArg);

                ptrArg[indexArg + 1] = argToPass[indexArg + 1];
                p = argToPass[argcToCall];
                break;

            case ' ':
                *p = '\0';
                p = argToPass[++indexArg];
                break;

            default:
                *(p++) = buf;
        }
    }
}

int main(int argc, const char *argv[]) {
    xargs(argc - 1, argv);
    exit(0);
}