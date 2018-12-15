#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <errno.h>

#define KEY 2018


union semun{
	int val;
	struct semid_ds *buf;     //Used for SETVAL
	unsigned short *array;   //Used for IPC_STAT and IPC_SET
	struct seminfo *__buf;   //Used for SETALL
};

int main(int argc, char * argv[]){

	if (argc != 2){
		printf("the number you have dialed is not available\n"
			"please only add only one of the following arguments:\n"
			"'-c': make the thing\n"
			"'-r': remove the thing\n"
			"'-v': view the thing\n");
		return -1;
	}

	int semid;
	int shmid;
	int fd;
	union semun change;
	struct sembuf arrow;
	arrow.sem_num = 0;
	arrow.sem_flg = SEM_UNDO;

	if (!strcmp(argv[1],"-c")){ //creation
		semid = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0666);
//		if (semid == -1){printf("semerror: %s\n",strerror(errno));return -1;}
		printf("semid: %d\n",semid);
		shmid = shmget(KEY, 200, IPC_CREAT | IPC_EXCL | 0666);
//		if (shmid == -1){printf("shmerror: %s\n",strerror(errno));return -1;}
		printf("semid: %d\n",semid);
		fd = open("story.txt", O_CREAT | O_TRUNC, 0666);
//		if (fd == -1){printf("fderror: %s\n",strerror(errno));return -1;}
		printf("fd: %d\n",fd);
		change.val = 1;
		semctl(semid, 0, SETVAL, change); 
		close(fd);
	}
	else if (!strcmp(argv[1],"-r")){ //destruction
		semid = semget(KEY, 1, 0); 
		semctl(semid, 0, IPC_RMID);
		shmid = shmget(KEY, 200, 0);
		shmctl(shmid, IPC_RMID, NULL);
		fd = open("story.txt", O_RDONLY);
		char s[4000];
		read(fd,s,sizeof(s));
		printf("%s",s);
		unlink("story.txt");		
	}
	else if (!strcmp(argv[1], "-v")){
		fd = open("story.txt", O_RDONLY);
		char s[4000];
		read(fd,s,sizeof(s));
		printf("%s",s);
		close(fd);
	}
}
