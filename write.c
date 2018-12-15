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
	semd = semget(KEY, 1, 0);

	struct sembuf change;
	change.sem_num = 0;
	change.sem_op = -1;
	change.sem_flg = SEM_UNDO;

	while(semctl(semd, 0, GETVAL) == 0);

	semop(semd, &change, 1);

	int shmid = shmget(KEY, 200, 0);
	int shmem = shmat(shmid, 0, 0);

	int fd = open("story.txt", O_WRONLY | O_APPEND); 
	lseek(fd, -1 * shmem, SEEK_END);
	
	char last[200];
	read(fd, last, 200);
	printf("last line: %s\n",last);
	
	char input[200];
	printf("your addition: ");
	fgets(input, 200, stdin);
	
	int bytes = strlen(input);
	
	write(fd, input, 200);
	
	close(fd);
	
	semop(semd, &change, 1);

	shmem = bytes;
	shmdt(shmem);
	
	return 0;	
}
