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
#include "xmagma_op_executor.h"
#include "xmagma_operations.h"
namespace xmagma {
    template< typename T, typename L, typename R, Oper O >
    class MatrixExpression {
        typedef MatrixExpression< const T, const L,  const R, O > SelfType;
    public: 
        typedef magma_int_t size_type;
        // Constructor (no default constructor for matrix expression}
        MatrixExpression( L& lhs, R& rhs ): lhs_( lhs ), rhs_( rhs ) {}
        // - expression( A )
        MatrixExpression< const T, const SelfType, const SelfType,  M_NEGATIVE > 
        operator-() const {
            return MatrixExpression< const T, const SelfType, 
                const SelfType, M_NEGATIVE >
                ( *this, *this );
        }
        // Get operants
        L& lhs() const { return lhs_ ; }
        R& rhs() const{ return rhs_ ; }
        
        // Return dimensions of the resulting matrix
        magma_int_t size1() const { return MatrixSize< const L, const R, O >::size1( 
                lhs_, rhs_ ) ; }
        magma_int_t size2() const { return MatrixSize< const L, const R, O >::size2( 
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
        MatrixExpression< const T, const L, const R, O >& proxy ):
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
        // initialize a new matrix if rhs is empty matrix
        if (  size1_  == 0 || size2_ == 0 ) {
            size1_ = other.size1();
            size2_ = other.size2();
            ld_ = other.ld();
            mem_creator< T >( &elements_, ld_ * size2_ );
            copy_matrix< T >( other, *this );
            return *this;
        }
        if ( other.size1() == size1_ && other.size2() == size2_ ) {
            copy_matrix< T >( other, *this );
        } else {
            printf( "dimension doesn't match \n" );
        }
        return *this;
    }
    // mat_A = mat_expression( B )
    template< typename T >
    template< typename L, typename R, Oper O >
    Matrix< T >& Matrix< T >::operator=( const MatrixExpression< const T,
        const L, const R, O >& proxy ) {
        assert( ( proxy.size1() == size1() || size1() == 0 )
                && ( proxy.size2() == size2() || size2() == 0 )
                && bool( "dimension doesn't match!" ) );
        if ( size1() == 0 || size2() == 0 ) {
            size1_ = proxy.size1();
            size2_ = proxy.size2();
            ld_ = magma_roundup( proxy.size1(), 32 );
            mem_creator< T >( &elements_, ld_ * size2_ );
        }
        OpExecutor< SelfType, M_ASSIGN, MatrixExpression< const T, const L, const R,
                O > >::apply( *this, proxy );
        return *this;
    }
    // A = t( B )
    template< typename T >
    Matrix< T >& Matrix< T >::operator=( const MatrixExpression< const T, const 
        SelfType, const SelfType, M_TRANS >& proxy ) {
        // A = t( A ), m = n
        if ( elements_ == proxy.lhs().get_pointer() ) {
            if( size1_ == size2_ ) {
                inplace_trans( *this );
                // A = t( A ), m != n
            } else {
                Matrix< T > temp( proxy.lhs().size2(), proxy.lhs().size1() );
                trans( proxy.lhs(), temp );
                magma_free( elements_ );
                size1_ = temp.size1();
                size2_ = temp.size2();
                ld_ = temp.ld();
                elements_ = temp.get_pointer();
            }
        } else {
            // lhs is empty matrix
            if ( size1_ == 0 || size2_ == 0 ) {
                size1_ = proxy.lhs().size2();
                size2_ = proxy.lhs().size1();
                ld_ = magma_roundup( size1_, 32 );
                mem_creator< T >( &elements_, ld_* size2_ );
                trans( proxy.lhs(), *this );
            } else {
                // dimension not match
                if ( size1_ == proxy.lhs().size2() && 
                        size2_ == proxy.lhs().size1() ) {
                    trans( proxy.lhs(), *this );
                }
            }
        }
        return *this;
    }
    // A = solve( B )
    template< typename T >
    Matrix< T >& Matrix< T >::operator=( const MatrixExpression< const T, const 
        SelfType, const SelfType, M_INV >& proxy ) {
        // A = solve( A ), m = n
        if ( elements_ == proxy.lhs().get_pointer() ) {
            if( size1_ == size2_ ) {
                inv( *this );
            } 
        } else {
            // lhs is empty matrix
            if ( size1_ == 0 || size2_ == 0 ) {
                size1_ = proxy.lhs().size1();
                size2_ = proxy.lhs().size2();
                ld_ = magma_roundup( size1_, 32 );
                mem_creator< T >( &elements_, ld_* size2_ );
            } 
            *this = proxy.lhs();
            inv( *this );
        }
        return *this;
    }
    // A += expression( B )
    template< typename T >
    template< typename L, typename R, Oper O >
    Matrix< T >& Matrix< T >::operator+=( 
        const MatrixExpression< const T, const L, const R, O >& proxy ) {
        assert( proxy.size1() == size1_  && proxy.size2() == size2_ 
                && bool( "dimension not match!" ) );
        assert( size1_ > 0 && size2_ > 0 
                && bool( "Matrix not initialized!" ) );
        OpExecutor< SelfType, M_INPLACE_ADD, 
                MatrixExpression< const T, const L, const R, O > >::apply( *this, proxy );
        return *this;
    }
    // A -= expression( B )
    template< typename T >
    template< typename L, typename R, Oper O >
    Matrix< T >& Matrix< T >::operator-=( 
    const MatrixExpression< const T, const L, const R, O >& proxy  ) {
        assert( proxy.size1() == size1_  && proxy.size2() == size2_ 
                && bool( "dimension not match!" ) );
        assert( size1_ > 0 && size2_ > 0 
                && bool( "Matrix not initialized!" ) );
        OpExecutor< SelfType, M_INPLACE_SUB, 
                MatrixExpression< const T, const L, const R, O > >::apply( *this, proxy );
        return *this;
    }
    // A += B
    template< typename T >
    Matrix< T >& Matrix< T >::operator+=( const Matrix< T >& other ) {
        if ( this->elements_ != other.get_pointer() ) {
            inplace_add( *this, other );
        } else {
            scale< T >( *this, 2 );
        }
        return *this;
    }
    // A -= B
    template< typename T >
    Matrix< T >& Matrix< T >::operator-=( const Matrix< T >& other ) {
        if ( this->elements_ != other.get_pointer() ) {
            inplace_sub( *this, other );
        } else {
            set_const< T >( *this, 0 );
        }
        return *this;
    }
    // A *= a
    template< typename T >
    Matrix< T >& Matrix< T >::operator*=( T a ) {
        scale< T >( *this, a );
        return *this;
    }
    // A /= a
    template< typename T >
    Matrix< T >& Matrix< T >::operator/=( T a ) {
        if( a != 0 ) {
            scale< T >( *this, 1 / a );
        } else {
            printf( "Divided by zero!\n" );
        }
        return *this;
    }
    
    // A = a
    template< typename T >
    Matrix< T >& Matrix< T >::operator=( T a ) {
        set_const( *this, a );
        return *this;
    }
    // expression = trans( A )
    template< typename T >
    MatrixExpression< const T, const Matrix< T >, const Matrix< T >, M_TRANS > 
    t( const Matrix< T >& A ) {
        return MatrixExpression< const T, const Matrix< T >, const Matrix< T >, 
                M_TRANS >( A, A );
    }

    // expression = trans( expression( A ) )
    template< typename T, typename L, typename R, Oper O >
    MatrixExpression< const T, const MatrixExpression< const T, const L, const R, O >,
            const MatrixExpression< const T, const L, const R, O >, M_TRANS > 
    t( const MatrixExpression< const T, const L, const R, O >& proxy ) {
        return MatrixExpression< const T, const MatrixExpression< const T, const L, const R,
                O >, const MatrixExpression< const T, const L, const R, O >, M_TRANS >
                ( proxy, proxy );
    }
} //xmagma


#endif /* XMAGMA_MATRIX_EXPRESSION_H */

