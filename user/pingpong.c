//
// Created by Eric Zhao on 18/10/2021.
//

#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "../user/user.h"

enum {
    READ=0,WRITE
};

int main(int argc, const char *argv[]) {
    int p[2];
    int reverse[2];
    int pid;
    pipe(p);
    pipe(reverse);
    char buf;

    if((pid = fork())){
        close(p[READ]);
        write(p[WRITE],&pid,sizeof(int));
        wait(0);
        read(reverse[READ],&buf,1);
        printf("%d: received pong\n",getpid());
        exit(0);
    }else{
        close(p[READ]);
        read(p[READ],&buf,sizeof(int));
        printf("%d: received ping\n",buf);
        write(reverse[WRITE],&buf,sizeof(int));
        exit(0);
    }
}