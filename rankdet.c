#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>

struct student{
int rollno,rank;
char name[100];
};

void sort_ranks(struct student *stud,int n){
for(int i=0;i<n-1;i++){
      for(int j=i+1;j<n;j++){
           if(stud[i].rank > stud[j].rank){
                  struct student temp=stud[i];
                  stud[i]=stud[j];
                  stud[j]=temp;
                       }
                     }
                }
           }

int main(){
int n;
int shmid=shmget((key_t)2345,1024,0666);
  
struct student *shm_memory=(struct student*) shmat(shmid,NULL,0);
  
for(n=0;shm_memory[n].rank!=-1;n++);
  sort_ranks(shm_memory,n);
  printf("Rank List:\n");
  printf("Rollno\tName\tRank\n");
        for(int i=0;i<n;i++){
                  printf("%d\t%s\t%d\n",shm_memory[i].rollno,shm_memory[i].name,shm_memory[i].rank);
}
shmdt(shm_memory);
shmctl(shmid,IPC_RMID,NULL);
return 0;
}
