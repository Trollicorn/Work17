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
	semd = semget(KEY, 0, 0);

	struct sembuf change;
	change.sem_num = 0;
	change.sem_op = -1;
	change.sem_flg = SEM_UNDO;

	while(semctl(semd, 0, GETVAL) == 0);

	semop(semd, sembuf, 1);

	int shmid = shmget(KEY, 0, 0);
	int shmem = shmat(shmid, 0, 0);

	int fd = open("story.txt", O_APPEND);
	lseek(fd, -1 * shmem,SEEK_END);
	char last[500];
	read(fd, last, 500);
	
	printf("Current last line: %s", last);

	char input[500];
	printf("Enter new story line: ");
	fgets(input, 500, stdin);
	int bytes = strlen(input);

	write(fd, input, 500);

	close(fd);

	shmem = bytes;
	shmdt(&shmem);
	
}
