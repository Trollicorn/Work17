#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <ipc.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>

#define KEY 2018

int write() {

	int semd;
	semd = semget(KEY, 0, 0);

	struct sembuf change;
	change.sem_num = 0;
	change.sem_op = -1;
	change.sem_flg = SEM_UNDO;

	while(semctl(semd, 0, GETVAL) == 0);

	semop(semd, sembuf, 1);

	int fd = open("story.txt", O_APPEND);
	//read last line

	char input[500];
	printf("Enter new story line: ");
	fgets(input, 500, stdin);
	int bytes = strlen(input);

	write(fd, input, 500);

	close(fd);

	int shmid = shmget(KEY, 0, 0);
	int shmem = shmat(shmid, 0, 0);
	shmem = bytes;
	shmdt(
	

}
