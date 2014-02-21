/**
* RandomNumber.h.
* @author David B. Bracewell
* @date 12/14/2004
*/
#ifndef RANDOMNUMBER_H
#define RANDOMNUMBER_H

#include <ctime>
#include <cmath>
#include <cstdlib>

/**
* Random Number Class.
* Implements static methods for random numbers
*/
class RandomNumber
{
	public:

		/**
		* Random number generator seed.
		* Seeds the random number generator with the current time.
		* This method should be called at least once before using
		* the next* methods.
		*/
		static void seed();

		/**
		* Next Random Percentage.
		* Gets the next random percentage
		* @return A double between 0 and  100
		*/
		static double nextPercentage();
		
		/**
		* Next Random Number between 0 and upper bound.
		* Gets the next random number between 0 and nMax		
		* @param nMax an integer upper bound is nMax - 1
		* @return an integer between 0 and nMax - 1
		*/
		static int nextNumber(int nMax);

		/**
		* Next Random Number between lower and upper bound.
		* Gets the next random number between nMin and nMax
		* @param nMin an integer lower bound
		* @param nMax an integer upper bound is nMax - 1
		* @return an integer between nMin and nMax - 1
		*/
		static int nextNumber(int nMin, int nMax);

		/**
		* Next Boolean. 
		* Gets the next random boolean number
		* @return a boolean
		*/
		static bool nextBoolean();
};


/*********************************************
* RandomNumber::seed()
*********************************************/
inline void RandomNumber::seed()
{
	srand( (unsigned)time( NULL ) );
}

/*********************************************
* RandomNumber::nextPercentage()
*********************************************/
inline double RandomNumber::nextPercentage()
{
	//Get a number and divide it by 1 less than the max rand() can generate
	return ((double)rand()/(double)(RAND_MAX-1)); 
}

/*********************************************
* RandomNumber::nextNumber()
*********************************************/
inline int RandomNumber::nextNumber(int nMax)
{
	return (rand()%nMax);
}

/*********************************************
* RandomNumber::nextNumber()
*********************************************/
inline int RandomNumber::nextNumber(int nMin, int nMax)
{
	//calculate maximum
	int newMax = nMax - nMin;
	
	//if the user gave numbers that are out of whack return 0
	if( newMax <= 0 )
	{
		return 0;
	}
	
	//get the number between 0 and newMax-1 and add the minimum to it
	return ( (rand() % newMax) + nMin );
}

/*********************************************
* RandomNumber::nextBoolean()
*********************************************/
inline bool RandomNumber::nextBoolean()
{
	return  ( ( rand() % 2 ) == 1);
}


#endif
