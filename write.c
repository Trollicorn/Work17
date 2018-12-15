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

	int semid;
	semid = semget(KEY, 1, 0);

	struct sembuf change;
	change.sem_num = 0;
	change.sem_op = -1;
	change.sem_flg = SEM_UNDO;

//	while(semctl(semd, 0, GETVAL) == 0);

	semop(semid, &change, 1);

	int shmid = shmget(KEY, 200, 0);
	int shmem = shmat(shmid, (void *) 0, 0);

	int fd = open("story.txt", O_WRONLY | O_APPEND); 
	lseek(fd, -1 * shmem, SEEK_END);
	
	char last[200];
	read(fd, last, strlen(last));
	
	printf("last line: %s\n",last);
	char input[200];
	printf("your addition: ");
	fgets(input, strlen(input), stdin);
	
	int bytes = strlen(input);
	
	write(fd, input, strlen(input));
	
	
	close(fd);
	
	shmem = bytes;
	shmdt(&shmem);
	change.sem_op = 1;
	semop(semid,&change,1);
	
	return 0;	
}
