//
// Created by Eric Zhao on 18/10/2021.
//

#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "../user/user.h"

int main(int argc, const char *argv[]) {
    const char* err="An integer argument as time to sleep is required.\n";
    if(argc==1)
        write(1,err,strlen(err));
    sleep(atoi(argv[1]));
    exit(0);
}
