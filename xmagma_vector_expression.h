/* 
 * File:   xmagma_vector_expression.h
 * Author: hzhang
 * ***************************************************************************
 * Expression template for vector computations which results in a vector
 * L                            type of left hand side operant
 * R                            type of right hand side operant
 * O                           enumeration of operations
 * ***************************************************************************
 * Created on September 9, 2018, 2:30 PM
 */

#ifndef XMAGMA_VECTOR_EXPRESSION_H
#define XMAGMA_VECTOR_EXPRESSION_H


#ifdef HAVE_CUBLAS
#include "cublas_v2.h"    
#include "magma_v2.h"
#else 
#include "magma.h" // for clmagma
#endif

#include "magma_lapack.h" 
#include "xmagma_tools.h"
#include "xmagma_matrix.h"
#include "xmagma_vector.h"
#include "xmagma_forwards.h"
#include "xmagma_op_executor.h"
#include "xmagma_operations.h"

namespace xmagma {
    template< typename L, typename R, Oper O, typename M > // M for Major
    class VectorExpression {
        typedef VectorExpression< const L,  const R, O, M > SelfType;
    public: 
        typedef magma_int_t size_type;
        // Constructor (no default constructor for vector expression}
        VectorExpression( L& lhs, R& rhs ): lhs_( lhs ), rhs_( rhs ) {}
        // - expression( A )
        VectorExpression< const SelfType, const SelfType,  M_NEGATIVE, M > 
        operator-() const {
            return VectorExpression< const SelfType, 
                const SelfType, M_NEGATIVE, M >
                ( *this, *this );
        }
        // Get operants
        L& lhs() const { return lhs_ ; }
        R& rhs() const{ return rhs_ ; }
        
        // Return length of resulting vector
        magma_int_t size1() const { return VectorSize< L, R, O >::size( 
                lhs_, rhs_ ) ; }
        magma_int_t size2() const { return 1; }
    private: 
        L& lhs_;
        R& rhs_;
    };
    /* Member function of vector
     * len: length of vector
     * queue: #optional queue where it lives
     */
    // Constructor
    template< typename T, typename M > Vector< T, M >::Vector( size_type len, 
            magma_queue_t queue ): 
            size1_( len ), size2_( 1 ) {
        if ( size1_> 0 ) {
            mem_creator< T >( &elements_, size1_ );
        }
    }
    // Construct a vector from vector expression
    template< typename T, typename M > 
    template< typename L, typename R, Oper O >
    Vector< T, M >::Vector(const 
        VectorExpression< const L, const R, O, M >& proxy ):
        size1_( proxy.size1() ), size2_( 1 ) {
        if ( size1_ > 0 ) {
            mem_creator< T >( &elements_, size1_ );
            SelfType::operator=( proxy );
        }
    }
    // Construct from another vector
    template< typename T, typename M >
    Vector< T, M >::Vector( const SelfType& other ) :
    size1_( other.size1() ), size2_( 1 ) {
        if ( size1_ > 0 ) {
            mem_creator< T >( &elements_, size1_ );
            SelfType::operator=( other );
        }
    }
    /* vector operations */
    // v1 = v2
    template< typename T, typename M >
    Vector< T, M > & Vector< T, M >::operator=( const SelfType& other ) {
        if( &other == this ){
            return *this;
        }
        if ( other.size1() == 0 ) {
            return *this;
        }
        // initialize a new vector if lhs is empty matrix
        if (  size1_  == 0 ) {
            size1_ = other.size1();
            size2_ = 1;
            mem_creator< T >( &elements_, size1_ );
            copy_vector< T >( other, *this );
            return *this;
        }
        if ( other.size1() == size1_ ) {
            copy_vector< T >( other, *this );
        } else {
            printf( "dimension doesn't match \n" );
        }
        return *this;
    }
    // v1 = expression( v2 )
    template< typename T, typename M >
    template< typename L, typename R, Oper O >
    Vector< T, M >& Vector< T, M >::operator=( const VectorExpression<
        const L, const R, O, M >& proxy ) {
        assert( ( proxy.size1() == size1() || size1() == 0 )
                && ( proxy.size2() == size2() || size2() == 0 )
                && bool( "dimension doesn't match!" ) );
        if ( size1() == 0 ) {
            size1_ = proxy.size1();
            size2_ = proxy.size2();
            mem_creator< T >( &elements_, size1_ );
        }
        OpExecutor< SelfType, V_ASSIGN, VectorExpression< const L, const R,
                O, M > >::apply( *this, proxy );
        return *this;
    }
    
}

#endif /* XMAGMA_VECTOR_EXPRESSION_H */

