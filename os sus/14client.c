#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

int main() 
{ 
	int i=0;
    char *s;
	// ftok to generate unique key 
	key_t key = ftok(".",10); 


	// shmget returns an identifier in shmid 
	int shmid = shmget(key,1024,0666|IPC_CREAT); 

	// shmat to attach to shared memory 
	char *shm = (char*) shmat(shmid,(void*)0,0); 
	
	s=shm;

	printf("Data read from memory: %s\n",s); 
	
	//detach from shared memory 
	shmdt(shm); 
	
	// destroy the shared memory 
	shmctl(shmid,IPC_RMID,NULL); 
	
	return 0; 
} 

