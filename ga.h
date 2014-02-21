/****************************************************************
* ga.h
* David B. Bracewell
* 12/14/2004
****************************************************************/

#ifndef GA_H
#define GA_H

#include "chromosome.h"
#include "geneticOperators.h"
#include "randomNumber.h"
#include "fitness.h"
#include "selection.h"
#include <vector>
#include <algorithm>


/**
* Genetic Algorithm class.
* Standard genetic algorithm class. 
*/
template<class gene_type>
class GeneticAlgorithm
{
 public:
  std::vector< Chromosome<gene_type> > population; /**< population of individuals */

  /**
   * Constructor.
   * Only way to create an instance of the Genetic Algorithm class.
   * @param ffunc the fitness function to use
   * @param mOp the mutation operator to use
   * @param cOp the crossover operator to use
   * @param selMethod the selection method to use
   */
  GeneticAlgorithm( FitnessFunction<gene_type>& ffunc,
					MutationOperator<gene_type>& mOp,
					CrossoverOperator<gene_type>& cOp,
					SelectionMethod<gene_type>& selMethod	);


  virtual ~GeneticAlgorithm(){}


  /**
   * Create Population.
   * Creates a population of chromosomes and initializes them with a genrator function.
   * @param nPopSize size of the population
   * @param nChromLength length of a chromosome
   * @param GENERATE_FUNCTION a function that takes no arguments and returns a gene_type
   */
  void createPopulation( size_t nPopSize, size_t nChromLength, gene_type(*GENERATE_FUNCTION)(void) );


  /**
   * Perform Fitness.
   * Performs fitness on the population.
   */
  void performFitness();

  /**
   * Perform Mutation.
   * Performs mutation on the population.
   * @param dMutationRate the probability of a gene mutating
   */
  void performMutation(double dMutationRate);

  /**
   * Perform Crossover.
   * Performs crossover on the population.
   * @param dCrossoverRate the probability of two genes undergoing crossover
   */
  void performCrossover(double dCrossoverRate);

  /**
   * Perform Selection.
   * Performs selection on the population.
   */
  void performSelection();

 protected:
  FitnessFunction<gene_type>& mFitness;
  MutationOperator<gene_type>& mMutation;
  CrossoverOperator<gene_type>& mCrossover;
  SelectionMethod<gene_type>& mSelection;


};


/****************************************************************
* GeneticAlgorithm Constructor
****************************************************************/
template<class gene_type>
GeneticAlgorithm<gene_type>::GeneticAlgorithm( FitnessFunction<gene_type>& ffunc,
											   MutationOperator<gene_type>& mOp,
											   CrossoverOperator<gene_type>& cOp,
											   SelectionMethod<gene_type>& selMethod ):
mFitness(ffunc),
mMutation(mOp),
mCrossover(cOp),
mSelection(selMethod)
{
  RandomNumber::seed();
}


/****************************************************************
* GeneticAlgorithm createPopulation
****************************************************************/
template<class gene_type>
void GeneticAlgorithm<gene_type>::createPopulation( size_t nPopSize, 
													size_t nChromLength, 
													gene_type(*GENERATE_FUNCTION)(void) )
{
  population.resize( nPopSize );
  for( size_t i = 0; i < nPopSize; i++)
  {
    population[i].genes.resize(nChromLength);
    generate( population[i].genes.begin(), population[i].genes.end(), GENERATE_FUNCTION);
  }
  performFitness();
}

/****************************************************************
* GeneticAlgorithm performFitness
****************************************************************/
template<class gene_type>
void GeneticAlgorithm<gene_type>::performFitness()
{
  for( size_t i = 0; i < population.size(); i++ )
  {
	population[i].fitness = mFitness( population[i] );
  }
}


/****************************************************************
* GeneticAlgorithm performSelection
****************************************************************/
template<class gene_type>
void GeneticAlgorithm<gene_type>::performSelection()
{
  std::vector< Chromosome<gene_type> > children( population.size() );
  mSelection( population, children );
  population = children;
}

/****************************************************************
* GeneticAlgorithm performCrossover
****************************************************************/
template<class gene_type>
void GeneticAlgorithm<gene_type>::performCrossover(double dCrossoverRate)
{
  size_t max = population.size() % 2 == 0? population.size() : population.size() - 1;

  for( size_t i = 0; i < max; i+=2 )
  {
	if( i+1 > population.size() ) break;
	if( RandomNumber::nextPercentage() <= dCrossoverRate )
	{
	  std::pair< Chromosome<gene_type>, Chromosome<gene_type> > Children = mCrossover(population[i], population[i+1]);
	  population[i] = Children.first;
	  population[i+1] = Children.second;
	}
  }
}

/****************************************************************
* GeneticAlgorithm performMutation
****************************************************************/
template<class gene_type>
void GeneticAlgorithm<gene_type>::performMutation(double dMutationRate)
{
  for( size_t i = 0; i < population.size(); i++ )
  {
	for( size_t j = 0; j < population[i].genes.size(); j++ )
	{
	  if( RandomNumber::nextPercentage() <= dMutationRate)
	  {
		population[i].genes[j] = mMutation( population[i] );
	  }
	}
  }
}



#endif
