#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char *argv[])
{

   srand(time(NULL));
   int numberOfNums = 100;
	int array[numberOfNums];
	int length = 0;
	int data;

	int *sharedArray;
	int sharedMemoryId;
	key_t key;
	int i;
	size_t sharedArraySize;
	

	while(length < numberOfNums)
	{
		array[length] = rand() % 10;
		length++;
	}
	
	
	key = IPC_PRIVATE; // this states the parents id is where the shared array began


	sharedArraySize = length * sizeof(int);
	
	if ((sharedMemoryId = shmget(key, sharedArraySize, IPC_CREAT | 0666)) == -1) { //create shared memory
		perror("shmget");
		exit(1);
	}

	//connects shared array to the shared memory location
	if ((sharedArray = shmat(sharedMemoryId, NULL, 0)) == (int *) -1) {
		perror("shmat");
		exit(1);
	}

	for (i = 0; i < length; i++) {
		sharedArray[i] = array[i];
	}

	display(sharedArray, length);
	mergesort(sharedArray, length);
	printf("//////////////////////done sorting//////////////////////////////\n");
	display(sharedArray, length);

   //computation is complete, shared array doesnt need to be shared
	if (shmdt(sharedArray) == -1) {
		perror("shmdt");
		exit(1);
	}

	/* Delete the shared memory segment. */
	if (shmctl(sharedMemoryId, IPC_RMID, NULL) == -1) {
		perror("shmctl");
		exit(1);
	}

	return 0;
}

void display(int array[], int length)
{
	int i;
	printf(">");
	for (i = 0; i < length; i++)
		printf(" %d", array[i]);
	printf("\n");
}

void merge(int *left, int leftLength, int *right, int rightLength)
{
	int *leftTemp = (int *) malloc(leftLength * sizeof(int));
	int *rightTemp = (int *) malloc(rightLength * sizeof(int));

	int *leftLocation = leftTemp; //pointer to bucket 0 of left temp 
	int *rightLocation = rightTemp; //pointer to bucket 0 of right temp

	int *finalTemp = left;


	memcpy(leftTemp, left, leftLength * sizeof(int)); //copies left array into temp left and the num of bytes
	memcpy(rightTemp, right, rightLength * sizeof(int));

	while (leftLength > 0 && rightLength > 0) 
	{
		if (*leftLocation <= *rightLocation) 
		{
			//left value is less then right values
			*finalTemp = *leftLocation; //store left value
			++leftLocation; //move pointer in left array to the next bucket
			--leftLength; //leftLength is 1 less
		} else {
			//right value is less the left
			*finalTemp = *rightLocation; // store right value in the bucket in result
			++rightLocation; //pointer changes to next bucket
			--rightLength; //right length is 1 less
		}
		++finalTemp; //pointer changes to next bucket
	}
	
	if (leftLength > 0)
	{
		while (leftLength > 0) {
			//left array is the only one with values left
			*finalTemp = *leftLocation; //add number in left Location to the final tempArray
			++finalTemp; // move location to next bucket in array
			++leftLocation; // move location to next bucket in array
			--leftLength; //we have take one out of the left Array
		}
	}	
	else
	{
		while (rightLength > 0) {
			//right array is the only one with values left
			*finalTemp= *rightLocation;
			++finalTemp;
			++rightLocation;
			--rightLength;
		}
	}
	
	/* Release the memory used for the temporary arrays. */
	free(leftTemp);
	free(rightTemp);
}

void mergesort(int array[], int length)
{
	int middleIndex;
	int *left, *right;
	int leftLength;

	int leftChild = -1;
	int rightChild = -1;

	int status;

	if (length <= 1)
		return;

	middleIndex = length / 2;

	leftLength = length - middleIndex;

	left = array;
	right = array + leftLength;

	leftChild = fork();
	if (leftChild < 0) {
		perror("fork");
		exit(1);
	}
	if (leftChild == 0) {
		mergesort(left, leftLength);
		exit(0);
	} else {
		rightChild = fork();
		if (rightChild < 0) {
			perror("fork");
			exit(1);
		}
		if (rightChild == 0) {
			mergesort(right, middleIndex);
			exit(0);
		}
	}
	
	//wait for children to be done
	waitpid(leftChild, &status, 0);
	waitpid(rightChild, &status, 0);
	
	//merge both children together
	merge(left, leftLength, right, middleIndex);
}

