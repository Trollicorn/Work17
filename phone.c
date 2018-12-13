#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <fcntl.h>

#define KEY 2018

int main(int argc, char * argv[]){

	if (argc != 2){
		printf("the number you have dialed is not available\n"
			"please only add only one of the following arguments:\n"
			"'-c': make the thing\n"
			"'-r': remove the thing\n"
			"'-v': view the thing\n");
		return -1;
	}
	
	if (!strcmp(argv[0],"-c")){ //creation
		semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0666);
		shmget(KEY, 200, IPC_CREAT | IPC_EXCL | 0666);
		int fd = open("story.txt", O_CREAT | O_EXCL);
		close(fd);
	}
	if (!strcmp(argv[0],"-r")){ //destruction
		int semid = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0666); 
		semctl(semid, 0, IPC_RMID);
		int shmid = shmget(KEY, 200, IPC_CREAT | IPC_EXCL | 0666);
		shmctl(shmid, IPC_RMID, NULL);
		int fd = open("story.txt", O_RDONLY |  O_CREAT | O_EXCL);
		char s[4000];
		read(fd,s,sizeof(s));
		printf("%s",s);
		unlink("story.txt");		
	}
	if (!strcmp(argv[0], "-v")){
		int fd = open("story.txt", O_RDONLY |  O_CREAT | O_EXCL);
		char s[4000];
		read(fd,s,sizeof(s));
		printf("%s",s);
		close(fd);
	}
}
