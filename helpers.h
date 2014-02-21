
#ifndef HELPERS_H
#define HELEPRS_H

#include "chromosome.h"
#include <ostream>

template< class type >
void print_chromosome( Chromosome< type > c )
{
    std::ostream_iterator< type > it( cout, "" );
    std::copy( c.genes.begin(), c.genes.end(), it );
    std::cout << "\t" << c.fitness << std::endl;
}

#endif
