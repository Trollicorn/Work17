#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>

#define KEY 2018

int main() {

	int semd;
	printf("wow");
	semd = semget(KEY, 1, 0);
	printf("hello");

	struct sembuf change;
	change.sem_num = 0;
	change.sem_op = -1;
	change.sem_flg = SEM_UNDO;

	printf("here");

	while(semctl(semd, 0, GETVAL) == 0);

	printf("1");

	semop(semd, &change, 1);

	int shmid = shmget(KEY, 200, 0);
	int shmem;
//	char * data;
	shmat(shmid, &shmem, 0);
//	data = shmat(shmid, (void *) 0, 0);

	printf("2");

//	int fd = open("story.txt", O_APPEND);
	int fd = open("story.txt", O_RDWR | O_APPEND); 
	lseek(fd, -1 * shmem,SEEK_END);
	char last[200];

	read(fd, last, 200);
/*	if (!strlen(data)){
		printf("nothing here, you get to start the story!\n");
	}
	else{
		printf("last line: %s\n", data);
	}*/
	printf("last line: %s\n",last);
	char input[200];
	printf("your addition: ");
	fgets(input, 200, stdin);
	
	input[strlen(input)-1] = '\0';
	
//	strcpy(data,input);
	
	int bytes = strlen(input);
	
	write(fd, input, 200);
	
	close(fd);
	
//	shmdt(data);
//	change.sem_op = 1;
//	semop(semd, &change, 1);

	shmem = bytes;
	shmdt(&shmem);
	return 0;	
}
