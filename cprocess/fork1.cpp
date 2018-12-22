//
// Created by jingbao on 18-12-22.
//


#include <zconf.h>
#include <cstdlib>
#include <cstdio>

int fork1(){
    pid_t  pid;
    pid=fork();
    if (pid<0){
        perror("fail to fork");
        exit(-1);
    } else if (pid>0){
        printf("this is father\n");
        sleep(5);
    } else{
        printf("this is son\n");
        sleep(5);
    }
}

