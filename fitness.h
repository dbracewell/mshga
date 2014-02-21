/****************************************************************
* fitness.h
* David B. Bracewell
* 12/17/2004
*
* Base Abstract Fitness Class
****************************************************************/
#ifndef FITNESS_H
#define FITNESS_H

#include "chromosome.h"
#include <algorithm>

/**
* Abstract fitness class.
* An Abstract fitness class that is a unary funtor. Used as a base to create
* problem specfic fitness functions.
*/
template<class type>
class FitnessFunction
{
public:

	/**
	* Function Method.
	* Method to call the class like a functional	.
	* @param chromosome a chromosome to determine the fitness of.
	* @return double fitness of the chromosome
	*/
	virtual double operator() ( const Chromosome<type>& chromosome)=0;
}; 


/**
* Count Number Fitness.
* A simple fitness function where the fitness is the number
* of occurences of a number in the chromosome
*/
class CountNumberFitness : public FitnessFunction<int>
{
public:
  /**
   * Constructor
   * Only way to create an instance of the class
   * @param Number the number that are you looking for when calculating fitness
   */
  CountNumberFitness(int Number):mNum(Number){;}
  

  /**
   * Function Method.
   * Method to call the class like a functional	.
   * @param chromosome a chromosome to determine the fitness of.
   * @return double fitness of the chromosome
   */
  virtual double operator()(const Chromosome<int>&  chromosome )
  {
	return std::count(chromosome.genes.begin(), chromosome.genes.end(), mNum);
  }

private:
  int mNum;

};

#endif 
