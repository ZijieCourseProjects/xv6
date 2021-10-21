//
// Created by Eric Zhao on 18/10/2021.
//


#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "../user/user.h"

int main(int argc, const char *argv[]) {
    int numGot, prime = 3;
    int pip[2];
    int _exit[2];
    pipe(pip);
    pipe(_exit);
    int pipOut = pip[0], pipIn = pip[1];
    if ((fork())) {
        close(pipOut);
        close(_exit[1]);
        for (int i = 2; i <= 35; i++) {
            write(pipIn, &i, sizeof(int));
        }
        int i=-1;
        write(pipIn,&i,sizeof(int));
        read(_exit[0],&i,sizeof(int));
        close(pipIn);
        exit(0);
    }
    close(_exit[0]);
    char hasPrime=0;
    close(pipIn);
    char haveNext=0;

    while (read(pipOut, &numGot, sizeof(int))) {
        if (hasPrime && numGot % prime == 0) {
            continue;
        }else {
            if(haveNext){
                write(pipIn, &numGot, sizeof(int));
            }else{
                if(numGot==-1){
                    write(_exit[1],&numGot,sizeof(int));
                    exit(0);
                }
                int secPip[2];
                pipe(secPip);
                pipIn = secPip[1];
                if (!fork()) {
                    close(pipIn);
                    printf("prime %d\n",numGot);
                    prime = numGot;
                    pipOut = secPip[0];
                    hasPrime=1;
                }else{
                    haveNext=1;
                    close(secPip[0]);
                }
            }
        }
    }
    exit(0);
}
