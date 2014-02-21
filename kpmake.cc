#include <iostream>
#include "RandomNumber.h"
using namespace std;



int main()
{
  RandomNumber::seed();
  int totalWeight=0;

  for( int i = 0; i < 20; i++ )
  {
	int weight = RandomNumber::nextNumber(2,20);
	totalWeight += weight;
	cout << "{" <<  weight <<"," << RandomNumber::nextNumber(2,100) << "},\n";
  }


  cout << endl << totalWeight << endl;
  return 1;
}
