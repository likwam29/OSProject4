int initMemory(int sizeOfRegion);
void *allocateMemory(int size);
int freeMemory(int *ptr);
int isMemoryValid(void *ptr);
int getMemorySize(void *ptr);

//Allocates the memory to be used by the methods below.
//Returns 0 on success, -1 on failure
int initMemory(int sizeOfRegion)
{
	int temp = getpagesize();

	if(sizeOfRegion / temp < 1)
		sizeOfRegion = temp;
	else{
		sizeOfRegion = temp * ceil(sizeOfRegion / temp);
	}

	int *memoryPointer = mmap(0, sizeOfRegion, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);

	return memoryPointer;
}

//Allocates size amount of memory and returns a pointer to the start of the memory block
//Returns Pointer or Null if not enough free space
void *allocateMemory(int size)
{
	
}

//Frees memory if the pointer falls within an allocated block of memory
//returns 0 on success and -1 on failure
int freeMemory(int *ptr)
{
	
}

//Used in free memory.  Tells whether a pointer falls within an already allocated memory block
//Returns 1 if ptr falls in allocated block, 0 if it does not
int isMemoryValid(void *ptr)
{
	
}

//Used in allocateMemory to get the size of an allocated block
//returns the size in bytes of the memory block, otherwise -1
int getMemorySize(void *ptr)
{
	
}
