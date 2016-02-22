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
    
    int nums[numTotal];
    
    //////////RANDOM NUMBERS///////////////////////////
    for(i = 0; i < numTotal; i++)
    {
        nums[i] = rand()%10;
        //printf("%d\n", num);
    }
    
     for(i = 0; i < numTotal; i++)
    {
        printf("Old: %d\n", nums[i]);
    }
    ///////////////////////////////////////////////
    
    mergeSortDriver(nums, numTotal);
    
    for(i = 0; i < numTotal; i++)
    {
        printf("Sorted: %d\n", nums[i]);
    }
}
    
//---------------------------------------------------------------------------

void mergeSortDriver(int rey[], int reyLength)
{
    mergeSort(rey, 0, reyLength-1);
}
    
void mergeSort(int rey[], int begin, int end)
{
    if(begin != end)
    {
       
        int leftBegin = begin;
        int rightBegin = ((end-begin)/2 + begin) + 1;
        int leftEnd = ((end-begin)/2) + begin;
        int rightEnd = end;
        
        mergeSort(rey, leftBegin, leftEnd);
        mergeSort(rey, rightBegin, rightEnd);
        
        int tempRey[rightEnd-leftBegin+1];
        int currLeft = leftBegin;
        int currRight = rightBegin;
        
        int tempPos = 0;
        for(; tempPos < (rightEnd-leftBegin+1); tempPos++)
        {
            if(currLeft > leftEnd)
            {
                tempRey[tempPos] = rey[currRight];
                currRight++;
            }
            
            else if(currRight > rightEnd)
            {
                tempRey[tempPos] = rey[currLeft];
                currLeft++;
            }
            else
            {
                if(rey[currLeft] < rey[currRight])
                {
                    tempRey[tempPos] = rey[currLeft];
                    currLeft++;
                }
                else
                {
                    tempRey[tempPos] = rey[currRight];
                    currRight++;
                }
            }
        }
        int tempPos2 = 0;
        int loopVar = leftBegin;
        for(; loopVar<= rightEnd; loopVar++)
        {
            rey[loopVar] = tempRey[tempPos2];
            tempPos2++;
        }
   
    }
}
    
