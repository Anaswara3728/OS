#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>

struct message {
int priority;
char mssg[100];
};

int main() {
int shmid = shmget((key_t)2345, 1024, 0666 | IPC_CREAT);
struct message *shm_memory = (struct message *)shmat(shmid, NULL, 0);
printf("Enter 3 messages with priority\n");
for (int i = 0; i < 3; i++) {
         printf("Enter priority and message[priority,message]:\n");
         scanf("%d %[^\n]", &shm_memory[i].priority, shm_memory[i].mssg);
}
shmdt(shm_memory);
printf("Messages written to shared memory.\n");
return 0;
}
