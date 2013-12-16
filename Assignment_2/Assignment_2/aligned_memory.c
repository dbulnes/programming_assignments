//
//  main.c
//  Assignment_2
//
//  Created by David on 12/15/13.
//  Copyright (c) 2013 David Bulnes. All rights reserved.
//

/*
 Assignment 2:
 In C programming, you've probably used the following two functions from stdlib.h to respectively allocate and deallocate memory from the heap:
 
 void * malloc(size_t size);
 void free(void *ptr);
 
 The C language specification does not specify certain properties of memory allocated by malloc.  One of these unspecified properties is whether the allocated memory is aligned.  An n-byte aligned address is defined as an address that is a multiple of n bytes, where n is restricted to be a power of 2.  An n-byte aligned address is also sometimes referred to as an address that falls on a n-byte boundary.
 
 Your job is to implement a pair of functions that allocate and deallocate memory like malloc and free, but return addresses that aligned to an n-byte boundary, where n is again guaranteed to be a power of 2.  Use the following two prototypes as a reference:
 
 void * aligned_malloc(size_t size, size_t alignment);
 void aligned_free(void * ptr);
 
 You may use malloc and free to implement your solution.  Implement these, along with a small main() function that demonstrates their use.  Your solution should be a single C source file that may be compiled using a standard C compiler.
 
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * The general approach taken with writing aligned_malloc is to allocate enough memory, taking into account
 * extra memory within the allocated range to use for an aligned address (see memSize variable).
 *
 * Since we are allocating more memory than will be used or returned, a method of tracking the originally allocated address
 * is needed for when aligned_free is called. Originally, I thought to store a void * pointer to this original address
 * after the upper bound of the returned aligned address (ie address at aligned address + bytes requested + 1),
 * but this approach was problematic as it required aligned_free to know the upper bound of the word at the
 * void * pointer passed to aligned_free as a parameter. Instead, I decided to do the opposite and store the original
 * address (void *) bytes behind the returned aligned address. This way, aligned_free will know to look (void *)
 * bytes behind the void * parameter passed to it, in order to find the address from which it should actually free memory.
 * This way, all of the memory allocated using the original malloc call in aligned_malloc will be freed, instead of
 * only the memory starting at the aligned address passed to aligned_Free , which will typicaly be ahead of the original address.
 */

/** @function aligned_malloc
 *  @brief Allocates memory at a n-byte aligned address where n = size_t alignment parameter.
 *
 *  @param size_t bytes: The number memory bytes to allocate.
 *  @param size_t alignment: The power of 2 from which to align the allocated memory.
 *  @return void *
 */
void *aligned_malloc(size_t bytes, size_t alignment)
{
    //Declare the two memory pointers we will use- originalAddress to store the first malloc address,
    //and alignedAddress that will be the n-byte aligned memory address that is returned.
    void *originalAddress, *alignedAddress;
    size_t upperMemoryBound; //Will store the location of the upper memory bound of our original malloc call.
    
    /**
     * Compute the total number of bytes we will possibly need to allocate.
     * Sum together a void * pointer size, the bytes requested, and the power of 2 alignment requested.
     * We will use the void * pointer to store the originally allocated address,. We will add
     * alignment number of bytes to find an address that is a factor of the value of alignment, which at most is
     * aligned bytes away from originalAddress.
     */
    size_t memSize = sizeof(void *) + bytes + alignment;
    originalAddress = malloc(memSize); //Use the regular malloc function to allocate all our memory initially.
    if (!originalAddress) {
        return NULL;
    }
    
    //Find the upper memory bound allocated. Add the original address, plus memsize.
    //Subtract the parameter size_t bytes from this sum, as those are the bytes actually requested
    //in the call to aligned_malloc
    upperMemoryBound = (size_t)originalAddress + memSize - bytes;
    //By finding the modulo of upperMemoryBound and alignment, we will know how many bytes to move
    //away from upperMemoryBound to be at an aligned address.
    size_t bytesToMoveIntoAlignment = upperMemoryBound%alignment;
    alignedAddress = (void *)(upperMemoryBound - bytesToMoveIntoAlignment);
    
    
    //Store a void * pointer to the originalAddress pointer one void * address behind alignedAddress
    //*((size_t *)alignedAddress-1)= *(void *)originalAddress;
    ((void **)alignedAddress)[-1] = originalAddress;
    return alignedAddress;
}

/** @function aligned_malloc
 *  @brief Takes the void *ptr parameter and looks one void* address back to find the originally allocated
 *         address from aligned_malloc. Frees the memory starting at this original address.
 *
 *  @param void *ptr: The pointer from which to look backwards to the originally allocated address and free memory.
 *  @return void
 */
void aligned_free(void *ptr) {
    void **originalAddress = ((void **)ptr)[-1];
    free(originalAddress);
}


int main(int argc, const char * argv[])
{
    int *alignedMemory = (int *)aligned_malloc(6, 8);
    *alignedMemory = (int)1024;
    
    aligned_free(alignedMemory);
    return 0;
}

