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
    template< typename T, typename L, typename R, Oper O, VecType M > // M for Major
    class VectorExpression {
        typedef VectorExpression< const T,  const L,  const R, O, M > SelfType;
    public: 
        typedef magma_int_t size_type;
        // Constructor (no default constructor for vector expression}
        VectorExpression( L& lhs, R& rhs ): lhs_( lhs ), rhs_( rhs ) {}
        // - expression( A )
        VectorExpression< const T, const SelfType, const SelfType,  V_NEGATIVE, M > 
        operator-() const {
            return VectorExpression< const T, const SelfType, 
                const SelfType, V_NEGATIVE, M >
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
    template< typename T, VecType M > Vector< T, M >::Vector( size_type len, 
            magma_queue_t queue ): 
            size1_( len ), size2_( 1 ) {
        if ( size1_> 0 ) {
            mem_creator< T >( &elements_, size1_ );
        }
    }
    // Construct a vector from vector expression
    template< typename T, VecType M > 
    template< typename L, typename R, Oper O >
    Vector< T, M >::Vector(const 
        VectorExpression< const T, const L, const R, O, M >& proxy ):
        size1_( proxy.size1() ), size2_( 1 ) {
        if ( size1_ > 0 ) {
            mem_creator< T >( &elements_, size1_ );
            SelfType::operator=( proxy );
        }
    }
    // Construct from another vector
    template< typename T, VecType M >
    Vector< T, M >::Vector( const SelfType& other ) :
    size1_( other.size1() ), size2_( 1 ) {
        if ( size1_ > 0 ) {
            mem_creator< T >( &elements_, size1_ );
            SelfType::operator=( other );
        }
    }
    /* vector operations */
    // v = a
    template< typename T, VecType M >
    Vector< T, M > & Vector< T, M >::operator=( const T a ) {
        set_const( *this, a );
        return *this;
    }
    // v1 = v2
    template< typename T, VecType M >
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
            copy_vector< M, M >( other, *this );
            return *this;
        }
        if ( other.size1() == size1_ ) {
            copy_vector< M, M >( other, *this );
        } else {
            printf( "dimension doesn't match \n" );
        }
        return *this;
    }
    // v1 = expression( v2 )
    template< typename T, VecType M >
    template< typename L, typename R, Oper O >
    Vector< T, M >& Vector< T, M >::operator=( const VectorExpression< const T,
        const L, const R, O, M >& proxy ) {
        assert( ( proxy.size1() == size1() || size1() == 0 )
                && ( proxy.size2() == size2() || size2() == 0 )
                && bool( "dimension doesn't match!" ) );
        if ( size1() == 0 ) {
            size1_ = proxy.size1();
            size2_ = proxy.size2();
            mem_creator< T >( &elements_, size1_ );
        }
        OpExecutor< SelfType, V_ASSIGN, VectorExpression< const T, const L, const R,
                O, M > >::apply( *this, proxy );
        return *this;
    }
    // v1 = t( v2 )
    template< typename T, VecType M1 >
    template< VecType M2 >
    Vector< T, M1 >& Vector< T, M1 >::operator=( const VectorExpression< const T,
    const Vector< T, M2 >,
    const Vector< T, M2 >, V_TRANS, M1 >& proxy ) {
        if( M1 != M2 && elements_ != proxy.lhs().get_pointer() ) {
            // lhs is empty vector
            if ( size1_ == 0 ) {
                size1_ = proxy.lhs().size2();
                size2_ = proxy.lhs().size1();
                magma_int_t len = size1_ > size2_ ? size1_ : size2_;
                mem_creator< T >( &elements_, len );
                copy_vector( proxy.lhs(), *this );
            } else {
                // dimension not match
                if ( size1_ == proxy.lhs().size1() && 
                    size2_ == proxy.lhs().size2() ) {
                    copy_vector( proxy.lhs(), *this );
                }
            }
        }
        return *this;
    }
    // y += expression( x )
    template< typename T, VecType M >
    template< typename L, typename R, Oper O >
    Vector< T, M >& Vector< T, M >::operator+=( 
        const VectorExpression< const T, const L, const R, O, M >& proxy ) {
        assert( proxy.size1() == size1_  && proxy.size2() == size2_ 
                && bool( "dimension not match!" ) );
        assert( size1_ > 0 && size2_ > 0 
                && bool( "Vector not initialized!" ) );
        OpExecutor< SelfType, V_INPLACE_ADD, 
                VectorExpression< const T, const L, const R, O, M > >::apply( *this, proxy );
        return *this;
    }
    // y -= expression( x )
    template< typename T, VecType M >
    template< typename L, typename R, Oper O >
    Vector< T, M >& Vector< T, M >::operator-=( 
        const VectorExpression< const T, const L, const R, O, M >& proxy ) {
        assert( proxy.size1() == size1_  && proxy.size2() == size2_ 
                && bool( "dimension not match!" ) );
        assert( size1_ > 0 && size2_ > 0 
                && bool( "Vector not initialized!" ) );
        OpExecutor< SelfType, V_INPLACE_SUB, 
                VectorExpression< const T, const L, const R, O, M > >::apply( *this, proxy );
        return *this;
    }
    // y += v
    template< typename T, VecType M >
    Vector< T, M >& Vector< T, M >::operator+=( const SelfType& v ) {
        assert( v.size() == size() && 
                bool( "Vectors have different lengths") );
        if( size() > 0 ) {
            inplace_add( *this, v, 1 );
        }
        return *this;
    }
    // y -= v
    template< typename T, VecType M >
    Vector< T, M >& Vector< T, M >::operator-=( const SelfType& v ) {
        assert( v.size() == size() && 
                bool( "Vectors have different lengths") );
        if( size() > 0 ) {
            inplace_add( *this, v, -1 );
        }
        return *this;
    }
    // x *=a
    template< typename T, VecType M >
    Vector< T, M >& Vector< T, M >::operator*=( const T a ) {
        scale( *this, a );
        return *this;
    }
    // x /= a
    template< typename T, VecType M >
    Vector< T, M >& Vector< T, M >::operator/=( const T a ) {
        scale( *this, 1 / a );
        return *this;
    }
    /* Matrix-vector multiplication */
    // A * x
    template< typename T >
    VectorExpression< const T, const Matrix< T >, const Vector< T, COL >, 
            MV_MULT, COL >
    operator*( const Matrix< T >& A, const Vector< T, COL >& x ) {
        return VectorExpression< const T, const Matrix< T >, 
                const Vector< T, COL >, MV_MULT,
            COL >( A, x );
    }
    // A * expression( x )
    template< typename T, typename L, typename R, Oper O >
    VectorExpression< const T, const Matrix< T >, 
            const VectorExpression< const T, const L, const R, O, COL >, 
                MV_MULT, COL >
    operator*( const Matrix< T >& A, 
            const VectorExpression< const T, const L, const R, O, COL >& x ) {
        return VectorExpression< const T, const Matrix< T >, 
                const VectorExpression< const T, const L, const R, O, COL >, 
                    MV_MULT, COL >( A, x );
    }
    // expression( A ) * x (COL)
    template< typename T, typename L, typename R, Oper O >
    VectorExpression< const T, const MatrixExpression
    <  const T, const L, const R, O >, const Vector< T, COL >, MV_MULT, COL >
    operator*( const MatrixExpression
    < const T, const L, const R, O >& A, const Vector< T, COL >& B ) {
        return  VectorExpression< const T, const MatrixExpression
    < const T, const L, const R, O >, const Vector< T, COL >, MV_MULT, COL >
                ( A, B );
    }
    // expression( A ) * expression( x ) (COL)
    template< typename T, typename L1, typename R1, Oper O1,
            typename L2, typename R2, Oper O2 >
    VectorExpression< const T, const MatrixExpression< const T, const L1, const R1, O1 >, 
            const VectorExpression< const T, const L2,
            const R2, O2, COL >, MV_MULT, COL >
    operator*( const MatrixExpression< const T, const L1, const R1, O1 >& A, 
            const VectorExpression< const T, const L2, 
            const R2, O2, COL >& B ) {
        return  VectorExpression< const T, const MatrixExpression
            < const T, const L1, const R1, O1 >, const VectorExpression< const T, const L2, 
                const R2, O2, COL >, MV_MULT, COL >
                ( A, B );
    }
    // y = A * x
    template< typename T, VecType M >
    Vector< T, M >& Vector< T, M >::operator=( const
    VectorExpression< const T, const Matrix< T >, const Vector< T, M >, MV_MULT, M >& 
    proxy ) {
        magma_int_t size = proxy.size1();
        assert( size == size1() && bool( "Vectors have different lengths" ) );
        if( aliasing( *this, proxy.rhs() ) ) {
            Vector< T, M > result( size );
            mv_mult( proxy.lhs(), proxy.rhs(), result, MagmaNoTrans, 1, 0 );
            *this = result;
        } else {
            mv_mult( proxy.lhs(), proxy.rhs(), *this, MagmaNoTrans, 1, 0 );
        }
        return *this;
    }
    //  x * A (row vector)
    template< typename T >
    VectorExpression< const T, const Vector< T, ROW >, 
            const Matrix< T >, VM_MULT, ROW >
    operator*( const Vector< T, ROW >& x, const Matrix< T >& A ) {
        return VectorExpression< const T, const Vector< T, ROW >,
            const Matrix< T >, VM_MULT,
            ROW >( x, A );
    }
    //  expression( x ) * A (row vector)
    template< typename T, typename L, typename R, Oper O >
    VectorExpression< const T, 
            const VectorExpression< const T, const L, const R, O, ROW >, 
            const Matrix< T >, VM_MULT, ROW >
    operator*( const VectorExpression< const T, const L, 
            const R, O, ROW >& x,
            const Matrix< T >& A ) {
        return VectorExpression< const T, 
                const VectorExpression< const T, const L, const R, O, ROW >,
                const Matrix< T >, VM_MULT,
                ROW >( x, A );
    }
    // x * expression( A )
    template< typename T, typename L, typename R, Oper O >
    VectorExpression< const T, const Vector< T, ROW >, const MatrixExpression
    < const T, const L, const R, O >, VM_MULT, ROW >
    operator*( const Vector< T, ROW >& x, const MatrixExpression
    < const T, const L, const R, O >& A ) {
        return VectorExpression< const T, const Vector< T, ROW >, const MatrixExpression
    < const T, const L, const R, O >, VM_MULT,
                ROW >
                ( x, A );
    }
    // expression( x ) * expression( A )
    template< typename T, typename L1, typename R1, Oper O1,
            typename L2, typename R2, Oper O2 >
    VectorExpression< const T, 
            const VectorExpression< const T, const L1, const R1, O1, ROW >, 
            const MatrixExpression< const T, const L2, const R2, O2 >, VM_MULT, ROW >
    operator*( const VectorExpression< const T, const L1, 
            const R1, O1, ROW >& x, 
            const MatrixExpression< const T, const L2, const R2, O2 >& A ) {
        return VectorExpression< const T,
                const VectorExpression< const T, const L1, const R1, O1, ROW >, 
                const MatrixExpression< const T, const L2, const R2, O2 >, VM_MULT,
                ROW >( x, A );
    }
    // y = x * A (row vector)
    template< typename T, VecType M >
    Vector< T, M >& Vector< T, M >::operator=( const
    VectorExpression< const T, const Vector< T, M >, const Matrix< T >, VM_MULT, M >& 
    proxy ) {
        magma_int_t size = proxy.size1();
        assert( size == size1() && bool( "Vectors have different length" ) );
        if( aliasing( *this, proxy.lhs() ) ) {
            Vector< T, M > result( size );
            mv_mult( proxy.rhs(), proxy.lhs(), result, MagmaTrans, 1, 0 );
            *this = result;
        } else {
            mv_mult( proxy.rhs(), proxy.lhs(), *this, MagmaTrans, 1, 0 );
        }
        return *this;
    }
    // t( A ) * x
    template< typename T >
    VectorExpression< const T, const MatrixExpression< const T, 
    const Matrix< T >, const Matrix< T >, M_TRANS >, 
            const Vector< T, COL >, MV_MULT, COL >
    operator*( const MatrixExpression< const T, 
    const Matrix< T >, const Matrix< T >, M_TRANS >& A, 
            const Vector< T, COL >& x ) {
        return VectorExpression< const T, const MatrixExpression< const T, 
    const Matrix< T >, const Matrix< T >, M_TRANS >, const Vector< T, COL >, 
                MV_MULT,
                COL >
                ( A, x );
    }
    // t( A ) * expression( x )
    template< typename T, typename L, typename R, Oper O >
    VectorExpression< const T, const MatrixExpression< const T, 
    const Matrix< T >, const Matrix< T >, M_TRANS >, 
            const VectorExpression< const T, const L, const R, O, COL >, 
            MV_MULT, COL >
    operator*( const MatrixExpression< const T, 
    const Matrix< T >, const Matrix< T >, M_TRANS >& A, 
            const VectorExpression< const T, const L, const R, O, COL >& x ) {
        return VectorExpression< const T, 
                const MatrixExpression< const T, const Matrix< T >, 
                    const Matrix< T >, M_TRANS >, 
                const VectorExpression< const T, const L, const R, O, COL >,
                MV_MULT, COL >( A, x );
    }
    
    // y = t( A ) * x
    template< typename T, VecType M >
    Vector< T, M >& Vector< T, M >::operator=( const
    VectorExpression< const T, const MatrixExpression< const T, 
    const Matrix< T >, const Matrix< T >, M_TRANS >,
            const Vector< T, M >, MV_MULT, M >& 
    proxy ) {
        magma_int_t size = proxy.size1();
        assert( size == size1() && bool( "Vectors have different length" ) );
        if( aliasing( *this, proxy.rhs() ) ) {
            Vector< T, M > result( size );
            mv_mult( proxy.lhs().lhs(), proxy.rhs(), result, MagmaTrans, 1, 0 );
            *this = result;
        } else {
            mv_mult( proxy.lhs().lhs(), proxy.rhs(), *this, MagmaTrans, 1, 0 );
        }
        return *this;
    }
    //  x * t( A )             row vector x 
    template< typename T >
    VectorExpression< const T, const Vector< T, ROW >, const MatrixExpression< const T, 
    const Matrix< T >, const Matrix< T >, M_TRANS >, VM_MULT, ROW >
    operator*( const Vector< T, ROW >& x, const MatrixExpression< const T, 
    const Matrix< T >, const Matrix< T >, M_TRANS >& A ) {
        return VectorExpression< const T, const Vector< T, ROW >, const MatrixExpression< const T, 
    const Matrix< T >, const Matrix< T >, M_TRANS >, VM_MULT,
                ROW >
                ( x, A );
    }
    // expression( x ) * t( A )             row vector x 
    template< typename T, typename L, typename R, Oper O >
    VectorExpression< const T, 
            const VectorExpression< const T, const L, const R, O, ROW >, 
            const MatrixExpression< const T, const Matrix< T >, 
                const Matrix< T >, M_TRANS >, 
            VM_MULT, ROW >
    operator*( const VectorExpression< const T, const L, const R, O, ROW >& x, 
            const MatrixExpression< const T, const Matrix< T >, 
            const Matrix< T >, M_TRANS >& A ) {
        return VectorExpression< const T, 
            const VectorExpression< const T, const L, const R, O, ROW >, 
            const MatrixExpression< const T, const Matrix< T >, 
                const Matrix< T >, M_TRANS >, 
            VM_MULT, ROW >( x, A );
    }
    // y = x * t( A )       row vector x
    template< typename T, VecType M >
    Vector< T, M >& Vector< T, M >::operator=( const
    VectorExpression< const T, const Vector< T, M >, const MatrixExpression< const T, 
    const Matrix< T >, const Matrix< T >, M_TRANS >, VM_MULT, M >& 
    proxy ) {
        magma_int_t size = proxy.size1();
        assert( size == size1() && bool( "Vectors have different length" ) );
        if( aliasing( *this, proxy.lhs() ) ) {
            Vector< T, M > result( size );
            mv_mult( proxy.rhs().lhs(), proxy.lhs(), result, MagmaNoTrans, 1, 0 );
            *this = result;
        } else {
            mv_mult( proxy.rhs().lhs(), proxy.lhs(), *this, MagmaNoTrans, 1, 0 );
        }
        return *this;
    }

}

#endif /* XMAGMA_VECTOR_EXPRESSION_H */

