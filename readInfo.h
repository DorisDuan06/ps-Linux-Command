#ifndef _READINFO_H_
#define _READINFO_H_

typedef struct {
    char state;
    int utime;
    int stime;
    int vmemory;
    int uid;
    int buffer;
    char buf, buffer0[];
} processInfo;

void readInfo(int pid);

#endif

