#include <iostream>
#include <vector>
using namespace std;



typedef struct
{
  int weight;
  int value;
}ITEM_TYPE;

const int NumOfItems = 20;



ITEM_TYPE items[NumOfItems]={ 
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
{9,60},
{18,44},
{16,2},
{17,53},
{7,75},
{6,22},
{5,42},
{18,60}
};

int knapsack(int Weight);


int main()
{

// 							70,
// 							93,
// 							117,
// 							140,
// 							164,
// 							187,
// 							210

  cout <<  knapsack(24) << endl
	   <<  knapsack(46) << endl
	   <<  knapsack(70) << endl
	   <<  knapsack(93) << endl
	   <<  knapsack(117) << endl
	   <<  knapsack(140) << endl
	   <<  knapsack(164) << endl
	   <<  knapsack(187) << endl
	   <<  knapsack(210) << endl;
}


int knapsack(int Weight)
{
  vector< vector<int> > matrix;

  matrix.resize( NumOfItems );
  for( size_t i = 0; i < NumOfItems; i++ )
  {
	matrix[i].resize( Weight+1 );
	matrix[i][0] = 0;
  }
  
  for( size_t i = items[0].weight; i <= Weight; i++)
	matrix[0][i]= items[0].value;


  for( size_t item = 1; item < NumOfItems; item++)
	for( size_t weight = 1; weight <= Weight; weight++)
	{
	  int v1 = 	matrix[item-1][weight];
	  int v2 = -1;
	  if( items[item].weight <= weight  )
		v2 = matrix[item-1][weight- items[item].weight] + items[item].value;

	  matrix[item][weight]= max(v1,v2);

	}

  return matrix[ NumOfItems-1 ][ Weight ];
}
