#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>

struct message {
int priority;
char mssg[100];
};

void sort_msg(struct message *msgs) {
for (int i = 0; i < 2; i++) {
   for (int j = i + 1; j < 3; j++) {
      if (msgs[i].priority > msgs[j].priority) {
         struct message temp = msgs[i];
         msgs[i] = msgs[j];
         msgs[j] = temp;
                 }
         }
   }
}

int main() {
int shmid = shmget((key_t)2345, 1024, 0666);
  
struct message *shm_memory = (struct message *)shmat(shmid, NULL, 0);
sort_msg(shm_memory);
printf("Messages sorted by priority:\n");
  
for (int i = 0; i < 3; i++) {
       printf("%s\n",shm_memory[i].mssg);
          }
shmdt(shm_memory);
shmctl(shmid, IPC_RMID, NULL);
return 0;
  }
