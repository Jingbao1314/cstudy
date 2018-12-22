//
// Created by jingbao on 18-12-22.
//

#include <termio.h>
#include <zconf.h>
#include <cstdio>
#include <cstdlib>

int zombie(){
    pid_t  pid=fork();
    if (pid>0){
        sleep(10);
        printf("father sleep end\n");
    } else{
        sleep(5);
        printf("son exit\n");
        exit(0);
    }
    return 0;
}