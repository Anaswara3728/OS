#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>

struct student{
int rollno,rank;
char name[100];
};

int main(){
int n;
int shmid=shmget((key_t)2345,1024,0666 |IPC_CREAT);
struct student *shm_memory=(struct student *) shmat(shmid,NULL,0);
  
printf("Enter number of students:");
scanf("%d",&n);
printf("Enter student details:\n");
  
for(int i=0;i<n;i++){
      printf("Enter roll no of student %d:",i+1);
      scanf("%d",&shm_memory[i].rollno);
      printf("Enter name of student %d:",i+1);
      scanf("%s",shm_memory[i].name);
printf("Enter rank of student %d:",i+1);
scanf("%d",&shm_memory[i].rank);
          }
shm_memory[n].rank=-1;
shmdt(shm_memory);
printf("Details passed to the receiver.\n");
return 0;
}
