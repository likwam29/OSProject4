//Matthew Likwarz

#include <math.h>
#include <limits.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct block {
	void* start;
	void* end;
	int size;
	int flagged;
	int used;
	
}Block;

struct block blocks[];

int globalSize;

void* currIndex;

int hateThis = 0;

int numObjects = 0;



// Template out methods
int initMemory(int sizeOfRegion);
void *allocateMemory(int size);
int freeMemory(void *ptr);
int isMemoryValid(void *ptr);
int getMemorySize(void *ptr);


// This was left in the code so the stupid thing would still compile.
int main(void){
	
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

	currIndex = (void*) mmap(0, sizeOfRegion, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);

	blocks[sizeOfRegion];
	//blocks = malloc(sizeOfRegion * sizeof(struct block));

	globalSize = sizeOfRegion;

	return 0;
}

//Allocates size amount of memory and returns a pointer to the start of the memory block
//Returns Pointer or Null if not enough free space
void *allocateMemory(int size){
	
	struct block b;
	
	// if there are no objects in the data structure yet then add it to the first spot
	if(numObjects == 0){
		b.start = currIndex;
		b.end = currIndex + size;
		b.used = 1;
		b.size = size;
		blocks[0] = b;
		numObjects++;
		hateThis++;
		return &blocks[0];
	}
	
	int minIndex = 0;
	int minIndexEndVal = INT_MAX;
	
	int i;
	int j;
	for(i=0; i<globalSize; i++){
		// find open spot that is the smallest size.
		if(blocks[i].used == 1){
			for(j=1; j<globalSize; j++){
				if(blocks[j].used == 1){
					long one = (long)blocks[i].start + (long)blocks[i].end;
					long two = (long)blocks[j].start + (long)blocks[j].end;
					long diff = one - two;
					if(one < two){
						diff = two - one;
					}
				
					if(diff >= size && diff < minIndexEndVal){
						minIndexEndVal = diff;
						minIndex = i;
					}
				}			
			}
		}
	}

	// if we didn't find anything then return the NULL guy
	if(minIndex == 0){
		return NULL;
	}

	// Otherwise assign the thing so it works
	b.start = (void*)(long)blocks[minIndex].start + (long)blocks[minIndex].end + 1;
	b.end = b.start + size;
	b.used = 1;
	blocks[hateThis] = b;
	numObjects++;
	hateThis++;
	return b.start;
}

//Frees memory if the pointer falls within an allocated block of memory
//returns 0 on success and -1 on failure
int freeMemory(void *ptr){
	return isMemoryValid(ptr);
}

//Used in free memory.  Tells whether a pointer falls within an already allocated memory block
//Returns 1 if ptr falls in allocated block, 0 if it does not
int isMemoryValid(void *ptr){
	int retVal = -1;
	int i;
	for(i=0; i<globalSize; i++){
		// find open spot that is the smallest size.
		if(blocks[i].used == 1){
			void* start = blocks[i].start;
			void* end = blocks[i].end;
			void* temp = ptr;

			if(temp >= start && temp <= end){
				blocks[i].used = 0;
				retVal = 0;
			}
		}
	}
	return retVal;
}

//Used in allocateMemory to get the size of an allocated block
//returns the size in bytes of the memory block, otherwise -1
int getMemorySize(void *ptr){
	int retVal = -1;
	int i;
	for(i=0; i<globalSize; i++){
		// find open spot that is the smallest size.
		if(blocks[i].used == 1){
			void* start = blocks[i].start;
			void* end = blocks[i].end;
			void* temp = ptr;

			if(temp >= start && temp <= end){
				blocks[i].used = 0;
				retVal = blocks[i].size;
			}
		}
	}
	return retVal;
}
