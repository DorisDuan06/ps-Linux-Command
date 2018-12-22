WARNING_FLAGS = -Wall -Wextra

537ps: readInfo.o printInfo.o 537ps.o
	gcc $(WARNING_FLAGS) readInfo.o printInfo.o 537ps.o -o 537ps
readInfo.o: readInfo.c
	gcc $(WARNING_FLAGS) -c readInfo.c
printInfo.o: printInfo.c
	gcc $(WARNING_FLAGS) -c printInfo.c
537ps.o: 537ps.c
	gcc $(WARNING_FLAGS) -c 537ps.c
clean:
	rm *.o