/*
// Main File:      537ps.c
// This File:      readInfo.c
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

//stores the process information, i.e., state, stime, utime, size...
processInfo pinfo;

//readInfo() reads the process's state, stime and utime information from the stat file, reads the process's size information from the statm file, and reads the process's user id information in the status file
void readInfo(int pid) {
    char statFileName[255], statmFileName[255], statusFileName[255], statStr[2048], statmStr[4096], statusStr[2048], *s;
    FILE *fp1, *fp2, *fp3;

    sprintf(statFileName, "/proc/%d/stat", pid);
    sprintf(statmFileName, "/proc/%d/statm", pid);
    sprintf(statusFileName, "/proc/%d/status", pid);
    
    if (access(statFileName, R_OK) == -1) {
        printf("Process %d doesn't exit!\n", pid);
        exit(1);
    }
    if (access(statmFileName, R_OK) == -1)
        exit(1);
    if (access(statusFileName, R_OK) == -1)
        exit(1);
  
    if ((fp1 = fopen(statFileName, "r")) == NULL)
        exit(1);
    if ((fp2 = fopen(statmFileName, "r")) == NULL)
        exit(1);
    if ((fp3 = fopen(statusFileName, "r")) == NULL)
        exit(1);
  
    if ((s = fgets(statStr, 2048, fp1)) == NULL) {
        fclose(fp1);
        exit(1);
    }
    if ((s = fgets(statmStr, 4096, fp2)) == NULL) {
        fclose(fp2);
        exit(1);
    }
    if ((s = fgets(statusStr, 2048, fp3)) == NULL) {
        fclose(fp3);
        exit(1);
    }

    s = strchr(statStr, ')'); //set the starting point in the file
    sscanf (s + 2, "%c %d %d %d %d %d %u %u %u %u %u %d %d",
                  /* 1  2  3  4  5  6  7  8  9 10 11 12 13 */
	  &(pinfo.state), &(pinfo.buffer), &(pinfo.buffer), &(pinfo.buffer), &(pinfo.buffer), &(pinfo.buffer), &(pinfo.buffer), &(pinfo.buffer), &(pinfo.buffer), &(pinfo.buffer), &(pinfo.buffer), &(pinfo.utime), &(pinfo.stime));    //use pinfo.buffer to store information we don't need
    fclose(fp1);
    
    sscanf(statmStr, "%d", &(pinfo.vmemory));
    fclose(fp2);

    //set the starting point in the status file    
    fpos_t pos;
    rewind(fp3);
    //the UID lies in the 9th line
    for (int i = 0; i < 8; i++)
        fgets(pinfo.buffer0, 1024, fp3);
    fgetpos(fp3, &pos);
    fgets(pinfo.buffer0, 1024, fp3);
    sscanf(pinfo.buffer0, "%c %c %c %c %d", &(pinfo.buf), &(pinfo.buf), &(pinfo.buf), &(pinfo.buf), &(pinfo.uid)); //skip first 4 char, which are "U", "i", "d", ":"
    fclose(fp3);
}