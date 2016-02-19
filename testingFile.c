#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char** argv)
{
    
    srand(time(NULL));
    int num;
    int i;
    
    /*
    int numTotal = 10;
    
    int begin = 0;
    int end = numTotal-1;
    
    int leftBegin = 0;
    int rightBegin = (numTotal-1)/2;
    int leftEnd = (numTotal-1)/2 + 1;
    int rightEnd = end;
    
    int nums[numTotal];
    
    ///////////////////////////////////////////
    for(i = 0; i < numTotal; i++)
    {
        nums[i] = rand()%2;
        //printf("%d\n", num);
    }
    for(i = 0; i < numTotal; i++)
    {
        printf("woot: %d\n", nums[i]);
    }
    ////////////////////////////////////////////
    if(begin != end)
    {
        pid_t pidRight = fork();
        pid_t pidLeft = fork();
        
    }
    */
    
    printf("About to Fork...\n");
    
    int rey[3] = {'1','2','0'};
    i = 0;
    int child_status;
    
    while(rey[i]>0)
    {
        //printf("Looped process ID : %d\n", getpid());
        pid_t pid = fork();
        i++;
        printf("Janis %d\n", pid);
        printf("Janis %d\n", i);
        /* This is run by the parent.  Wait for the child
        to terminate. */
        
    
        
    }
    
    /*
    if(pid == 0)
    {
        for(; i < 100; i++)
        {
            printf("parent: %d\n", i);
        }
    }
    else
    {
        for(; i < 100; i++)
        {
            printf("child (%d): %d\n", pid, i);
        }
    }
    */
}

//https://github.com/mlitman/CSC250_Fall2015_MergeSort/blob/master/Driver.java
//http://www.cs.ecu.edu/karl/4630/sum01/example1.html
//http://www.thegeekstuff.com/2012/03/c-process-control-functions/
