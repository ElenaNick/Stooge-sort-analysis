/******************************************************************************
 * Author: Elena Greblova
 * Class: CS 325
 * Assignment: HW2 - stooge sort timing
 * Date: 2017-10-8
 * Description: This program generates 7 arrays of random integers, then
 *              measures the time needed to sort it with stooge sort.
 *****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void stoogeSrt(int array[], int low, int high);
int* generate(int n);
float timing(int array[], int n);
void testRun(int n);

int main()
{
	srand(time(NULL));
	testRun(250);
	testRun(500);
	testRun(1000);
	testRun(2000);	
	testRun(4000);
	testRun(8000);
	testRun(16000);

	return 0;
}


/***************************************************
 *                    stoogeSrt()
 *Description: uses recursive stooge sort to sort
 *             an array
 *Parameters: array to sort,
 *            low - an index to start sorting from
 *            high - an index to stop sorting at
 **************************************************/
void stoogeSrt(int array[], int low, int high){
	int n = high - low + 1;
	//base case
	if(n == 2){
		if(array[low] > array[high]){
			int temp = array[low];
			array[low] = array[high];
			array[high] = temp;
		}
	}
	else{
		int m = (int) ceil((double)n*2/3);
		stoogeSrt(array, low, low+m-1);
		stoogeSrt(array, high-m+1, high);
		stoogeSrt(array, low, low+m-1);
	}
}



/**************************************************
 *              generate()
 *Description: generates an array of n random ints
 *             from 0 to 10,000
 *Pre-requisites: srand should be set before 
 *                calling this function
**************************************************/ 
int* generate(int n){
	int* array = malloc(n*sizeof(int));
	int i;
	for(i = 0; i < n; i++)
		array[i] = rand()% 10001;
	return array;
}

/**************************************************************
 *                 timing()
 *Description: calculates time in sec to sort an array of n 
 *             elements.
 ************************************************************/
float timing(int array[], int n){
	//record the start time
	clock_t t1 = clock();
	//stooge sort
	stoogeSrt(array, 0, n-1);
	//record the end time
	clock_t t2 = clock();
	//count the time taken by the sort
	float time = ((float)t2 - (float)t1) / CLOCKS_PER_SEC;
	return time;
}

/************************************************************************
 *                    testRun()
 *Description: generates an array on n random numbers and calls timing()
 *             to calculate time to sort the array. Then print out the 
 *             result
 **********************************************************************/
void testRun(int n){

	//fill the array with random numbers from 0 to 10,000
	int* array = generate(n);
	//calculate time and print the result
	float time = timing(array, n);
	printf("Time to sort %d elements is %f\n", n, time);
	free(array);
}


