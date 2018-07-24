/* 
 * File:   matrix.h
 * Author: hzhang
 * Definition of dense matrix class 
 * and declaration of member functions
 * Created on July 7, 2018, 11:21 AM
 */

#ifndef XMAGMA_MATRIX_H
#define XMAGMA_MATRIX_H

#include "xmagma_forwards.h"
#include "xmagma_util.h"

namespace xmagma {

    template < typename T > class Matrix {     
        typedef Matrix< T > SelfType;
    public: 
        typedef Scalar< T > ValueType;
        typedef magma_int_t size_type;
        // Default constructor. Does not allocate memory
        explicit Matrix(): size1_( 0 ), size2_( 0 ), ld_( 0 ) {}
        
        /*  Construct the matrix with given dimensions on memory
         *  nrow               #of rows
         *  ncol                #of columns
         *  queue             optional queue in which the matrix is created                          
         *  (default argument is the static variable queue)
         */
        explicit Matrix( size_type nrow, size_type ncol,                 
                magma_queue_t queue = Backend::get_queue() );
        
        /* Construct matrix from matrix expression
         * L                    type of left hand side argument 
         * R                    type of right hand side argument
         * O                   type of operator
         */
        template< typename L, typename R, Oper O >
        explicit Matrix( MatrixExpression< const L, const R, O > const& 
            proxy );
        
        /* Deep copy of the matrix */
        Matrix( const SelfType& other );
        ~Matrix() {
            magma_free( elements_ );
        }
        /* Operators whose return value is the reference of the matrix 
         * itself
         */
        // A = B
        SelfType& operator=( const SelfType& other );
        template< typename L, typename R, Oper O>
        SelfType& operator=( const MatrixExpression< const L, const R,
                O >& proxy );
        // A = trans( B )
        SelfType& operator=( const MatrixExpression< const SelfType,
                const SelfType, M_TRANS >& proxy );
        // A = A + B
        template< typename L, typename R, Oper O>
        SelfType& operator+=( const MatrixExpression< const L,
                const R, O> & proxy );
        SelfType& operator+=( const SelfType& other );
        // A = A - B;
        template< typename L, typename R, Oper O >
        SelfType& operator-=( const MatrixExpression< const L,
                const R, O >& proxy );
        SelfType& operator-=( const SelfType& other );
        // A *= a inplace scale a matrix
        SelfType& operator*=( T );
        SelfType& operator/=( T );
        // -A
        MatrixExpression< const SelfType, const T,  M_MULT > 
        operator-() const;
        
        /* Return dimensions of the matrix */
        // #of rows
        size_type size1() const { return size1_; }
        size_type size2() const { return size2_; }
        size_type ld() const { return ld_; }
        /* Return pointer of elements */
        MagmaPtr< T > get_pointer() const { return elements_; }
    private: 
        MagmaPtr< T > elements_;
        size_type size1_; // #of rows
        size_type size2_; // #of columns
        size_type ld_; // leading dimension of matrix, ld_ >= size1_
    };  //Matrix
} //xmagma
#endif /* XMAGMA_MATRIX_H */
