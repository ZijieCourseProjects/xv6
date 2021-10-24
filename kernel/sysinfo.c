//
// Created by Eric Zhao on 24/10/2021.
//

#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "stat.h"
#include "spinlock.h"
#include "proc.h"
#include "fs.h"
#include "sleeplock.h"
#include "file.h"
#include "fcntl.h"
#include "sysinfo.h"

int sys_sysinfo(void){
    uint64 to;
    struct proc *p=myproc();
    struct sysinfo info;

    info.nproc=countProc();
    info.freemem=countFree();

    argaddr(0,&to);

    if (copyout(p->pagetable,to,(char *) &info,sizeof(info)) < 0){
        return -1;
    }

    return 0;
}
