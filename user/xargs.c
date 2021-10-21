//
// Created by Eric Zhao on 21/10/2021.
//


#include "../kernel/types.h"
#include "../user/user.h"
#include "../kernel/param.h"

void xargs(int argcToCall,const char*argvToCall[]){
    char argToPass[MAXARG][64];
    char buf;
    short indexArg = argcToCall;
    for(int p=0;p<argcToCall;p++){
        memcpy(argToPass[p],argvToCall[p], strlen(argvToCall[p]));
    }
    char *p = argToPass[indexArg];
    while (read(0, &buf, 1)) {
        switch (buf) {
            case ' ':
                *p='\0';
                p = argToPass[indexArg++];
                break;
            default:
                *(p++)=buf;
        }
    }
    exec((void *)argvToCall[0],(void *)argToPass);
}
int main(int argc, const char *argv[]) {
    xargs(argc-1,(void *)argv[1]);
    exit(0);
}