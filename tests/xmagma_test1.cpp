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

magma_int_t m = 3; // length of a
double *a; // a - m- vector on the host
double *d_a; // d_a - m- vector a on the device
// allocate array on the host
magma_dmalloc_cpu ( &a , m ); // host memory for a
// allocate array on the device
magma_dmalloc ( &d_a , m ); // device memory for a
// a={ sin (0) , sin (1) ,... , sin (m -1)}
for(int j=0;j<m;j++) a[j]= sin (( float )j);
// copy data from host to device
magma_dsetvector (m, a, 1, d_a ,1, xmagma::Backend::get_queue() ); // copy a -> d_a
// find the smallest index of the element of d_a with maximum
// absolute value
int i = magma_idamax( m, d_a, 1, xmagma::Backend::get_queue() );
printf ("max |a[i]|: %f\n",fabs (a[i -1]));
printf (" fortran index : %d\n",i);

xmagma::M_SUB;
xmagma::Matrix< double > A( 2, 5 );
xmagma::Matrix< double > C;
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
C = A; 
printf( "matrix C \n" );
magma_dprint_gpu( C.size1(),C.size2(), C.get_pointer(),
            C.ld(), xmagma::Backend::get_queue() );
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
printf( "xMat6\n" );
xmagma::print( xMat6 );
xMat5 += xMat6;
xmagma::print( xMat5 );
//inplace_sub
xMat5 -=xMat6;
xmagma::print( xMat5 );
xMat5 -=xMat5;
xmagma::print( xMat5 );
//scale
xMat6 *=8;
xmagma::print( xMat6 );
xMat6 /=8;
xmagma::print( xMat6 );
xMat6 /=0;
// -A
-xMat6;
// A = 10
xMat6 = 10;
xmagma::print( xMat6 );
//expression( A ) + expression( B )
( xMat6 + xMat6 ) + ( xMat6 + xMat6 );
xMat6 + xMat6 + xMat6 + xMat6;
xMat6 + ( xMat6 + xMat6 );
// expression( A ) - expression( B )
( xMat6 + xMat6 ) - ( xMat6 + xMat6 );
// expression( A ) - B
( xMat6 + xMat6 ) - xMat6;
// A - expression( B )
 xMat6 - ( xMat6 + xMat6 );
 // A - B
 xMat6 - xMat6;
 t( t( xMat6 ) );
 xmagma::print( xMat6 );
 
 xmagma::copy( RMat3, xMat5 );
 xmagma::print( xMat5 );
 xMat6 = xMat6 + ( xMat5 + xMat5 );
 xmagma::print( xMat6 );
 // A = B + t ( C )
 xmagma::Matrix< double > xMat7( 3, 3);
 xMat7 = 7;
 xmagma::print( xMat7 );
 xMat6 = t( xMat5 + xMat7 ) + xMat5;
 xmagma::print( xMat6 );
 xMat6 = ( xMat5 + xMat7 ) + t( xMat5 + xMat7 );
 xmagma::print( xMat6 );

 xMat6 = t( t( xMat5 ) ) ;
 xmagma::print( xMat6 );

 //xMat6 / 0;
 // OpExecutor
 // A -= B
 xMat6 -= xMat7;
 xmagma::print( xMat6 );
 xmagma::print( xMat7 );
  xMat6 -= t( xMat7 );
  xmagma::print( xMat6 );
 // A -= trans( expression( B + C )
   xmagma::print( xMat5 );
  xMat6 -= t( xMat7 + xMat5 );
  xmagma::print( xMat6 );
  xmagma::print( xMat7 );

  xMat6 += xMat7 * 2.0;
  xmagma::print( xMat6 );
   xMat6 += xMat7 / 2.0;
    xmagma::print( xMat6 );
   xMat6 -= xMat7 / 2;
   xmagma::print( xMat6 );
   xMat6 = xMat7 * 2 * 2 ;
   xmagma::print( xMat6 );
   xMat6 = 2 * 4 * xMat7;
   xMat6 = ( xMat7 + xMat6 ) / 2 / 7;
   xmagma::print( xMat6 );
   xMat6 = - ( - xMat7 + xMat6 );
   xmagma::print( xMat6 );
   xMat6 = xMat5;
   print( xMat6 );
   xMat6 += xMat6 * 1;
   print( xMat6 );
   xMat6 += -xMat5;
   print( xMat6 );
   xMat6 += -( xMat5 + xMat7 ) ;
   print( xMat6 );
   xMat6 += - xMat5;
   print( xMat6 );
   xMat7 -= ( - xMat7 ) * 3;
   print( xMat7 );
   xMat7 -= - ( 2 *  xMat7 );
   print( xMat7 );
   xMat7 = 7;
   printf( "xMat7\n" );
   print( xMat7 );
   print( xMat6 );
   xMat6 += ( - xMat7 ) /  2;
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 -= ( - xMat7 ) /  2;
   printf( "xMat6\n" );
   print( xMat6 );
   printf( "xMat5" );
   print( xMat5 );
   xMat6 = (- xMat5 ) + (- xMat6 );
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 = ( 2 * xMat5 ) + (- xMat6 );
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 = ( xMat7 / 2 ) + (- xMat6 );
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 = ( xMat7 / 2 ) + (- xMat6 / 2 );
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 += xMat7 / 5;
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 += ( xMat7 + 2 * xMat6 );
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 += ( xMat7 + xMat6 );
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 += ( xMat7 * 2 + xMat6 );
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 += ( xMat7 / 2 + xMat6 );
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 += ( xMat7 + xMat6 * 2 );
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 += ( xMat7 + xMat6 / 2 );
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 += ( xMat7 * 2 + xMat5 / 2 );
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 -= ( xMat7 * 2 + xMat6 / 2 );
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 -= ( - xMat5 + xMat6 );
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 -= (  xMat5 + xMat7 );
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 -= ( 2 * xMat5 + xMat7 / 2 );
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 = ( 2 * xMat5 - xMat7 / 2 );
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 = ( xMat5 - xMat7 );
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 = ( xMat5 - xMat7 );
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 = ( 2 * xMat5 - xMat7 / 2 );
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 = ( 2 * xMat5 - xMat7 / 2 );
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 += ( 2 * xMat5 - xMat6 );
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 -= ( - xMat5 - xMat6 );
   printf( "xMat6\n" );
   print( xMat6 );
   printf( "xMat5\n" );
   print( xMat5 );
   xMat6 = ( xMat5 * xMat5 );
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 = ( xMat5 * t( xMat6 ) );
   printf( "xMat5\n" );
   print( xMat5 );
   printf( "xMat7\n" );
   print( xMat7 );
   xMat6 = xMat5 * ( xMat7 + xMat5 );
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 = t( xMat5 ) * xMat7;
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 = ( xMat5 + xMat7 ) * xMat5;
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 = t( xMat5 ) * t( xMat5 );
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 = t( xMat5 + xMat5 ) * ( xMat5 + xMat7 );
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 += xMat5 * xMat7;
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 += xMat5 * t( xMat6 );
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 += xMat5 * ( xMat6 + xMat7 );
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 += t( xMat5 ) * xMat7;
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 += t( xMat5 + xMat6 ) * xMat7;
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 += t( xMat5 ) * t( xMat6 );
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 = xMat5;
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 += ( xMat5 - xMat7 ) * ( xMat5 - 10 * xMat7 );
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 -= xMat5 * xMat7;
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 -= xMat5 * t( xMat6 );
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 -= xMat5 * ( xMat6 - 2 * xMat7 );
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 -= t( xMat5 ) * xMat7;
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 -= ( xMat5 - xMat7 ) * xMat7;
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 -= t( xMat5 ) * t( xMat6 );
   printf( "xMat6\n" );
   print( xMat6 );
   xMat6 -= ( xMat5 - 2 * xMat7 ) * t( xMat6 + 3 * xMat7 );
   xMat6 = -( xMat5 + xMat7 );
   printf( "xMat6\n" );
   print( xMat6 );
   /* Vector */
   xmagma::RVector< double > rv1( &a[ 0 ], m );
   std::cout << rv1;
   xmagma::Vector< double, xmagma::COL > xV1( 3 ), xV2( 3 );
   transfer_vector( rv1, xV1 );
   printf( "xV1\n");
   print( xV1 );
   for(int j=0;j<m;j++) a[j]= tan (( float )j) + 1;
   transfer_vector( rv1, xV2 );
   printf( "xV2\n");
   print( xV2 );
   xmagma::Vector< double, xmagma::COL > xV3( xV2 );
   printf( "xV3\n");
   print( xV3 );
   xmagma::Vector< double, xmagma::COL > xV4;
   xV4 = xV3; 
   printf( "xV4\n");
   print( xV4 );

   xmagma::Vector< double, xmagma::ROW > xV5( 3 ), xV6 ( 3 ), xV7( 3 );
   xmagma::copy( rv1, xV5 );
   printf( "xV5\n");
   print( xV5 );
   xMat6 = xMat5;
   printf( "xMat6\n");
   double c[ 3 ] = { 0.561985, -107.274344, 5.306721 };
   xmagma::RVector< double > rv2( &c[ 0 ], 3 );
   transfer_vector( rv2, xV7 );
   transfer_vector( rv2, xV4 );
   print( xMat6 );
   xV4 = xMat6 * xV4;
   printf( "xV4\n");
   print( xV4 );
   xV6 = xV5 * xMat6;
   printf( "xV6\n");
   print( xV6 );
   xV4 = t( xMat6 ) * xV4;
   printf( "xV4\n");
   print( xV4 );
   xV1 = 6;
   printf( "xV1\n");
   print( xV1 );
   xV6 = xV6 * xMat6;
   printf( "xV6\n");
   print( xV6 );
   xV6 += xV5;
   printf( "xV6\n");
   print( xV6 );
   xV6 -= xV7;
   printf( "xV6\n");
   print( xV6 );
   xV6 *= 5;
   printf( "xV6\n");
   print( xV6 );
   xV6 /= 100;
   printf( "xV6\n");
   print( xV6 );
   printf( "xV1\n");
   print( xV1 );
   xV6 + xV5;
   xV6 - xV5;
   xV6 + xV5 - xV5;
   -xV5;
   xV1 * t( xV4 );
   double p;
   v_inner( xV6, xV4, p );
   printf( "inner product:%f\n", p );
   xmagma::Matrix< double > xM8( 3, 3 );
   xM8 = 0;
   v_outer( xV4, xV6, xM8 );
   printf( "xM8\n");
   print( xM8 );
   printf( "%f\n", xV6 * xV4 + 1 - 1);
   xV6 = xV6 + xV5 + 2 * xV7;
   printf( "xV6\n");
   print( xV6 );
   xV6 = xV6 + xV5 + xV7 * 2;
   printf( "xV6\n");
   print( xV6 );
   xV6 = xV5 * 2;
   printf( "xV6\n");
   print( xV6 );
   xV6 = ( xV5 + xV7 ) * 2;
   printf( "xV6\n");
   print( xV6 );
   xV6 = xV7 / 2;
   printf( "xV6\n");
   print( xV6 );
   xV6 = ( xV5 + xV7 ) / 2;
   printf( "xV6\n");
   print( xV6 );
   xV6 = - xV7;
   printf( "xV6\n");
   print( xV6 );
   xV6 = ( xV5 + xV5 + xV7 * 2 );
   printf( "xV6\n");
   print( xV6 );
   printf( "xV5\n");
   print( xV5 );
   printf( "xV4\n");
   print( xV4 );
