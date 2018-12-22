//
// Created by jingbao on 18-12-22.
//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#define MAXFILE 65535
volatile sig_atomic_t _running = 1;
void sigterm_handler(int arg)
{
    _running = 0;
}
int daemon1(){
    pid_t pc;
    int i,fd,len;
    char *buf="this is a Dameon\n";
    len = strlen(buf);

    /* 屏蔽一些有关控制终端操作的信号
     * 防止在守护进程没有正常运转起来时，因控制终端受到干扰退出或挂起
     * */
    signal(SIGINT,  SIG_IGN);// 终端中断
    signal(SIGHUP,  SIG_IGN);// 连接挂断
    signal(SIGQUIT, SIG_IGN);// 终端退出
    signal(SIGPIPE, SIG_IGN);// 向无读进程的管道写数据
    signal(SIGTTOU, SIG_IGN);// 后台程序尝试写操作
    signal(SIGTTIN, SIG_IGN);// 后台程序尝试读操作
    signal(SIGTERM, SIG_IGN);// 终止


    pc = fork(); /*第一步 分离子进程，干掉父进程*/
    if(pc<0){
        printf("error fork\n");
        exit(1);
    }else if(pc>0){
        exit(0);
    }

    setsid(); /*第二步 创建一个新的会话，并担任该会话组的组长*/
    /**
     *    (a) 让进程摆脱原会话的控制；
          (b) 让进程摆脱原进程组的控制；
          (c) 让进程摆脱原控制终端的控制；
     */
    chdir("/"); /*第三步 设置目录为根目录*/
    umask(0); /*第四步 讲权限掩码设置为不屏蔽任何权限*/
    for(i=0;i<MAXFILE;i++) /*第五步 关掉所有的设备*/
        close(i);

    /*第六步 设置关闭信号*/
//    signal(SIGTERM, sigterm_handler);//kill -15 pid
    signal(31, sigterm_handler);//kill -31 pid
    while(_running){
        if((fd=open("/tmp/dameon.log",O_CREAT|O_WRONLY|O_APPEND,0600))<0){
            perror("open");
            exit(1);
        }
        write(fd,buf,len+1);
        close(fd);
        sleep(10);
    }
    return 0;
}
