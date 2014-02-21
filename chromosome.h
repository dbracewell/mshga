/**
* chromosome.h
* @author David B. Bracewell
* @date 12/14/2004
*/
#ifndef GENE_H
#define GENE_H

#include <functional>
#include <vector>
#include <ostream>

/**
* Chromosome class.
* Implements a basic templated chromosome class
*/
template<class gene_type>
class Chromosome
{
public:
	/**
	* Default Constructor.
	*/
	Chromosome():fitness(0.0){}	

	/**
	* Const Copy Constructor.
	* Const Copy Constructor
	* @param rhs chromosome to copy
	*/
	Chromosome(const Chromosome<gene_type>& rhs);


	std::vector< gene_type > genes; /**< vector of gene_type that is the actual encoding */
	double fitness; /**< fitness of the chromosome */


	/**
	* Copy Operator.
	* Copies fitness and genes of another chromosome to this one
	* @param rhs reference to the chromosome to copy from
	*/
	Chromosome<gene_type>& operator=(const Chromosome<gene_type>& rhs);


	/**
	* Greater Than Operator.
	* Checks if this chromosome's fitness is greater than anothers
	* @param rhs reference to a chromosome to compare to
	* @return bool result of the comparison
	*/
	bool operator>(Chromosome<gene_type>& rhs) const;

	/**
	* less Than Operator.
	* Checks if this chromosome's fitness is less than anothers
	* @param rhs reference to a chromosome to compare to
	* @return bool result of the comparison
	*/
	bool operator<(Chromosome<gene_type>& rhs) const;

	/**
	* Equal to Operator.
	* Checks if this chromosome's fitness is equal to anothers
	* @param rhs reference to a chromosome to compare to
	* @return bool result of the comparison
	*/
	bool operator==(Chromosome<gene_type>& rhs)const;

	/**
	* Greater Than Equal to Operator.
	* Checks if this chromosome's fitness is greater than or equal to anothers
	* @param rhs reference to a chromosome to compare to
	* @return bool result of the comparison
	*/
	bool operator>=(Chromosome<gene_type>& rhs)const;

	/**
	* LessThan Equal to Operator.
	* Checks if this chromosome's fitness is less than or equal to anothers
	* @param rhs reference to a chromosome to compare to
	* @return bool result of the comparison
	*/
	bool operator<=(Chromosome<gene_type>& rhs)const;

	/**
	* double cast
	* Casts the chromosome as a double returning the fitness
	*/
	operator double() const
	{
		return fitness;
	}

};


typedef Chromosome<int> IntChromosome;		/**< Predefined Integer Chromosome */
typedef Chromosome<bool> BoolChromosome;	/**< Predefined Boolean Chromosome */
typedef Chromosome<char> CharChromosome;	/**< Predefined Character Chromosome */

/****************************************************************
* Chromosome Copy  Constructor
****************************************************************/
template<class gene_type>
Chromosome<gene_type>::Chromosome(const Chromosome<gene_type>& rhs)
{
  genes = rhs.genes;
  fitness = rhs.fitness;
}


/****************************************************************
* Chromosome operator=
****************************************************************/
template<class gene_type>
Chromosome<gene_type>&  Chromosome<gene_type>::operator=(const Chromosome<gene_type>& rhs)
{
  genes = rhs.genes;
  fitness = rhs.fitness;
  return (*this);
}

/****************************************************************
* Chromosome operator<
****************************************************************/
template<class gene_type>
bool Chromosome<gene_type>::operator<(Chromosome<gene_type>& rhs) const
{
  return fitness < rhs.fitness; 
}

/****************************************************************
* Chromosome operator>
****************************************************************/
template<class gene_type>
bool Chromosome<gene_type>::operator>(Chromosome<gene_type>& rhs) const
{
  return fitness > rhs.fitness; 
}

/****************************************************************
* Chromosome operator==
****************************************************************/
template<class gene_type>
bool Chromosome<gene_type>::operator==(Chromosome<gene_type>& rhs) const
{
  return ( (fitness == rhs.fitness) && (genes == rhs.genes) ); 
}

/****************************************************************
* Chromosome operator<=
****************************************************************/
template<class gene_type>
bool Chromosome<gene_type>::operator<=(Chromosome<gene_type>& rhs) const
{
  return (fitness < rhs.fitness) || ( *this == rhs); 
}

/****************************************************************
* Chromosome operator>=
****************************************************************/
template<class gene_type>
bool Chromosome<gene_type>::operator>=(Chromosome<gene_type>& rhs) const
{
  return (fitness > rhs.fitness) || ( *this == rhs); 
}

#endif
