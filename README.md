# ps-Linux-Command
`537ps` implemented partial functions of Linux ps command. It can display a process's `state (s)`, `user time (U)`, `system time (S)`, `virtual memory size (v)` and `command line (c)` information. Users will type `537ps [-p <pid>] [-s[-]] [-U[-]] [-S[-]] [-v[-]] [-c[-]]` on the Linux command line.

`-p <pid>`: Display process information only for the process whose number is pid. It does not matter if the specified process is owned by the current user. If this option is not present then display information for all processes of the current user (and only of the current user).

`-s`: Display the single-character state information about the process. This information is in the stat file in process's directory, the third ("state") field. This option defaults to be false, so if it is not present, do not display this information. -s- is valid but has no effect.

`-U`: Display the amount of user time consumed by this process. This information is in the stat file in process's directory, the "utime" field. This option defaults to be true, so if it is not present, then this information is displayed. -U- turns this option off.

`-S`: Display the amount of system time consumed so far by this process. This information is in the stat file in process's directory, the "stime" field. This option defaults to be false, so if it is not present, then this information is not displayed. -S- is valid but has no effect.

`-v`: Display the amount of virtual memory currently being used (in pages) by this program. This information is in the statm file in process's directory, the first ("size") field. This option defaults to be false, so if it is not present, then this information is not displayed. -v- is valid but has no effect.

`-c`: Display the command-line that started this program. This information is in the cmdline file in process's directory. This option defaults to be true, so if it is not present, then this information is displayed. -c- turns this option off.

__537ps.c__ reads the command line, rules out illegal combinations of arguments that the user types, marks the presence of each argument, and calls readInfo() in readInfo.c to grab the information the user needs. If "-p <pid>" doesn't exist, it iterates through the process directory /proc, finds all pids and calls readInfo(). 

__readInfo.c__ reads the process's state, user time and system time information from the /proc/<pid>/stat, the process's size information from the /proc/<pid>/statm, User ID for that process in the /proc/<pid>/status to a process structure.

__printInfo.c__ reads and prints the command line information from /proc/<pid>/cmdline and prints out the process's state, utime, stime, size information stored in the process structure.
