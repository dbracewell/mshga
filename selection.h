/****************************************************
 * selection.h
 * David B. Bracewell
 * 12/18/2004
 ****************************************************/
#ifndef SELECTION_H
#define SELECTION_H

#include "chromosome.h"
#include <numeric>


/**
* Abstract Selection Method.
* Abstract base selection method class. All selection methods
* should be derived from this.
*/
template<class type>
class SelectionMethod
{
  public:
    typedef std::vector< Chromosome<type> >& first_argument_type;
    typedef std::vector< Chromosome<type> >& second_argument_type;

	/**
	* Function operator.
	* Function operator to make selection method a functor object.
	* @param parents a vector of Chromosome<type>, source population
	* @param children a vector of Chromosome<type>, destination population
	*/
    virtual void operator()( first_argument_type parents, second_argument_type children)=0;
};



/**
* Tournament Selection.
* A default tournament selection method with tournament size of 2.
* Tournament selection works by choosing 2 individuals and given
* a percentage (Selection Pressure) the more fit one is chosen to
* go to the next generation. This implementation assumes a larger 
* number fitness is better.
*/
template<class type>
class TournamentSelection : public SelectionMethod< type >
{
public:
  /**
   * Constructor.
   * The only constructor.
   * @param dSelectionPressure the percentage of time the more fit individual is chosen
   */
  TournamentSelection( double dSelectionPressure ):mSelectionPressure(dSelectionPressure){;}

  /**
   * Function operator.
   * Function operator to call Tournament selection.
   * @param parents a vector of Chromosome<type>, source population
   * @param children a vector of Chromosome<type>, destination population
   */
  virtual void operator()( std::vector< Chromosome<type> >& parents, 
						   std::vector< Chromosome<type> >& children);
  
protected:
	double mSelectionPressure   ;
};


/**
* Roulette Wheel  Selection.
* A default roulette wheel selection method.
* Roulette wheel or proportional selection assigns each individual
* a probability on being selected based on their fitness. This 
* implementation assumes a larger number fitness is better.
*/
template<class type>
class RouletteWheelSelection : public SelectionMethod< type >
{
public:
  /**
   * Function operator.
   * Function operator to call Roulette wheel selection.
   * @param parents a vector of Chromosome<type>, source population
   * @param children a vector of Chromosome<type>, destination population
   */
  virtual void operator()( std::vector< Chromosome<type> >& parents, 
						   std::vector< Chromosome<type> >& children);
};



/****************************************************************
* TournamentSelection operator()
****************************************************************/
template<class type>
void TournamentSelection<type>::operator()(  std::vector< Chromosome<type> >& parents, 
										   std::vector< Chromosome<type> >& children)
{
  for ( size_t i = 0; i < children.size(); i++ )
  {
	Chromosome<type> c1 = parents[RandomNumber::nextNumber( parents.size() )];
   	Chromosome<type> c2 = parents[RandomNumber::nextNumber( parents.size() )];
	if ( RandomNumber::nextPercentage() <= mSelectionPressure )
   	{
	  children[i] = ( c1.fitness > c2.fitness ) ? c1 : c2;
	}
	else
   	{
   	  children[i] = ( c1.fitness > c2.fitness ) ? c2 : c1;
   	}
  }
}


/****************************************************************
* RouletteWheelSelection operator()
****************************************************************/
template<class type>
void RouletteWheelSelection<type>::operator()( std::vector< Chromosome<type> >& parents, 
						   std::vector< Chromosome<type> >& children)
{
  double sum = std::accumulate( parents.begin(), parents.end(), 0.0 );
  std::vector< double > wheel( parents.size() );
  double previous = 0.0;

  for( size_t i = 0; i < parents.size(); i++ )
  {
	wheel[i] = previous + (parents[i].fitness / sum);
	previous = wheel[i];
  }

  for ( size_t i = 0; i < children.size(); i++ )
  {
	double percent = RandomNumber::nextPercentage();
	size_t item;

	for( item = 0; (item < wheel.size());  item++ )
		if( percent <= wheel[item] ) break;

	children[i] = parents[item];				
  }

}


#endif
