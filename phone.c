#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define KEY 2018

int main(int argc, char * argv[]){

	if (argc != 2){
		printf("the number you have dialed is not available\n
			please only add only one of the following arguments:\n
			'-c': make the thing\n
			'-r': remove the thing\n
			'-v': view the thing\n")
		return -1;
	}
	
	if (!strcmp(argv[0],"-c")){
		semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0666);
		
	}


}
