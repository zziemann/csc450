#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include "shmExample.h"
#define SHMSZ 9


 int main(int argc, char** argv)
 { 
    char c;
    int shmid;
    key_t key;
    char *shm, *s;

    /*
     * We'll name our shared memory segment
     * "5678".
     */
    key = 5678;

    /*
     * Create the segment.
     */
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        return -1;
    }
    
    /*
     * Now we attach the segment to our data space.
     */
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        return -1;
    }
    
    //settting the scene
    int i = 1;
    for(; i < 10; i++)
    {
        shm[i] = '?';
    }
   
    shm[0] = 'P';
    int pid = fork();
    int test = 0;
    int test2 = 0;
    
    if(pid != 0)
    {
        while(test < 500)
        {
            //parent
            if(shm[0] == 'P')
            {
                int tempRand = 0;
                tempRand = randomize();
                
                while(shm[tempRand] != '?')
                {
                    tempRand = randomize();
                }
                //printf("Test is (Parent): %d\n ", tempRand);
                shm[tempRand] = 'x';
                
                test++;
                
                if((((shm[1] == shm[2]) && (shm[1] == shm[3])) && (shm[1] == 'x')) || 
                   (((shm[4] == shm[5]) && (shm[4] == shm[6])) && (shm[4] == 'x')) ||      
                   (((shm[7] == shm[8]) && (shm[7] == shm[9])) && (shm[7] == 'x')) ||     
                   (((shm[1] == shm[4]) && (shm[1] == shm[7])) && (shm[1] == 'x')) ||
                   (((shm[2] == shm[5]) && (shm[2] == shm[8])) && (shm[2] == 'x')) ||
                   (((shm[3] == shm[6]) && (shm[3] == shm[9])) && (shm[3] == 'x')) ||
                   (((shm[1] == shm[5]) && (shm[1] == shm[9])) && (shm[1] == 'x')) ||
                   (((shm[7] == shm[5]) && (shm[7] == shm[3])) && (shm[7] == 'x')))
                   {
                       printf("The grand winner is X's (parent)\n");
                       
                       display(shm);
    
                       return 0;
                   }
                   else if( shm[1] != '?' && 
                             shm[2] != '?' && 
                             shm[3] != '?' &&           
                             shm[4] != '?' &&
                             shm[5] != '?' &&
                             shm[6] != '?' && 
                             shm[7] != '?' && 
                             shm[8] != '?' && 
                             shm[9] != '?')
                   {
                       printf("It's a tie)\n");
                       
                       display(shm);
                        
                        return 0;
                   } 
                   
                   shm[0] = 'C';
            }
            waitWhileEqual('C', shm);
        }
    }
    else
    {
       while(test2 < 500)
        {
            if(shm[0] == 'C')
            {
                int tempRand2 = 0;
                tempRand2 = randomize();
                
                while(shm[tempRand2] != '?')
                {
                    tempRand2 = randomize();
                }
                //printf("Test is (Child): %d\n ", tempRand2);
                shm[tempRand2] = 'o';
                
                test2++;
                
                if((((shm[1] == shm[2]) && (shm[1] == shm[3])) && (shm[1] == 'o')) || 
                   (((shm[4] == shm[5]) && (shm[4] == shm[6])) && (shm[4] == 'o')) ||      
                   (((shm[7] == shm[8]) && (shm[7] == shm[9])) && (shm[7] == 'o')) ||     
                   (((shm[1] == shm[4]) && (shm[1] == shm[7])) && (shm[1] == 'o')) ||
                   (((shm[2] == shm[5]) && (shm[2] == shm[8])) && (shm[2] == 'o')) ||
                   (((shm[3] == shm[6]) && (shm[3] == shm[9])) && (shm[3] == 'o')) ||
                   (((shm[1] == shm[5]) && (shm[1] == shm[9])) && (shm[1] == 'o')) ||
                   (((shm[7] == shm[5]) && (shm[7] == shm[3])) && (shm[7] == 'o')))
                   {
                       printf("The grand winner is O's (child)\n");
                       
                       display(shm);
    
                       return 0;
                   }
                   else if( shm[1] != '?' && 
                             shm[2] != '?' && 
                             shm[3] != '?' &&           
                             shm[4] != '?' &&
                             shm[5] != '?' &&
                             shm[6] != '?' && 
                             shm[7] != '?' && 
                             shm[8] != '?' && 
                             shm[9] != '?')
                   {
                       printf("It's a tie)\n");
                       
                       display(shm);
                        
                        return 0;
                   }          
                   
                   shm[0] = 'P';
            }
            waitWhileEqual('P', shm);
        }
    }
    
    return 0;
 }
 
 void waitWhileEqual(char val, char* shm)
 {
    while(shm[0] == val)
    {
        //wait
    }
 }
 
 int randomize()
 {
     int val = 0;
     do
     {
         val = rand()%10;
     }
     while(val == 0);
     return val;
 }
 
  
 void display(char* shm)
 {
     printf(" %c |", shm[1]);
     printf(" %c |", shm[2]);
     printf(" %c\n", shm[3]);
     printf(" ---------\n");
     printf(" %c |", shm[4]);
     printf(" %c |", shm[5]);
     printf(" %c\n", shm[6]);
     printf(" ---------\n");
     printf(" %c |", shm[7]);
     printf(" %c |", shm[8]);
     printf(" %c\n", shm[9]);
 }