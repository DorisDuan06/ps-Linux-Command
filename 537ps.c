/*
// Main File:      537ps.c
// This File:      537ps.c
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
extern processInfo pinfo;

int main(int argc, char *argv[]){
    //flag[] marks whether to print out corresponding information (in order: -p -s -U -S -v -c), 0: don't print, 1: print
    int flag[6] = {0, 0, 1, 0, 0, 1}, opt, pid = 0;
    
    while ((opt = getopt(argc, argv, ":p:s::U::S::v::c::")) != -1) {
        switch (opt) {
                
            //if "-p" is present, catch the <pid> following it
            case 'p':
                flag[0] = 1;
                pid = atoi(optarg);
                //if the user doesn't type <pid>, syntax error
                if (pid == 0) {
                    printf("Usage: 537ps [-p <pid>] [-s[-]] [-U[-]] [-S[-]] [-v[-]] [-c[-]]\n");
                    exit(EXIT_FAILURE);
                }
                break;
                            
            case 's':
                //if not "-s-", print out state
                if (optarg == NULL) {
                    flag[1] = 1;
                }
                //if other characters go after "-s", syntax error
                else if (*optarg != '-') {
                    printf("Usage: 537ps [-p <pid>] [-s[-]] [-U[-]] [-S[-]] [-v[-]] [-c[-]]\n");
                    exit(EXIT_FAILURE);
                }
                break;
            
            case 'U':
                if (optarg != NULL) {
                    //if "-U-", don't print out utime
                    if (*optarg == '-')
                        flag[2] = 0;
                    //if characters other than "-" go after "-U", syntax error
                    else {
                        printf("Usage: 537ps [-p <pid>] [-s[-]] [-U[-]] [-S[-]] [-v[-]] [-c[-]]\n");
                        exit(EXIT_FAILURE);
                    }
                }
                break;
            
            case 'S':
                //if not "-S-", print out stime
                if (optarg == NULL) {
                    flag[3] = 1;
                }
                //if characters other than "-" go after "-S", syntax error
                else if (*optarg != '-') {
                    printf("Usage: 537ps [-p <pid>] [-s[-]] [-U[-]] [-S[-]] [-v[-]] [-c[-]]\n");
                    exit(EXIT_FAILURE);
                }
                break;
            
            case 'v':
                //if not "-v-", print out size
                if (optarg == NULL) {
                    flag[4] = 1;
                }
                //if characters other than "-" go after "-v", syntax error
                else if (*optarg != '-') {
                    printf("Usage: 537ps [-p <pid>] [-s[-]] [-U[-]] [-S[-]] [-v[-]] [-c[-]]\n");
                    exit(EXIT_FAILURE);
                }
                break;
            
            case 'c':
                if (optarg != NULL) {
                    //if "-c-", don't print out cmdline
                    if (*optarg == '-')
                        flag[5] = 0;
                    //if characters other than "-" go after "-c", syntax error
                    else {
                        printf("Usage: 537ps [-p <pid>] [-s[-]] [-U[-]] [-S[-]] [-v[-]] [-c[-]]\n");
                        exit(EXIT_FAILURE);
                    }
                }
                break;
            
            default:
                printf("Usage: 537ps [-p <pid>] [-s[-]] [-U[-]] [-S[-]] [-v[-]] [-c[-]]\n");
                exit(EXIT_FAILURE);
        }
    }
    
    //if "-p <pid>" is present, print the information of this process
    if (flag[0] == 1) { 
        readInfo(pid);
        printInfo(pid, flag);
    }
    //if "-p <pid>" isn't present, find all current user's processes
    else if (flag[0] == 0) {
        DIR *dp;
        struct dirent *ep;
        dp = opendir("/proc");
        int uid = (int)getuid(); //get the current user's uid
        if (dp != NULL) {
            //read all the pids
            while ((ep = readdir(dp)) != NULL) {
              pid = atoi(ep->d_name); //convert the string type to integer
              //pid = 0 means the folder name is not a number, which is not a pid
              if (pid != 0) {
                  readInfo(pid);
                  //see if this process's user is the current user
                  if (uid == pinfo.uid)
                      printInfo(pid, flag);
              }
            }
            (void)closedir(dp);
        }
        else
            perror ("Couldn't open the directory\n");
    }
    
    exit(EXIT_SUCCESS);
}