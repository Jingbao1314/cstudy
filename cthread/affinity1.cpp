//
// Created by jingbao on 18-12-22.
//
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

/*线程亲和性的设置和获取主要通过下面两个函数来实现：
int pthread_setaffinity_np(pthread_t thread, size_t cpusetsize，
const cpu_set_t *cpuset);
int pthread_getaffinity_np(pthread_t thread, size_t cpusetsize,
                           cpu_set_t *cpuset);
//初始化，设为空
void CPU_ZERO (cpu_set_t *set);
//将某个cpu加入cpu集中
void CPU_SET (int cpu, cpu_set_t *set);
//将某个cpu从cpu集中移出
void CPU_CLR (int cpu, cpu_set_t *set);
//判断某个cpu是否已在cpu集中设置了
int CPU_ISSET (int cpu, const cpu_set_t *set);
*/
void *myfun(void *arg)
{
    cpu_set_t mask;
    cpu_set_t get;
    char buf[256];
    int i;
    int j;
    int num = sysconf(_SC_NPROCESSORS_CONF);//返回系统可以使用的核数
    printf("system has %d processor(s)\n", num);

    for (i = 0; i < num; i++) {
        CPU_ZERO(&mask);
        CPU_SET(i, &mask);
        if (pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask) < 0) {
            fprintf(stderr, "set thread affinity failed\n");
        }
        CPU_ZERO(&get);
        if (pthread_getaffinity_np(pthread_self(), sizeof(get), &get) < 0) {
            fprintf(stderr, "get thread affinity failed\n");
        }
        for (j = 0; j < num; j++) {
            if (CPU_ISSET(j, &get)) {
                printf("thread %d is running in processor %d\n", (int)pthread_self(), j);
            }
        }
        j = 0;
        while (j++ < 900000000) {
            memset(buf, 0, sizeof(buf));
        }
    }
    pthread_exit(NULL);
}

int affinity1()
{
    pthread_t tid;
    if (pthread_create(&tid, NULL, myfun, NULL) != 0) {
        fprintf(stderr, "thread create failed\n");
        return -1;
    }
    pthread_join(tid, NULL);
    return 0;
}


