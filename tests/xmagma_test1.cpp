/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   newsimpletest.cpp
 * Author: hzhang
 *
 * Created on July 19, 2018, 12:21 PM
 */

#include <stdlib.h>
#include <iostream>
#include "xmagma.h"
/*
 * Simple C++ Test Suite
 */

void test1() {

magma_int_t m = 1024 ; // length of a
float *a; // a - m- vector on the host
float *d_a; // d_a - m- vector a on the device
// allocate array on the host
magma_smalloc_cpu ( &a , m ); // host memory for a
// allocate array on the device
magma_smalloc ( &d_a , m ); // device memory for a
// a={ sin (0) , sin (1) ,... , sin (m -1)}
for(int j=0;j<m;j++) a[j]= sin (( float )j);
xmagma::M_SUB;
xmagma::Matrix< double > A( 2000, 2000 );
xmagma::Matrix< double > B( 10, 10 );
A = B;
double array [ ] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
xmagma::RMatrix< double > RMat1( &array[ 0 ], 2, 5 );
xmagma::Matrix< double > xMat1( 2, 5 );
xmagma::copy( RMat1, xMat1 );

magma_dprint_gpu( xMat1.size1(), xMat1.size2(), xMat1.get_pointer(),
            xMat1.ld(), xmagma::Backend::get_queue() );

A = xMat1;
magma_dprint_gpu( A.size1(),A.size2(), A.get_pointer(),
            A.ld(), xmagma::Backend::get_queue() );

xmagma::Matrix< double > xMat2( xMat1 ); 
magma_dprint_gpu( xMat2.size1(),xMat2.size2(), xMat2.get_pointer(),
           xMat2.ld(), xmagma::Backend::get_queue() );

double array2 [ ] = { 12, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
xmagma::RMatrix< double > RMat2( &array2[ 0 ], 2, 5 );
std::cout << RMat2 << std::endl;
// transfer
xmagma::copy( xMat2, RMat2 );
std::cout << RMat2 << std::endl;
xmagma::RVector< double > rvec1( &array2[ 0 ], 10 );
std::cout << rvec1 << std::endl;
// transpose
xmagma::Matrix< double > xMat3;
xMat3 = xmagma::t( xMat2 );
magma_dprint_gpu( xMat2.size1(),xMat2.size2(), xMat2.get_pointer(),
           xMat2.ld(), xmagma::Backend::get_queue() );

magma_dprint_gpu( xMat3.size1(),xMat3.size2(), xMat3.get_pointer(),
           xMat3.ld(), xmagma::Backend::get_queue() );

xmagma::Matrix< double > xMat4( 5, 2 );
xMat4 = xmagma::t( xMat2 );
magma_dprint_gpu( xMat4.size1(),xMat4.size2(), xMat4.get_pointer(),
           xMat4.ld(), xmagma::Backend::get_queue() );

double array3 [ ] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
xmagma::RMatrix< double > RMat3( &array[ 0 ], 3, 3 );
xmagma::Matrix< double > xMat5( 3, 3 );
array[ 7 ] = 100;
xmagma::RMatrix< double > RMat4( &array[ 0 ], 3, 3 );
xmagma::Matrix< double > xMat6( 3, 3 );
xmagma::copy( RMat4, xMat6 );
xmagma::copy( RMat3, xMat5 );
magma_dprint_gpu( xMat5.size1(),xMat5.size2(), xMat5.get_pointer(),
           xMat5.ld(), xmagma::Backend::get_queue() );
// inplace add
xMat5 = xmagma::t( xMat5 );
magma_dprint_gpu(xMat5.size1(), xMat5.size2(), xMat5.get_pointer(),
            xMat5.ld(), xmagma::Backend::get_queue());
xmagma::print( xMat5 );
xMat5 += xMat5;
xmagma::print( xMat5 );
xmagma::print( xMat6 );
xMat5 += xMat6;
xmagma::print( xMat5 );
// copy data from host to device
magma_ssetvector (m, a, 1, d_a ,1, xmagma::Backend::get_queue() ); // copy a -> d_a
// find the smallest index of the element of d_a with maximum
// absolute value
int i = magma_isamax( m, d_a, 1, xmagma::Backend::get_queue() );
printf ("max |a[i]|: %f\n",fabs (a[i -1]));
printf (" fortran index : %d\n",i);
magma_free_cpu (a); // free host memory
magma_free (d_a ); // free device memory

}

void test2() {
    std::cout << "newsimpletest test 2" << std::endl;
    std::cout << "%TEST_FAILED% time=0 testname=test2 (newsimpletest) message=error message sample" << std::endl;
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% newsimpletest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test1 (newsimpletest)" << std::endl;
    test1();
    std::cout << "%TEST_FINISHED% time=0 test1 (newsimpletest)" << std::endl;

//    std::cout << "%TEST_STARTED% test2 (newsimpletest)\n" << std::endl;
//    test2();
//    std::cout << "%TEST_FINISHED% time=0 test2 (newsimpletest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

