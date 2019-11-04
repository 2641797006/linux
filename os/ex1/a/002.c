#include <stdio.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/wait.h>

#define SEM_KEY	0x240001 // 信号量键值
#define NUM_PROCS	5

void child_do(int, const char*);
void update_file(int, const char*, int);

int main()
{
	int i, semid; // 信号量标识符
	pid_t child_pid;
	const char *file_name = "sem_aaa";

	semid = semget(SEM_KEY, 1, IPC_CREAT | 0600);
	// 创建一个信号量, 信号量访问权限0600;

	if (semid == -1) {
		perror("main semget");
		return -1;
	}

	// 把第一个信号量的数值设置为1
	if (semctl(semid, 0, SETVAL, 1) == -1) {
		perror("main semctl");
		return -1;
	}

	for (i=0; i<NUM_PROCS; ++i) {
		child_pid = fork();
		switch (child_pid) {
		case -1:
			perror("fork");
			return -1;
		case 0:
			child_do(semid, file_name);
			return 0;
		default:
			break;
		}
	}

	for (i=0; i<NUM_PROCS; ++i)
		wait(NULL);

	printf("main: All done\n");
}

void
update_file(int semid, const char *file_name, int n)
{
	FILE *fp;
	struct sembuf sops[1];

	sops[0].sem_num = 0;
	sops[0].sem_op = -1;
	sops[0].sem_flg = 0;

	if (semop(semid, sops, 1) == -1) {
		perror("semop");
		return;
	}

	fp = fopen(file_name, "w");
	if ( fp ) {
		fprintf(fp, "%d\n", n);
		printf("%d\n", n);
		fclose(fp);
	}

	sops[0].sem_num = 0;
	sops[0].sem_op = 1;
	sops[0].sem_flg = 0;

	if (semop(semid, sops, 1) == -1) {
		perror("semop");
		return;
	}
}

void
child_do(int semid, const char *file_name)
{
	int i;
	pid_t pid = getpid();

	for (i=0; i<3; ++i) {
		update_file(semid, file_name, pid);
		usleep(500000);
	}
}

