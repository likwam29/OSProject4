
#include <math.h>
#include <limits.h>
#include <sys/mman.h>
#include <stdlib.h>

typedef struct block {
	int start;
	int end;
	int flagged;
	int used;
	
}Block;

struct block** blocks;

int globalSize;

int currIndex = 0;

int numObjects = 0;



// Template out methods
int initMemory(int sizeOfRegion);
void *allocateMemory(int size);
int freeMemory(int *ptr);
int isMemoryValid(void *ptr);
int getMemorySize(void *ptr);

// keep track of the pointer where to next place a memory block
// the int returned will be in hex

// create a struct that has a pointer address, and size of object.

// make an array of those objects

int main(){
	
	int temp = initMemory(5);
	
	printf("star point %i\n", temp);
	
	int i;
	for(i=0; i<globalSize;i++){
		printf("num of interation %i\n", i);
		
	}
	
	return 0;
}


//Allocates the memory to be used by the methods below.
//Returns 0 on success, -1 on failure
int initMemory(int sizeOfRegion){
	int temp = getpagesize();

	if(sizeOfRegion / temp < 1){
		sizeOfRegion = temp;
	}else{
		sizeOfRegion = temp * ceil(sizeOfRegion / temp);
	}

	int* memoryPointer = (int*) mmap(0, sizeOfRegion, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);

	blocks = malloc(sizeOfRegion * sizeof(struct block*));

	globalSize = sizeOfRegion;

	return (int) memoryPointer;
}

//Allocates size amount of memory and returns a pointer to the start of the memory block
//Returns Pointer or Null if not enough free space
void *allocateMemory(int size){
	
	struct block b;
	
	// if there are no objects in the data structure yet then add it to the first spot
	if(numObjects == 0){
		b.start = currIndex;
		b.end = currIndex + size;
		blocks[0] = b;
		numObjects++;
		return (int) b.start;
	}
	
	int minIndex = INT_MAX;
	int minIndexEndVal = 0;
	
	int i;
	for(i=0; i<globalSize; i++){
		// find open spot that is the smallest size. 
		
	}
}

//Frees memory if the pointer falls within an allocated block of memory
//returns 0 on success and -1 on failure
int freeMemory(int *ptr){
	
}

//Used in free memory.  Tells whether a pointer falls within an already allocated memory block
//Returns 1 if ptr falls in allocated block, 0 if it does not
int isMemoryValid(void *ptr){
	
}

//Used in allocateMemory to get the size of an allocated block
//returns the size in bytes of the memory block, otherwise -1
int getMemorySize(void *ptr){
	
}
