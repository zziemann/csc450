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
    
    int numTotal = 10;
    
    int begin = 0;
    int end = numTotal-1;
    
    int leftBegin = 0;
    int rightBegin = (numTotal-1)/2;
    int leftEnd = (numTotal-1)/2 + 1;
    int rightEnd = end;
    
    int nums[numTotal];
    
    //////////RANDOM NUMBERS///////////////////////////
    for(i = 0; i < numTotal; i++)
    {
        nums[i] = rand()%2;
        //printf("%d\n", num);
    }
    for(i = 0; i < numTotal; i++)
    {
        printf("Janis: %d\n", nums[i]);
    }
    ///////////////////////////////////////////////
    
    while(begin != end)
    {
        pid_t pidRight, pidLeft = fork();
        if we're in pidLeft 
        {
            begin = leftBegin;
            end = leftEnd;
        }
        
        if we're in pidRight
        {
            begin = rightBegin;
            end = rightEnd;
            wait(for pidLeft to terminate)
        }
        
        if(pidLeft == 0)
        //we're in parent
        {
            wait(for pidRight to terminate)
        }
        
        int tempRey[rightEnd-leftBegin+1];
        int currLeft = leftBegin;
        int currRight = rightBegin;
        
        for(int tempPos = 0; tempPos < (rightEnd-leftBegin+1); tempPos++)
        {
            if(currLeft > leftEnd)
            {
                tempRey[tempPos] = nums[currRight];
                currRight++;
            }
            
            else if(currRight > rightEnd)
            {
                temp[tempPos] = nums[currLeft];
                currLeft++;
            }
            else
            {
                if(nums[currLeft] < nums[currRight])
                {
                    temp[tempPos] = nums[currLeft];
                    currLeft++;
                }
                else
                {
                    temp[tempPos] = nums[currRight];
                    currRight++;
                }
            }
        }
        int tempPos = 0;
        for(int i = leftBegin; i<= rightEnd; i++)
        {
            nums[i] = nums[tempPos];
            tempPos++;
        }
        
        
    }
    
}