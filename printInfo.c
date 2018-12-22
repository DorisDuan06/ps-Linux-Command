/*
// Main File:      537ps.c
// This File:      printInfo.c
//
// Author:         Yanjia Duan
// Email:          duan35@wisc.edu
// CS Login:       yanjia
//
// Author:         Karina Nihalani
// Email:          nihalani@wisc.edu
// CS Login:       karina
//
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "readInfo.h"
#include "printInfo.h"

//stores the process information, i.e., state, stime, utime, size...
processInfo pinfo;

//printInfo() reads and prints the process's command line information, and prints out the process's state, utime, stime, size information that are stored in pinfo
void printInfo(int pid, int flag[]) {
    char cmlFileName[255], ch;
    FILE *fp3;
    
    sprintf(cmlFileName, "/proc/%d/cmdline", pid); //get the cmdline file's directory name
    if (access(cmlFileName, R_OK) == -1)
        exit(1);
    if ((fp3 = fopen(cmlFileName, "r")) == NULL)
        exit(1);
    
    printf("%d: ", pid);
    if (flag[1] == 1)
        printf("%c ", pinfo.state);
    if (flag[2] == 1)
        printf("utime=%d ", pinfo.utime);
    if (flag[3] == 1)
        printf("stime=%d ", pinfo.stime);
    if (flag[4] == 1)
        printf("vmemory=%d ", pinfo.vmemory);
    if (flag[5] == 1) {
        printf("[");
        //read the cmdline file character by character
        while((ch = fgetc(fp3)) != EOF) {
            printf("%c", ch);
        }
        fclose(fp3);
        printf("]");
    }
    printf("\n");
}