/****************************************************************
* geneticOperators.h
* David B. Bracewell
* 12/17/2004
*
* Genetic operators, base fitness function, base selection method
****************************************************************/
#ifndef GENETICOPS_H
#define GENETICOPS_H

#include <vector>
#include "randomNumber.h"
#include "chromosome.h"

/**
* Abstract Mutation Operator.
* Abstract mutation operator that implements a virtual function call.
* Mutation works on a gene by gene basis
*/
template<class type>
class MutationOperator
{
 public:
	/**
	* Function Method.
	* Method to call the class like a function. 
	* @param gene the gene to mutate
	* @return the gene after mutation
	*/
    virtual type operator()(type gene)=0;
    
};


/**
* A boolean flip for integers.
* Mutation operator that returns 1 - value for mutation. 
* To be used when integers are being used for binary values.
*/
class IntBooleanFlip : public MutationOperator<int>
{
public:
	/**
	* Function Method.
	* Method to call the class like a function. 
	* @param gene the gene to mutate
	* @return 1 - the gene value
	*/
    virtual int operator()( int gene )
    {
	  return 1 - gene;
	}

};



/**
* Abstract Crossover Operator.
* Abstract crossover operator that implements a virtual function call
*/
template<class type>
class CrossoverOperator
{
public:
	/**
	* Function Method.
	* Method to call the class like a function. 
	* @param mother the first parent chromosome
	* @param father the second parent chromosome
	* @return pair of children chromosomes
	*/
	virtual  std::pair< Chromosome<type> , Chromosome<type> >
	operator()(const Chromosome<type>& mother, const Chromosome<type>& father )=0;

};

/**
* One Point Crossover.
* One Point Crossover functor taking two parent chromosomes.
*/
template<class type>
class OnePointCrossover : public CrossoverOperator<type>
{
public:

	/**
	* Function Method.
	* Method to call the class like a function. Upon completion the parameters will have
	* the results of the one point crossover.
	* @param mother the first parent chromosome
	* @param father the second parent chromosome
	* @return pair of children chromosomes
	*/
	virtual  std::pair< Chromosome<type> , Chromosome<type> >
	operator()(const Chromosome<type>& mother, const Chromosome<type>& father );
};



/**
* Two Point Crossover.
* Two Point Crossover functor taking two parent chromosomes.
*/
template<class type>
class TwoPointCrossover : public CrossoverOperator<type>
{
public:

	/**
	* Function Method.
	* Method to call the class like a function. Takes two parent chromosomes and
	* performs two point crossover on them.
	* @param mother the first parent chromosome
	* @param father the second parent chromosome
	* @return pair of children chromosomes
	*/
	virtual std::pair< Chromosome<type> , Chromosome<type> >
	operator()(const Chromosome<type>& mother, const Chromosome<type>& father );

};


/**
* Uniform Crossover.
* Uniform Crossover functor taking two parent chromosomes.
* This implementation creates a bit mask. It uses the bit mask
* and the inverse bit mask to create two offspring.<br>
* parent1 1010<br>
* parent2 0111<br>
*
* bitmask 0110<br>
*
* offspring1 0011<br>
* offspring2 1110<br>
*/
template<class type>
class UniformCrossover : public CrossoverOperator<type>
{
public:

	/**
	* Function Method.
	* Method to call the class like a function. Upon completion the parameters will have
	* the results of the uniform crossover.
	* @param mother the first parent chromosome
	* @param father the second parent chromosome
	* @return pair of children chromosomes
	*/
	virtual std::pair< Chromosome<type> , Chromosome<type> >
	operator()(const Chromosome<type>& mother, const Chromosome<type>& father );
};


/****************************************************************
* OnePointCrossover operator()
****************************************************************/
template<class type>
std::pair< Chromosome<type> , Chromosome<type> >
OnePointCrossover<type>::operator()(const Chromosome<type>& mother, const Chromosome<type>& father )
{
	int min = static_cast<int>( mother.genes.size() );
	size_t point  =  (size_t)RandomNumber::nextNumber(min);
	std::pair< Chromosome<type> , Chromosome<type> > children;

	children.first = mother;
	children.second = father;

	for( size_t i = 0; i <= point; i++ )
	{
   	children.first.genes[i]  = father.genes[i];
   	children.second.genes[i] = mother.genes[i];
	}

	return children;
}

/****************************************************************
* TwoPointrossover operator()
****************************************************************/
template<class type>
std::pair< Chromosome<type> , Chromosome<type> >
TwoPointCrossover<type>::operator()(const Chromosome<type>& mother, const Chromosome<type>& father )
{
	int min = static_cast<int>( mother.genes.size() );
	size_t point  =  (size_t)RandomNumber::nextNumber(min);
	size_t point2 =  (size_t)RandomNumber::nextNumber(min);
	std::pair< Chromosome<type> , Chromosome<type> > children;

	while( point2 == point ) point2 = RandomNumber::nextNumber(min);
	if( point > point2) std::swap(point,point2);

	children.first = mother;
	children.second = father;

	for( size_t i = point; i <= point2; i++ )
	{
   	children.first.genes[i] = father.genes[i];
   	children.second.genes[i] = mother.genes[i];
	}

	return children;
}


/****************************************************************
* UniformCrossover operator()
****************************************************************/
template<class type>
std::pair< Chromosome<type> , Chromosome<type> >
UniformCrossover<type>::operator()(const Chromosome<type>& mother, const Chromosome<type>& father )
{
	std::vector<bool> mask( mother.genes.size() );
	std::pair< Chromosome<type> , Chromosome<type> > children;

	//Create the mask
	for( size_t i = 0; i < mask.size(); i++ )
	{
		mask[i] = RandomNumber::nextNumber(2) == 1;
	}

	children.first.genes.resize(mother.genes.size());
	children.second.genes.resize(mother.genes.size());

	//loop through the chilrens' genes
	for( size_t i = 0; i < mother.genes.size(); i++ )
	{
		//if the mask is 1 then the first child gets
		//genes from its father and the second child
		//from its mother.
   		if( true == mask[i] )
		{
			children.first.genes[i] = father.genes[i];
			children.second.genes[i] = mother.genes[i];
		}
		//if the mask is 0 then the first child gets
		//genes from its mother and the second child
		//from its father.
		else
		{
			children.first.genes[i] = mother.genes[i];
			children.second.genes[i] = father.genes[i];
		}
	}

	return children;
}


#endif
