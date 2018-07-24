/* 
 * File:   xmagma_forwards.h
 * Author: hzhang
 * Forward declaration of types, enumeration and functions 
 * Created on July 19, 2018, 11:40 AM
 */

#ifndef XMAGMA_FORWARDS_H
#define XMAGMA_FORWARDS_H

namespace xmagma {
    /* Enumerator of all operations
     * M                               matrix
     * V                                vector
     * S                                scalar
     */
    enum Oper {
        M_ADD,
        M_SUB,
        M_TRANS,
        M_MULT,
        V_OUTER,
        M_SCALE
    };
    class Backend;
    class Queue;
    template< typename L, typename R, Oper O > 
    class MatrixExpression;
    template < typename T > class RVector;
    template < typename T > class RMatrix;
    template< typename L, typename R, Oper O > class MatrixSize;
    template< typename T> class Matrix;
    template < typename T> class ScalarValue;
    template< typename T > using Scalar = 
        typename ScalarValue< T >::type;
    template < typename T> class Buffer;
    template< typename T > using MagmaPtr =
    typename Buffer< T >::type; 
    template< typename T > 
    magma_int_t mem_creator( MagmaPtr< T > *ptr_ptr, magma_int_t n );
    template< typename T > 
    int copy_matrix( Matrix< T >& mat1, 
            const Matrix< T >& mat2 );
    template< typename T > 
    void transfer_matrix( RMatrix< T > const& mat1,
            Matrix< T >& mat2 );
    template< typename T >
    void copy( const RMatrix< T >& cpu, Matrix< T >& gpu );
    
    
} // xmagma

#endif /* XMAGMA_FORWARDS_H */

