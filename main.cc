#include "ga.h"
#include "fitness.h"
#include "selection.h"
#include "helpers.h"
#include <iostream>
#include <iomanip>
#include <numeric>
#include <iterator>
#include <string>
#include <math.h>
using namespace std;

static size_t NumOfX = 10;
static size_t curFit = 0; 	  //Which X value we are on
vector< IntChromosome > memory;

const double MutationRate = 0.005;
const double CrossoverRate = 0.8;
const size_t PopulationSize = 100;
const size_t ChromosomeLength = 100;


class MyMutation : public MutationOperator<int>
{
public:
  int operator()( int gene )
  {
	return RandomNumber::nextNumber(NumOfX);
  }
};



class MyFitness : public FitnessFunction<int>
{
public:
  virtual double operator()(const Chromosome<int>& chromosome)
  {
	return count( chromosome.genes.begin(), chromosome.genes.end(), static_cast<int>(curFit));
  }

};


MyFitness 					c;
MyMutation 					m;
UniformCrossover< int > 	p;
TournamentSelection<int> 	s( 0.80 );



int rGene( void )
{
  return RandomNumber::nextNumber( 10 );
}

IntChromosome rChromosome( IntChromosome c )
{
   generate(c.genes.begin(),c.genes.end(),rGene);
   return c;
}

int main(int argc, char** argv)
{
  bool useRandomImmigrants = false;
  bool useElite = false;
  bool useMemory = false;

  for( int i = 0; i < argc ; i++ )
  {
   	   if( strcmp("-r", argv[i]) == 0 ) useRandomImmigrants = true;
   	   if( strcmp("-R", argv[i]) == 0 ) useRandomImmigrants = true;
   	   if( strcmp("-e", argv[i]) == 0 ) useElite = true;
  	   if( strcmp("-E", argv[i]) == 0 ) useElite = true;
   	   if( strcmp("-m", argv[i]) == 0 ) useMemory = true;
  	   if( strcmp("-M", argv[i]) == 0 ) useMemory = true;
  	   if( strcmp("-h", argv[i]) == 0 )
  	   {
  	   	 cout<< "usage: main options\n\t-r: use random immigrants\n\t-e: use elitism\n\t-m: use memory\n";
		 return 0;
  	   }
  }

  cerr << "Using: ";
  if( useMemory ) cerr << "Memory ";
  if( useElite  ) cerr << "Elitism ";
  if( useRandomImmigrants ) cerr << "Random Immigrants";
  cerr << endl;

  GeneticAlgorithm<int> T( c, m, p, s );
  T.createPopulation( PopulationSize, ChromosomeLength, rGene );
  IntChromosome elite;
  bool update = false;

  vector< vector<double> > b_fit( 400 * NumOfX );

for( int run = 0; run < 100; run++)
{
  memory.resize(0);
  T.createPopulation( PopulationSize, ChromosomeLength, rGene );
  for ( size_t gen = 1; gen <= 400 * NumOfX; gen++ )
  {
	elite = *max_element( T.population.begin(), T.population.end() );

	if( RandomNumber::nextPercentage() <= 0.15 )
	{
	  if( memory.size() > curFit)
	  	  memory[ curFit ] = *max_element( T.population.begin(), T.population.end() );
	  else
	  	  memory.push_back( *max_element( T.population.begin(), T.population.end() ) );

	  if( curFit == (NumOfX-1) )
		curFit = 0;
	  else
		curFit++;

	  if( useMemory && memory.size() > curFit )
	  {
	  	  elite = memory[ curFit ];
	  	  update =true;
	  }
	}

    T.performSelection();
    T.performCrossover( CrossoverRate );
    T.performMutation( MutationRate );
    T.performFitness();

	if( useRandomImmigrants )
	{
		sort( T.population.begin(), T.population.end() );
		vector< IntChromosome >::iterator itr = T.population.begin();
		for( size_t i = 0;i < PopulationSize *.1; i++)
		  itr++;
		transform< vector< IntChromosome >::iterator >( T.population.begin(), itr , T.population.begin(), rChromosome);
		T.performFitness();
	}

	if( useElite || (useMemory && update))
	{
		T.population[0] = elite;
		T.population[0].fitness = c( T.population[0] );
	}
//	cout << gen << endl;
	b_fit[ gen - 1 ].push_back( ( max_element( T.population.begin(), T.population.end() ) )->fitness );
//    cout << gen << "\t" << accumulate( T.population.begin(), T.population.end(), 0.0 ) / PopulationSize << "\t";
//	cout << ( max_element( T.population.begin(), T.population.end() ) )->fitness << "\n";
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
