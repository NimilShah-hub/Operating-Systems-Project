/* GROUP 34 :
		1741016 Kausha Vora
		1741048 Nimil Shah

A Multithreaded Program that implements the BANKER'S ALGORITHM


# compile
 	gcc banker_final.c -std=c99 -pthread

# execute
 	./a.out

 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>

int numberof_resources,
    numberof_processes;
int *totalinstances;
int *available_resources;
int **allocated_resources;
int **maxRequired_resources;
int **needof_resources;
int *safeSeq;
int nProcessRan = 0;

pthread_mutex_t lockResources;
pthread_cond_t condition;

// get safe sequence if there is one else return false
bool getSafeSeq();

// process function
void* processCode(void* );

int main(int argc, char** argv) 
{


	//reading total number of processes from the user
        printf("\nEnter Total Number Of Processes :  ");
        scanf("%d", &numberof_processes);


	//reading total number of resources from the user
        printf("\nEnter The Number Of Resources :  ");
        scanf("%d", &numberof_resources);



	//dynamic memory allocation	
        totalinstances = (int *)malloc(numberof_resources * sizeof(*totalinstances)); 
	
	available_resources = (int *)malloc(numberof_resources * sizeof(*available_resources));

	allocated_resources = (int **)malloc(numberof_processes * sizeof(*allocated_resources));
        for(int i=0; i<numberof_processes; i++)
	{
                allocated_resources[i] = (int *)malloc(numberof_resources * sizeof(**allocated_resources));
	}

	maxRequired_resources = (int **)malloc(numberof_processes * sizeof(*maxRequired_resources));
        for(int i=0; i<numberof_processes; i++)
	{
                maxRequired_resources[i] = (int *)malloc(numberof_resources * sizeof(**maxRequired_resources));
	}

	needof_resources = (int **)malloc(numberof_processes * sizeof(*needof_resources));
        for(int i=0; i<numberof_processes; i++)
	{
                needof_resources[i] = (int *)malloc(numberof_resources * sizeof(**needof_resources));
	}

	safeSeq = (int *)malloc(numberof_processes * sizeof(*safeSeq));




	//reading instances of every resource from the user
	printf("\nEnter Total Instances Of Every Resource [Press Enter]:  ");
        for(int i=0; i<numberof_resources; i++)
	{
		scanf("%d", &totalinstances[i]);
	}
	printf("\n");

	

        // Reading allocated resource matrix for every process from the user
        for(int i=0; i<numberof_processes; i++) 
	{
                printf("\nResource Matrix Allocated To Process %d [Press Enter]:  ", i);
                for(int j=0; j<numberof_resources; j++)
		{
                        scanf("%d", &allocated_resources[i][j]);
		}
        }
	printf("\n");

	

	//calculating available resource vectore for every resource after above allocation
	for(int i=0; i<numberof_resources; i++)
	{
		int sumResource = 0;
		for(int j=0; j<numberof_processes; j++)
		{
		        sumResource += allocated_resources[j][i];
		}	
		available_resources[i] = totalinstances[i] - sumResource;			
	}
	


	// Reading maximum required resources matrix for every process from the user
        for(int i=0; i<numberof_processes; i++) 
	{
                printf("\nMaximum Resource Matrix Required By Process %d [Press Enter] :  ", i);
                for(int j=0; j<numberof_resources; j++)
		{
                        scanf("%d", &maxRequired_resources[i][j]);
		}
        }
        printf("\n");




	// calculating need matrix for every process
        for(int i=0; i<numberof_processes; i++)
	{
                for(int j=0; j<numberof_resources; j++)
		{
                        needof_resources[i][j] = maxRequired_resources[i][j] - allocated_resources[i][j];
		}
	}




	// initializing the variable safeSeq to -1 
        for(int i=0; i<numberof_processes; i++) 
	{
		safeSeq[i] = -1;
	}




	//function call to 'getSafeSeq' (getSafeSeq returns false if safe state sequence is not found; else gives a sequence)
        if(!getSafeSeq()) 
	{ 
                printf("\nUnsafe State! The processes lead the system to an UNSAFE STATE.\n\n");
                exit(-1);
        }

	printf("\nExecuting Safe State Sequence Algorithm\n\n");
        sleep(1);

        printf("\n\nSafe Sequence Found : ");
        for(int i=0; i<numberof_processes; i++) 
	{
                printf("%-3d", safeSeq[i]);
        }

        
	
	// run threads
	pthread_t processes[numberof_processes];
        pthread_attr_t attr;
        pthread_attr_init(&attr);

	int processNumber[numberof_processes];
	for(int i=0; i<numberof_processes; i++) 
	{
		processNumber[i] = i;
	}

        for(int i=0; i<numberof_processes; i++)
	{
                pthread_create(&processes[i], &attr, processCode, (void *)(&processNumber[i]));
	}

        for(int i=0; i<numberof_processes; i++)
	{
                pthread_join(processes[i], NULL);
	}

        printf("\nAll Processes Successfully Executed\n");	
	



	// free resources
        free(available_resources);
        for(int i=0; i<numberof_processes; i++) 
	{
                free(allocated_resources[i]);
                free(maxRequired_resources[i]);
		free(needof_resources[i]);
        }
        
	free(allocated_resources);
        free(maxRequired_resources);
	free(needof_resources);
        free(safeSeq);
}
//end of main()





// function to generate the safe sequence
bool getSafeSeq() 
{
	
        int tempRes[numberof_resources];
        for(int i=0; i<numberof_resources; i++) 
	{
		tempRes[i] = available_resources[i]; //initializing tempRes vector with currently available resources vector
	}

        bool finished[numberof_processes];
        for(int i=0; i<numberof_processes; i++) 
	{
		finished[i] = false; //initializing finished vector with false
        }

	int nfinished=0;
        while(nfinished < numberof_processes) 
	{
                bool safe = false;

                for(int i=0; i<numberof_processes; i++) 
		{
                        if(!finished[i]) 
			{	
                                bool possible = true;

                                for(int j=0; j<numberof_resources; j++)
				{
                                        if(needof_resources[i][j] > tempRes[j]) 
					{ 
                                                possible = false;
                                                break;
                                        }
				}

                                if(possible) 
				{                                        
					 for(int j=0; j<numberof_resources; j++)
					 {
                                                tempRes[j] += allocated_resources[i][j]; 
					 }

                                        safeSeq[nfinished] = i; 
                                        finished[i] = true; 	
                                        ++nfinished;		
                                        safe = true;
                                }
                        }
                }

                if(!safe) 
		{ 
                        for(int k=0; k<numberof_processes; k++) safeSeq[k] = -1;
                        return false; // no safe sequence found
                }
        }

        return true; // safe sequence found
}
//end of getSafeSeq()




// process code
void* processCode(void *arg) {
        int p = *((int *) arg);

	// lock resources
        pthread_mutex_lock(&lockResources);

        // condition check
        while(p != safeSeq[nProcessRan])
                pthread_cond_wait(&condition, &lockResources);

	// process
        printf("\n--> Process %d", p);
        printf("\n\tAllocated Matrix : ");
        for(int i=0; i<numberof_resources; i++)
	{
                printf("%3d", allocated_resources[p][i]);
	}

        printf("\n\tNeed Matrix      : ");
        for(int i=0; i<numberof_resources; i++)
 	{
               printf("%3d", needof_resources[p][i]);
	}

        printf("\n\tAvailable Vector : ");
        for(int i=0; i<numberof_resources; i++)
	{
                printf("%3d", available_resources[i]);
	}

        printf("\n"); 
	sleep(1);
        printf("\tResources Allocated!");
        printf("\n"); 
	sleep(1);
        printf("\tExecution Of BANKER'S ALGORITHM");
        printf("\n"); 
	sleep(1);
        printf("\tResources Released!");
	sleep(1);
	
	for(int i=0; i<numberof_resources; i++)
	{
		available_resources[i] += allocated_resources[p][i];
	}

        printf("\n\tResources Now Available : ");
        for(int i=0; i<numberof_resources; i++)
	{
                printf("%3d", available_resources[i]);
	}
        printf("\n\n");

        sleep(1);

	// condition broadcast
        nProcessRan++;
        pthread_cond_broadcast(&condition);
        pthread_mutex_unlock(&lockResources);
	pthread_exit(NULL);
}
