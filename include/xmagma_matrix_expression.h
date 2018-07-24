/* 
 * File:   xmagma_matrix_expression.h
 * Author: hzhang
 * ***************************************************************************
 * Expression template for matrix computations which results in a matrix
 * L                            type of left hand side operant
 * R                            type of right hand side operant
 * O                           enumeration of operations
 * ***************************************************************************
 * Created on July 21, 2018, 8:21 PM
 */

#ifndef XMAGMA_MATRIX_EXPRESSION_H
#define XMAGMA_MATRIX_EXPRESSION_H

#ifdef HAVE_CUBLAS
#include "cublas_v2.h"    
#include "magma_v2.h"
#else 
#include "magma.h" // for clmagma
#endif

#include "magma_lapack.h" 
#include "xmagma_tools.h"
#include "xmagma_matrix.h"
#include "xmagma_forwards.h"

namespace xmagma {
    template< typename L, typename R, Oper O >
    class MatrixExpression {
    public: 
        typedef magma_int_t size_type;
        // Constructor (no default constructor for matrix expression}
        MatrixExpression( L& lhs, R& rhs ): lhs_( lhs ), rhs_( rhs ) {}
        
        // Get operants
        L& lhs() const { return lhs_ ; }
        R& rhs() const{ return rhs_ ; }
        
        // Return dimensions of the resulting matrix
        magma_int_t size1() const { return MatrixSize< L, R, O >::size1( 
                lhs_, rhs_ ) ; }
        magma_int_t size2() const { return MatrixSize< L, R, O >::size2( 
                lhs_, rhs_ ) ; }
    private: 
        L& lhs_;
        R& rhs_;
    };
    
    /* Member function of Matrix
     * nrow: #of rows of the matrix
     * ncol: #of columns of the matrix
     * queue: #optional queue where it lives
     */
    // Constructor
    template< typename T > Matrix< T >::Matrix( size_type nrow, 
            size_type ncol, magma_queue_t queue ): 
            size1_( nrow ), size2_( ncol ), ld_( magma_roundup( nrow, 32 ) ) {
        if ( size1_> 0 && size2_ > 0 ) {
            mem_creator< T >( &elements_, ld_* size2_ );
        }
    } 
    
    // Construct a matrix from matrix expression
    template< typename T > 
    template< typename L, typename R, Oper O >
    Matrix< T >::Matrix(const 
        MatrixExpression< const L, const R, O >& proxy ):
        size1_( proxy.size1() ), size2_( proxy.size2() ), 
        ld_( magma_roundup( proxy.size1(), 32 ) ) {
        if ( size1_ > 0 && size2_ > 0 ) {
            mem_creator< T >( &elements_, ld_ * size2_ );
            SelfType::operator=( proxy );
        }
    }
    
    // Construct from another matrix
    template< typename T >
    Matrix< T >::Matrix( const SelfType& other ) :
    size1_( other.size1() ), size2_( other.size2() ), 
    ld_( magma_roundup( other.size1(), 32 ) ) {
        if ( size1_ > 0 && size2_ > 0 ) {
            mem_creator< T >( &elements_, ld_ * size2_ );
            SelfType::operator=( other );
        }
    }
    
    /* matrix operations */
    // A = B
    template< typename T >
    Matrix< T > & Matrix< T >::operator=( const SelfType& other ) {
        if( &other == this ){
            return *this;
        }
        if ( other.size1() == 0 || other.size2() == 0 ) {
            return *this;
        }
        // initialize a new matrix of dimension doesn't match
        if(  other.size1() != this->size1_ || other.size2() != this->size2_ ){
            magma_free( this->elements_ );
            size1_ = other.size1();
            size2_ = other.size2();
            ld_ = other.ld();
            mem_creator< T >( &elements_, ld_ * size2_ );
            
        }
        copy_matrix< T >( other, *this );
        return *this;
    }
    // A = expression( B )
    
} //xmagma


#endif /* XMAGMA_MATRIX_EXPRESSION_H */

