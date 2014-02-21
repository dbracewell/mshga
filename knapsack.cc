#include "ga.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <algorithm>
#include <functional>
using namespace std;

const size_t PopulationSize = 500;
const size_t ChromosomeLength = 20;
const size_t NumOfGenerations = 800;
const size_t NumOfRuns = 100;
const double MutationRate = 0.01;
const double CrossoverRate = 0.8;

const int NumberOfSizes = 8;
const int NumberOfItems = ChromosomeLength;

int curSize;

typedef struct
{
  int weight;
  int value;

}ITEM_TYPE;


typedef struct
{
	int size;
	int optimal;

}FIT;


ITEM_TYPE items[NumberOfItems]={ 
{9,60},
{18,44},
{16,2},
{17,53},
{7,75},
{6,22},
{5,42},
{15,85},
{8,51},
{18,56},
{19,62},
{13,34},
{4,43},
{13,62},
{17,77},
{17,11},
{2,23},
{10,69},
{11,5},
{18,60}
 };


FIT ans[NumberOfSizes] = {
{93,587},
{164,821},
{46,363},
{140,743},
{187,884},
{210,923},
{70,474},
{117,671}
/*	{46,363},
	{70,474},
	{93,587},
	{117,671},
	{140,743},
	{164,821},
	{187,884},
	{210,923}*/
};

template< class type >
void print_chromosome( Chromosome< type > c )
{
    std::ostream_iterator< type > it( cout, "" );
    std::copy( c.genes.begin(), c.genes.end(), it );
    std::cout << "\t" << c.fitness << std::endl;
}


bool randomGene(void);
double maxFitness( vector< Chromosome<bool> >& pop );


Chromosome<bool> rChromosome( Chromosome<bool> c )
{
   generate(c.genes.begin(),c.genes.end(),randomGene);
   return c;
}


class KnapsackFitness: public FitnessFunction<bool>
{
public:
  virtual double operator()( const Chromosome<bool>& chromosome )
  {
	int totalWeight = 0;
	int totalValue  = 0;
	for( size_t i = 0; i < ChromosomeLength; i++ )
	{
		totalWeight += ( chromosome.genes[i]==true? items[i].weight : 0);
		totalValue  += ( chromosome.genes[i]==true? items[i].value  : 0);
	}
	
	if( totalWeight > ans[curSize].size )
	  return 0;
	else
	  return totalValue;
  }
};

class KnapsackMutation: public MutationOperator<bool>
{
public:
  virtual bool operator()(bool gene){ return !gene;}

};

KnapsackFitness fitness;
KnapsackMutation  mutation;
UniformCrossover<bool> crossover;
TournamentSelection<bool> selection(0.98);

int main(int argc, char** argv)
{

  bool useRandomImmigrants = false;
  bool useMemory = false;

  for( int i = 0; i < argc ; i++ )
  {
   	   if( strcmp("-r", argv[i]) == 0 ) useRandomImmigrants = true;
   	   if( strcmp("-R", argv[i]) == 0 ) useRandomImmigrants = true;
   	   if( strcmp("-m", argv[i]) == 0 ) useMemory = true;
  	   if( strcmp("-M", argv[i]) == 0 ) useMemory = true;
  	   if( strcmp("-h", argv[i]) == 0 )
  	   {
  	   	 cout<< "usage: main options\n\t-r: use random immigrants\n\t-e: use elitism\n\t-m: use memory\n";
		 return 0;
  	   }
  }



 GeneticAlgorithm<bool> ga( fitness,mutation,crossover,selection );
 vector< vector<double> > b_fit( NumOfGenerations );


 for( size_t run = 1; run <= NumOfRuns; run++)
 {
	 Chromosome<bool>  Memory[NumberOfSizes];
	curSize = 0;
   ga.createPopulation( PopulationSize, ChromosomeLength, randomGene );
	
   for( size_t generation = 1; generation <= NumOfGenerations; generation++ )
   {
	   
	   Chromosome<bool> Elite = *(max_element(ga.population.begin(),ga.population.end()));
	   
	   if( generation % 50 == 0 )
	   //if( RandomNumber::nextPercentage() <= 0.15 )
	   {
		   if( Elite.fitness > Memory[curSize].fitness )
			   Memory[curSize] = Elite;
			curSize++;
			if( curSize >= NumberOfSizes )
				curSize = 0;
 			ga.performFitness();
			
 			Elite.fitness = fitness(Elite);

			if( useMemory )
				Elite = Memory[curSize];
	   }	

		ga.performSelection();
		ga.performCrossover( CrossoverRate );
		ga.performMutation( MutationRate );
		ga.performFitness();
	

		if( useRandomImmigrants )
		{
			sort( ga.population.begin(), ga.population.end() );
			vector< Chromosome<bool> >::iterator itr = ga.population.begin();
			for( size_t i = 0;i < PopulationSize *.1; i++)
			  itr++;
			transform< vector< Chromosome<bool> >::iterator >( ga.population.begin(), itr , ga.population.begin(), rChromosome);
			ga.performFitness();
		}


 		if( Elite.fitness > maxFitness(ga.population) )
 			ga.population[0] = Elite;

	b_fit[ generation - 1 ].push_back(maxFitness(ga.population) / ans[curSize].optimal * 100 );
/*		cout << generation << "\t" << accumulate(ga.population.begin(),ga.population.end(),0.0)/PopulationSize << "\t"
			 << maxFitness(ga.population) << "\t" 
			 << maxFitness(ga.population) / ans[curSize].optimal * 100
			 << endl;
*/
   }

 }

  for( size_t i = 0; i < b_fit.size(); i++ )
  {
  	double mean = accumulate( b_fit[i].begin(), b_fit[i].end(), 0.0 ) / b_fit[i].size();
  	double stdDev = 0.0;
  	for( size_t j = 0; j < b_fit[i].size(); j++ )
  		 stdDev += pow(b_fit[i][j] - mean,2);
	stdDev *= (1.0 / b_fit[i].size() );
	stdDev = sqrt(stdDev);
   	   cout << i+1 << "\t" << mean << "\t" << stdDev << endl;
  }


 return 1;
}


bool randomGene(void)
{
  return RandomNumber::nextBoolean();
}

double maxFitness( vector< Chromosome<bool> >& pop )
{
	return (max_element(pop.begin(),pop.end()))->fitness;
}
