#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

int main() 
{ 
    key_t key;
    int i=0;
    char *s, buff[20]="MCOE college";
	// ftok to generate unique key 
	key = ftok(".",10); 


	// shmget returns an identifier in shmid 
	int shmid = shmget(key,1024,0666|IPC_CREAT); 

	// shmat to attach to shared memory 
	char *shm = (char*) shmat(shmid,(void*)0,0); 

	printf("Write Data : ");
	
	s=shm;
	for(i=0;buff[i]!='\0';i++)
	    {
	        *s=buff[i];
	        s++;
	    }

	printf("Data written in memory: %s\n",shm); 
	
	//detach from shared memory 
	shmdt(shm); 

	return 0; 
} 