//   copy_vector( xV4, xV6 );
   xV6 = t( xV4 );
   printf( "xV6\n");
   print( xV6 );
   xV6 = ( xV5 + t( xV4 ) );
   printf( "xV6\n");
   print( xV6 );
   xV6 = xV5 + ( - ( xV5 + xV6 ) );
   printf( "xV6\n");
   print( xV6 );
   xV6 = xV5 * 2 + ( - ( xV5 + xV6 ) );
   printf( "xV6\n");
   print( xV6 );
   xV6 = xV5 / 2 - ( - (  3 * xV5 + xV6 + t( xV4 ) ) );
   printf( "xV6\n");
   print( xV6 );
   xV6 = xV5 * xMat6 + xV5;
   printf( "xV6\n");
   print( xV6 );
   double a2 = xV5 * xMat6 * xV4;
   double a3 = xV5 * xMat6 * t( xV5 );
   printf( "a3: %f\n", a3 );
   a3 = xV5 * xMat6 * ( t( xV5 ) + xV4 );
   printf( "a3: %f\n", a3 );
   double d[ 3 ] = { 1, 3, -2 };
   xmagma::RVector< double > rv3( &d[ 0 ], 3 );
   transfer_vector( rv3, xV3 );
   rv3[ 0 ] = 2;
   rv3[ 1 ] = 3;
   rv3[ 2 ] = 5;
   transfer_vector( rv3, xV4 );
   rv3[ 0 ] = 7;
   rv3[ 1 ] = 13;
   rv3[ 2 ] = 11;
   transfer_vector( rv3, xV5 );
   rv3[ 0 ] = 17;
   rv3[ 1 ] = 19;
   rv3[ 2 ] = 23;
   transfer_vector( rv3, xV6 );
           
   a3 = t( 2 * xV4 - xV3 / 2 ) * t( 2 * xV5 * 2 / 2 + xV6 * 2 );
   printf( "a3: %f\n", a3 );
   xV3 = xMat6 * xV4;
   printf( "xV3\n");
   print( xV3 );
   xV7 = xV6 * xMat6 + xV7;
   printf( "xV7\n");
   print( xV7 );
   xV3 = t( xMat6 ) * xV4 + xV3;
   printf( "xV3\n");
   print( xV3 );
   xV7 = xV6 * t( xMat6 ) + xV6;
   printf( "xV7\n");
   print( xV7 );
   xV3 = ( xMat6 * 2 ) * xV4;
   printf( "xV3\n");
   print( xV3 );
   xV7 = xV6 * ( xMat6 / 2 ) + xV6 / 2;
   printf( "xV7\n");
   print( xV7 );
   xV3 = xMat6 * ( xV4 + xV3 );
   printf( "xV3\n");
   print( xV3 );
   xV7 = ( xV6 - xV7 ) * xMat6;
   printf( "xV7\n");
   print( xV7 );
   xV3 = t( xMat6 * 2 ) * xV4;
   printf( "xV3\n");
   print( xV3 );
   xV7 = xV7 * t( xMat6 + xMat5 );
   printf( "xV7\n");
   print( xV7 );
   xV3 = t( xMat6 ) * ( xV4 + xV3 );
   printf( "xV3\n");
   print( xV3 );
   xV7 = ( xV7 / 2 ) * t( xMat6 );
   printf( "xV7\n");
   print( xV7 );
   xV3 = xV4 + ( xMat6 + xMat5 ) * ( xV4 + xV3 );
   printf( "xV3\n");
   print( xV3 );
   xV7 = ( xV7 / 2 ) * ( xMat6 * 2 );
   printf( "xV7\n");
   print( xV7 );
   xV3 = t( xMat6 + xMat5 ) * ( xV4 / 2 );
   printf( "xV3\n");
   print( xV3 );
   xV7 = ( xV7 / 2 ) * t( xMat6 * 2 );
   printf( "xV7\n");
   print( xV7 );
   xV7 += ( xV6 / 2 ) * t( xMat6 * 2 ) * 10000;
   printf( "xV7\n");
   print( xV7 );
   xV7 -= ( xV6 / 2 ) * t( xMat6 * 2 ) * 100000;
   printf( "xV7\n");
   print( xV7 );
   xMat6 = xV3 * t( xV3 );
   printf( "xMat6\n");
   print( xMat6 );
   xMat6 = xV3 * t( xV3 ) * 3;
   printf( "xMat6\n");
   print( xMat6 );
   xMat6 = 3 * ( xV3 * t( xV3 ) );
   printf( "xMat6\n");
   print( xMat6 );
   xMat6 += xV3 * t( xV3 );
   printf( "xMat6\n");
   print( xMat6 );
   xMat6 += 3 * ( xV3 * t( xV3 ) ) ;
   printf( "xMat6\n");
   print( xMat6 );
   xMat6 -= ( xV3 * t( xV3 ) );
   printf( "xMat6\n");
   print( xMat6 );
   xMat6 = xV3 * xV5 ;
   printf( "xMat6\n");
   print( xMat6 );
   xMat6 = 2 * ( xV3 * xV5 );
   printf( "xMat6\n");
   print( xMat6 );
   xMat6 += ( xV3 * xV5 );
   printf( "xMat6\n");
   print( xMat6 );
   xMat6 -= ( xV3 * xV5 ) * 2;
   printf( "xMat6\n");
   print( xMat6 );
   xMat6 += ( t( xV5 ) * xV5 );
   printf( "xMat6\n");
   print( xMat6 );
   xMat6 += xV3 * ( xV5 + xV6 ) ;
   printf( "xMat6\n");
   print( xMat6 );
   xMat6 += xV3 * 2 * ( xV5 + xV6 );
   printf( "xMat6\n");
   print( xMat6 );
   xMat6 -=  xMat5 + ( xV3 + xV4 ) * 2 * ( xV5 + xV6 ) + xMat5;
   printf( "xMat6\n");
   print( xMat6 );
   inv( xMat6 );
   printf( "xMat6\n");
   print( xMat6 );
   xMat6 = solve( xMat6 );
   printf( "xMat6\n");
   print( xMat6 );
   xMat5 = solve( xMat6 );
   printf( "xMat5\n");
   print( xMat5 );
   xmagma::Matrix< double > xMat11;
   xMat11 = solve( xMat6 );
   printf( "xMat11\n");
   print( xMat11 );
   xMat6 = solve( xMat11 * 2 );
   printf( "xMat6\n");
   print( xMat6 );
   xMat6 += solve( xMat11 );
   printf( "xMat6\n");
   print( xMat6 );
   xMat6 += solve( xMat11 / 2 );
   printf( "xMat6\n");
   print( xMat6 );
   xMat6 -= solve( xMat11 );
   printf( "xMat6\n");
   print( xMat6 );
   xMat6 -= solve( xMat11 / 2 );
   printf( "xMat6\n");
   print( xMat6 );
   printf( "det( xMat6 ) = %f\n", det( xMat6 ) );
   printf( "det( xMat6 ) = %f\n", det( xMat6 / 2 ) );
   printf( "det( xMat6 ) = %f\n", det( xMat6 / 2 - xMat5 ) );
   printf( "det( xMat5 ) = %f\n", det( xMat5 ) );
   
   double array11 [ ] = { 1, 7, 3, 3, 4, 6, 0, 5, 3, 2, 14, 15, 0, 6, 0, 16 };
   xmagma::RMatrix< double > RMat11( &array11[ 0 ], 4, 4 );
   xmagma::Matrix< double > xMat12( 4, 4 );

   xmagma::copy( RMat11, xMat12 );
   printf( "det( xMat12 ) = %f\n\n\n\n\n\n\n", det( xMat12 ) );
   
   
   double array13 [ ] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 };
   double array14 [ ] = { 0, 0, 0, 0, 0,  1.0 / 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.0 / 4 };
   xmagma::RMatrix< double > RMat13( &array13[ 0 ], 4, 4 );
   xmagma::RMatrix< double > RMat14( &array14[ 0 ], 4, 4 );
   xmagma::Matrix< double > LOVE( 4, 4 ), XUN( 4, 4 ), FOREVER( 4, 4 );
   copy( RMat13, LOVE );
   copy( RMat14, XUN );
   FOREVER = solve( LOVE + XUN );
   printf( "solve( LOVE + XUN ) = \n" );
   print( FOREVER );
   xmagma::RMatrix< float > rmat924( 4, 4 );
   xmagma::RVector< float > rv924( 3 );
   host_copy( rv3, rv924 );
   host_copy( RMat11, rmat924 );
   std::cout << rv924 << std::endl;
   std::cout << rv3 << std::endl;
   std::cout << rmat924 << std::endl;
   std::cout << RMat11 << std::endl;


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

