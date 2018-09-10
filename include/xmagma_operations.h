/* 
 * File:   xmagma_operations.h
 * Author: hzhang
 * Matrix operations
 * Created on July 23, 2018, 12:35 PM
 */

#ifndef XMAGMA_OPERATIONS_H
#define XMAGMA_OPERATIONS_H

#include "xmagma_matrix.h"
#include "xmagma_matrix_expression.h"
#include "xmagma_R_array.h"
#include "xmagma_backend.h"
#include "xmagma_vector.h"

namespace xmagma{
    
    /* Copy matrix */
    template< typename T > 
    void copy_matrix( const Matrix< T >& mat1, 
            Matrix< T >& mat2 ){ };
    template<>
    void copy_matrix< float >( const Matrix< float >& mat1,
            Matrix< float >& mat2 ){
        magma_scopymatrix( mat1.size1(), mat1.size2(), mat1.get_pointer(),
                mat1.ld(), mat2.get_pointer(), mat2.ld(), 
                Backend::get_queue()  );
    }
    template<>
    void copy_matrix< double >( const Matrix< double >& mat1,
            Matrix< double >& mat2 ){
        magma_dcopymatrix( mat1.size1(), mat1.size2(), mat1.get_pointer(),
                mat1.ld(), mat2.get_pointer(), mat2.ld(), 
                Backend::get_queue()  );
    }
    /* Copy vector */
    template< typename T, VecType Major > 
    void copy_vector( const Vector< T, Major >& v1, 
            Vector< T, Major >& v2 ){ };
    template<>
    void copy_vector< float, ROW >( const Vector< float, ROW >& v1,
            Vector< float, ROW >& v2 ){
        magma_scopyvector( v1.size(), v1.get_pointer(), 1,
                v2.get_pointer(), 1,
                Backend::get_queue()  );
    }
    template<>
    void copy_vector< float, COL >( const Vector< float, COL >& v1,
            Vector< float, COL >& v2 ){
        magma_scopyvector( v1.size(), v1.get_pointer(), 1,
                v2.get_pointer(), 1,
                Backend::get_queue()  );
    }
    template<>
    void copy_vector< double, ROW >( const Vector< double, ROW >& v1,
            Vector< double, ROW >& v2 ){
        magma_dcopyvector( v1.size(), v1.get_pointer(), 1,
                v2.get_pointer(), 1,
                Backend::get_queue()  );
    }
    template<>
    void copy_vector< double, COL >( const Vector< double, COL >& v1,
            Vector< double, COL >& v2 ){
        magma_dcopyvector( v1.size(), v1.get_pointer(), 1,
                v2.get_pointer(), 1,
                Backend::get_queue()  );
    }
    /* Transfer matrix from host to device */
    template< typename T > 
    void transfer_matrix( RMatrix< T >& mat1, 
            Matrix< T >& mat2 ){};
    template<>
    void transfer_matrix< float >( RMatrix< float >& mat1,
            Matrix< float >& mat2 ){
        magma_ssetmatrix( mat1.size1(), mat1.size2(), mat1.begin(),
                mat1.size1(), mat2.get_pointer(), mat2.ld(), 
                Backend::get_queue()  );
    }
    template<>
    void transfer_matrix< double >( RMatrix< double >& mat1,
            Matrix< double >& mat2 ){
        magma_dsetmatrix( mat1.size1(), mat1.size2(), mat1.begin(),
                mat1.size1(), mat2.get_pointer(), mat2.ld(), 
                Backend::get_queue()  );
    }
    /* Transfer vector from host to device */
    template< typename T, VecType M > 
    void transfer_vector( RVector< T >& v1, 
            Vector< T, M >& v2 ){};
    template<>
    void transfer_vector< float, ROW >( RVector< float >& v1,
            Vector< float, ROW >& v2 ){
        magma_ssetvector( v1.size(), v1.begin(), 1, v2.get_pointer(), 1,
                Backend::get_queue()  );
    }
    template<>
    void transfer_vector< float, COL >( RVector< float >& v1,
            Vector< float, COL >& v2 ){
        magma_ssetvector( v1.size(), v1.begin(), 1, v2.get_pointer(), 1,
                Backend::get_queue()  );
    }
    template<>
    void transfer_vector< double, ROW >( RVector< double >& v1,
            Vector< double, ROW >& v2 ){
        magma_dsetvector( v1.size(), v1.begin(), 1, v2.get_pointer(), 1,
                Backend::get_queue()  );
    }
    template<>
    void transfer_vector< double, COL >( RVector< double >& v1,
            Vector< double, COL >& v2 ){
        magma_dsetvector( v1.size(), v1.begin(), 1, v2.get_pointer(), 1,
                Backend::get_queue()  );
    }
    /* Transfer matrix from device to host */
    template< typename T > 
    void transfer_matrix( Matrix< T >& mat1, RMatrix< T >& mat2 ){};
    template<>
    void transfer_matrix< float >( Matrix< float >& mat1,
            RMatrix< float >& mat2 ){
        magma_sgetmatrix( mat1.size1(), mat1.size2(), mat1.get_pointer(),
                mat1.ld(), mat2.begin(), mat2.size1(), 
                Backend::get_queue()  );
    }
    template<>
    void transfer_matrix< double >( Matrix< double >& mat1,
            RMatrix< double >& mat2 ){
        magma_dgetmatrix( mat1.size1(), mat1.size2(), mat1.get_pointer(),
                mat1.ld(), mat2.begin(), mat2.size1(), 
                Backend::get_queue()  );
    }
    /* Transfer vector from device to host */
    template< typename T, VecType M > 
    void transfer_vector( Vector< T, M >& v1, RVector< T >& v2 ){};
    template<>
    void transfer_vector< float, ROW >( Vector< float, ROW >& v1,
            RVector< float >& v2 ){
        magma_sgetvector( v1.size(), v1.get_pointer(),
                1, v2.begin(), 1,
                Backend::get_queue()  );
    }
    template<>
    void transfer_vector< float, COL >( Vector< float, COL >& v1,
            RVector< float >& v2 ){
        magma_sgetvector( v1.size(), v1.get_pointer(),
                1, v2.begin(), 1,
                Backend::get_queue()  );
    }
    template<>
    void transfer_vector< double, ROW >( Vector< double, ROW >& v1,
            RVector< double >& v2 ){
        magma_dgetvector( v1.size(), v1.get_pointer(),
                1, v2.begin(), 1,
                Backend::get_queue()  );
    }
    template<>
    void transfer_vector< double, COL >( Vector< double, COL >& v1,
            RVector< double >& v2 ){
        magma_dgetvector( v1.size(), v1.get_pointer(),
                1, v2.begin(), 1,
                Backend::get_queue()  );
    }
    /* Matrix transpose */
    // inplace transpose
    template< typename T > 
    void inplace_trans( Matrix< T >& mat ) {};
    template<>
    void inplace_trans< float >( Matrix< float >& mat ) {
        magmablas_stranspose_inplace( mat.size1(), mat.get_pointer(),
                mat.ld(), Backend::get_queue() ); 
    }
    template<>
    void inplace_trans< double >( Matrix< double >& mat ) {
        magmablas_dtranspose_inplace( mat.size1(), mat.get_pointer(),
                mat.ld(), Backend::get_queue() ); 
    }
    // transpose
    template< typename T > 
    void trans( const Matrix< T >& a, Matrix< T >& ta ) {};
    template<>
    void trans< float >( const Matrix< float >& a, Matrix< float >& ta ) {
        magmablas_stranspose( a.size1(), a.size2(), a.get_pointer(),
                a.ld(), ta.get_pointer(), ta.ld(), Backend::get_queue() ); 
    }
    template<>
    void trans< double >( const Matrix< double >& a, Matrix< double >& ta ) {
        magmablas_dtranspose( a.size1(), a.size2(), a.get_pointer(),
                a.ld(), ta.get_pointer(), ta.ld(), Backend::get_queue() ); 
    }
    // inplace add
    template< typename T >
    void inplace_add( Matrix< T >& b, const Matrix< T >& a, 
            const T s = 1 ) {};
    template<>
    void inplace_add( Matrix< float >& b, const Matrix< float >& a, 
            const float s ) {
        magmablas_sgeadd( a.size1(), a.size2(), s, a.get_pointer(), a.ld(),
                b.get_pointer(), b.ld(), Backend::get_queue() );
    }
    template<>
    void inplace_add( Matrix< double >& b, const Matrix< double >& a, 
            const double s ) {
        magmablas_dgeadd( a.size1(), a.size2(), s, a.get_pointer(), a.ld(),
                b.get_pointer(), b.ld(), Backend::get_queue() );
    }
    // inplace add2
    template< typename T >
    void inplace_add2( Matrix< T >& b, const Matrix< T >& a, 
            const T s, const T beta = 0 ) {};
    template<>
    void inplace_add2( Matrix< float >& b, const Matrix< float >& a, 
            const float s, const float beta ) {
        magmablas_sgeadd2( a.size1(), a.size2(), s, a.get_pointer(), a.ld(),
                beta, b.get_pointer(), b.ld(), Backend::get_queue() );
    }
    template<>
    void inplace_add2( Matrix< double >& b, const Matrix< double >& a, 
            const double s, const double beta ) {
        magmablas_dgeadd2( a.size1(), a.size2(), s, a.get_pointer(), a.ld(),
                beta, b.get_pointer(), b.ld(), Backend::get_queue() );
    }
    // C = A * B
    template< typename T >
    void m_mult( const Matrix< T >& A, const Matrix< T >& B, Matrix< T >& C, 
            magma_trans_t transA, magma_trans_t transB, T a = 1, T b = 0 ) {};
    template<>
    void m_mult( const Matrix< float >& A, const Matrix< float >& B, 
            Matrix< float >& C, magma_trans_t transA, magma_trans_t transB,
            float a, float b ) {
        magma_int_t m = 0, n = 0, k = 0;
        m = ( transA ) ? A.size2() : A.size1();
        k = ( transA ) ? A.size1() : A.size2();
        n = ( transB ) ? B.size2() : B.size1();
        magmablas_sgemm( transA, transB, m, n, k, a, A.get_pointer(), A.ld(),
                B.get_pointer(), B.ld(), b, C.get_pointer(), C.ld(), 
                Backend::get_queue() );
    }
    template<>
    void m_mult( const Matrix< double >& A, const Matrix< double >& B, 
            Matrix< double >& C, magma_trans_t transA, magma_trans_t transB,
            double a, double b ) {
        magma_int_t m = 0, n = 0, k = 0;
        m = ( transA ) ? A.size2() : A.size1();
        k = ( transA ) ? A.size1() : A.size2();
        n = ( transB ) ? B.size2() : B.size1();
        magmablas_dgemm( transA, transB, m, n, k, a, A.get_pointer(), A.ld(),
                B.get_pointer(), B.ld(), b, C.get_pointer(), C.ld(), 
                Backend::get_queue() );
    }
            
    // inplace_sub
    template< typename T >
    void inplace_sub( Matrix< T >& b, const Matrix< T >& a,
            const T s = 1 ) {};
    template<>
    void inplace_sub( Matrix< float >& b, const Matrix< float >& a,
            const float s ) {
        magmablas_sgeadd( a.size1(), a.size2(),  -s, a.get_pointer(), a.ld(),
                b.get_pointer(), b.ld(), Backend::get_queue() );
    }
    template<>
    void inplace_sub( Matrix< double >& b, const Matrix< double >& a,
            const double s ) {
        magmablas_dgeadd( a.size1(), a.size2(),  -s, a.get_pointer(), a.ld(),
                b.get_pointer(), b.ld(), Backend::get_queue() );
    }
    // set all elements of a matrix to be a constant value
    template< typename T >
    void set_const( Matrix< T >& A,  T a ) {};
    template<>
    void set_const( Matrix< float >& A, float a ) {
        magmablas_slaset( MagmaFull, A.size1(), A.size2(), a, a, A.get_pointer(),
                A.ld(), Backend::get_queue() );
    }
    template<>
    void set_const( Matrix< double >& A, double a ) {
        magmablas_dlaset( MagmaFull, A.size1(), A.size2(), a, a, A.get_pointer(),
                A.ld(), Backend::get_queue() );
    }
    // scale
    template< typename T >
    void scale( Matrix< T >& a, T alpha ) {};
    template<>
    void scale( Matrix< float >& a, float alpha ) {
        magma_int_t info;
        magmablas_slascl( MagmaFull, 0, 0, 1, alpha, a.size1(),
                a.size2(), a.get_pointer(), a.ld(), Backend::get_queue(),
                &info );
    }
    template<>
    void scale( Matrix< double >& a, double alpha ) {
        magma_int_t info;
        magmablas_dlascl( MagmaFull, 0, 0, 1, alpha, a.size1(),
                a.size2(), a.get_pointer(), a.ld(), Backend::get_queue(),
                &info );
    }
    // expression( A ) + expression( B )
    template< typename L1, typename R1, Oper O1,
                     typename L2, typename R2, Oper O2 >
    MatrixExpression< const MatrixExpression< const L1, const R1, O1 >,
            const MatrixExpression< const L2, const R2, O2 >, M_ADD >
    operator+( MatrixExpression< const L1, const R1, O1 > const& proxy1,
            MatrixExpression< const L2, const R2, O2 > const& proxy2 ) {
        assert( proxy1.size1() == proxy2.size1()
                && proxy1.size2() == proxy2.size2() 
                && bool( "dimensions not match!") );
        return MatrixExpression< const MatrixExpression< const L1, const R1,
                O1 >, const MatrixExpression< const L2, const R2, O2 >, M_ADD >
                ( proxy1, proxy2 );
    }
    // expression( A ) + B
    template< typename L, typename R, Oper O, typename T >
    MatrixExpression< const MatrixExpression< const L, const R, O >, 
            const Matrix< T >, M_ADD >
    operator+( MatrixExpression< const L, const R, O > const& proxy1,
            Matrix< T > const& proxy2 ) {
        assert( proxy1.size1() == proxy2.size1()
                && proxy1.size2() == proxy2.size2() 
                && bool( "Dimension not match!" ) );
        return MatrixExpression< const MatrixExpression< const L, const R, O >,
                const Matrix< T >, M_ADD >( proxy1, proxy2 );
    }
    // A + expression( B ) = expression( B ) + A
    template< typename L, typename R, Oper O, typename T >
    MatrixExpression< const MatrixExpression< const L, const R, O >, 
            const Matrix< T >, M_ADD >
    operator+( Matrix< T > const& proxy2,
            MatrixExpression< const L, const R, O > const& proxy1
             ) {
        
        return ( proxy1 + proxy2 );
    }
    // A + B
    template< typename T >
    MatrixExpression< const Matrix< T >, const Matrix< T >, M_ADD >
    operator+( const Matrix< T >& A, const Matrix< T >& B ) {
        return MatrixExpression< const Matrix< T >,
                const Matrix< T >, M_ADD >( A, B );
    }
    // expression( A ) - expression( B )
    template< typename L1, typename R1, Oper O1,
            typename L2, typename R2, Oper O2 >
    MatrixExpression< const MatrixExpression< const L1, const R1, O1 >,
            const MatrixExpression< const L2, const R2, O2 >, M_SUB >
    operator-( MatrixExpression< const L1, const R1, O1 > const& proxy1,
            MatrixExpression< const L2, const R2, O2 > const& proxy2 ) {
        assert( proxy1.size1() == proxy2.size1() 
                && proxy1.size2() == proxy2.size2() 
                && bool( "Dimension not match!" ) );
        return MatrixExpression< const MatrixExpression< const L1, const R1,
                O1 >, const MatrixExpression< const L2, const R2, O2 >, M_SUB >
                ( proxy1, proxy2 );
    } 
    // expression( A ) - B
    template< typename L, typename R, Oper O, typename T >
    MatrixExpression< const MatrixExpression< const L, const R, O >,
            const Matrix< T >, M_SUB >
    operator-( MatrixExpression< const L, const R, O > const& proxy1,
            Matrix< T > const& proxy2 ) {
        assert( proxy1.size1() == proxy2.size1() 
                && proxy1.size2() == proxy2.size2() 
                && bool( "Dimension not match!" ) );
        return MatrixExpression< const MatrixExpression< const L, const R, O >,
                const Matrix< T >, M_SUB >( proxy1, proxy2 );
    }
    // A - expression( B )
    template< typename L, typename R, Oper O, typename T >
    MatrixExpression< const Matrix< T >,
            const MatrixExpression< const L, const R, O >,
            M_SUB >
    operator-( Matrix< T > const& proxy2,
            MatrixExpression< const L, const R, O > const& proxy1 ) {
        return MatrixExpression< const Matrix< T >,
                const MatrixExpression< const L, const R, O >,
                 M_SUB >( proxy2, proxy1 );
    }
    // A - B
    template< typename T >
    MatrixExpression< const Matrix< T >, const Matrix< T >, M_SUB >
    operator-( const Matrix< T >& A, const Matrix< T >& B ) {
        return MatrixExpression< const Matrix< T >, const Matrix< T >, M_SUB >
                ( A, B );
    }
    // A * a
    template< typename T, typename S >
    MatrixExpression< const Matrix< T >, const S,  M_SCALE >
    operator*( const Matrix< T >& A, const S& a ) {
        return MatrixExpression< const Matrix< T >, const S, M_SCALE >
                ( A,  a );
    }
    // expression( A ) * a;
    template< typename L, typename R, Oper O, typename S >
    MatrixExpression< const MatrixExpression< const L, const R, O >,
            const S, M_SCALE >
    operator*( const MatrixExpression< const L, const R, O >& proxy, 
            const S& a ) {
        return MatrixExpression< const MatrixExpression< const L, const R, O >,
            const S, M_SCALE >( proxy,  a );
    }
    // a * A = A * a
    template< typename T, typename S >
    MatrixExpression< const Matrix< T >, const S,  M_SCALE >
    operator*( const S& a, const Matrix< T >& A ) {
        return MatrixExpression< const Matrix< T >, const S,  M_SCALE >
                ( A, a );
    }
    // a * expression( A ); int
    template< typename L, typename R, Oper O >
    MatrixExpression< const MatrixExpression< const L, const R, O >,
            const int, M_SCALE >
    operator*( const int& a, const MatrixExpression< const L, const R, O >& proxy ) {
        return MatrixExpression< const MatrixExpression< const L, const R, O >,
            const int, M_SCALE >( proxy,  a );
    }
    // a * expression( A ); float
    template< typename L, typename R, Oper O >
    MatrixExpression< const MatrixExpression< const L, const R, O >,
            const float, M_SCALE >
    operator*( const float& a, const MatrixExpression< const L, const R, O >& proxy ) {
        return MatrixExpression< const MatrixExpression< const L, const R, O >,
            const float, M_SCALE >( proxy,  a );
    }
    // a * expression( A ); double
    template< typename L, typename R, Oper O >
    MatrixExpression< const MatrixExpression< const L, const R, O >,
            const double, M_SCALE >
    operator*( const double& a, const MatrixExpression< const L, const R, O >& proxy ) {
        return MatrixExpression< const MatrixExpression< const L, const R, O >,
            const double, M_SCALE >( proxy,  a );
    }
    // -A
    template< typename T >
    MatrixExpression< const Matrix< T >, const Matrix< T >, M_NEGATIVE >
    Matrix< T >::operator-() const {
        return MatrixExpression< const SelfType, const SelfType, M_NEGATIVE >
                ( *this, *this );
    }
    // A / a = A * ( 1 / a )
    template< typename T, typename S >
    MatrixExpression< const Matrix< T >, const S, M_DIV >
    operator/( const Matrix< T >& A, const S& a ) {
        assert( a != 0 
                && bool( "Divided by zero!" ) );
        return MatrixExpression< const Matrix< T >, const S, M_DIV >
                ( A, a );
    }
    // expression( A ) / a
    template< typename L, typename R, Oper O, typename S >
    MatrixExpression< const MatrixExpression< const L, const R, O >,
            const S, M_DIV >
    operator/( const MatrixExpression< const L, const R, O >& proxy, 
            const S& a ) {
        assert( a != 0 
                && bool( "Divided by zero!" ) );
        return MatrixExpression< const MatrixExpression< const L, const R, O >,
            const S, M_DIV >( proxy,  a );
    }
    // expression( v1  * t( v2 ) ) * a
    template< typename T, typename S >
    MatrixExpression< const MatrixExpression< const Vector< T, COL >, 
            const Vector< T, COL >, V_OUTER >, const S, M_SCALE >
    operator*=( const MatrixExpression< const Vector< T, COL >,
            const Vector< T, COL >, V_OUTER >&
    proxy, const S& a ) {
        return MatrixExpression< const MatrixExpression< const Vector< T, COL >, 
            const Vector< T, COL >, V_OUTER >, const S, M_SCALE >( proxy, a );
    }
    // a * expression( v1  * t( v2 ) )
    template< typename T, typename S >
    MatrixExpression< const MatrixExpression< const Vector< T, COL >, 
            const Vector< T, COL >, V_OUTER >, const S, M_SCALE >
    operator*=( const S& a, const MatrixExpression< const Vector< T, COL >,
            const Vector< T, COL >, V_OUTER >&
    proxy ) {
        return proxy * a;
    }
    // A * B 
    template< typename T >
    MatrixExpression< const Matrix< T >, const Matrix< T >, M_MULT >
    operator*( const Matrix< T >& A, const Matrix< T >& B ) {
        return MatrixExpression< const Matrix< T >, const Matrix< T >, M_MULT >
                ( A, B );
    }
    // A * expression( B )  
    template< typename T, typename L, typename R, Oper O >
    MatrixExpression< const Matrix< T >, const MatrixExpression
    < const L, const R, O >, M_MULT >
    operator*( const Matrix< T >& A, const MatrixExpression
    < const L, const R, O >& B ) {
        return MatrixExpression< const Matrix< T >, const MatrixExpression
    < const L, const R, O >, M_MULT >
                ( A, B );
    }
    // expresssion( A ) * B 
    template< typename T, typename L, typename R, Oper O >
    MatrixExpression< const MatrixExpression
    < const L, const R, O >, const Matrix< T >, M_MULT >
    operator*( const MatrixExpression
    < const L, const R, O >& A, const Matrix< T >& B ) {
        return MatrixExpression< const MatrixExpression
    < const L, const R, O >, const Matrix< T >, M_MULT >
                ( A, B );
    }
    // expresssion( A ) * expression( B ) 
    template< typename T, typename LL, typename LR, Oper LO,
            typename RL, typename RR, Oper RO >
    MatrixExpression< const MatrixExpression
    < const LL, const LR, LO >, const MatrixExpression
    < const RL, const RR, RO >, M_MULT >
    operator*( const MatrixExpression
    < const LL, const LR, LO >& A, const MatrixExpression
    < const RL, const RR, RO >& B ) {
        return MatrixExpression< const MatrixExpression
    < const LL, const LR, LO >, const MatrixExpression
    < const RL, const RR, RO >, M_MULT >
                ( A, B );
    }
    /* OpExecutor */
    // A = trans( expression )
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_ASSIGN, MatrixExpression<
            const MatrixExpression< const L, const R, O >, 
            const MatrixExpression< const L, const R, O >, M_TRANS > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression<
        const MatrixExpression< const L, const R, O >, 
        const MatrixExpression< const L, const R, O >, M_TRANS >& rhs ) {
            Matrix< T > temp( rhs.rhs());
            lhs = t( temp );
        }
    };
    // A += B
    template< typename T >
    class OpExecutor< Matrix< T >, M_INPLACE_ADD, Matrix< T > > {
    public:
        static void apply( Matrix< T >& lhs, const Matrix< T >& rhs ) {
            lhs += rhs;
        }
    };
    // A = B ( expr ) + C ( expr )
    template< typename T, typename L, typename R >
    class OpExecutor< Matrix< T >, M_ASSIGN, MatrixExpression< const L, 
            const R, M_ADD > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression< const L, 
            const R, M_ADD >& proxy ) {
            if( aliasing( lhs, proxy ) ) {
                Matrix< T > temp( proxy.lhs() );
                OpExecutor< Matrix< T >, M_INPLACE_ADD, R >::apply( 
                temp, proxy.rhs());
                lhs = temp;
            } else {
                lhs = proxy.lhs();
                OpExecutor< Matrix< T >, M_INPLACE_ADD, R >::apply( lhs,
                        proxy.rhs());
            }
        }
    };
    // A += trans( B )
    template< typename T >
    class OpExecutor< Matrix< T >, M_INPLACE_ADD, 
            MatrixExpression< const Matrix< T >, 
                                         const Matrix< T >, M_TRANS > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression<
                const Matrix< T >,
                const Matrix< T >, M_TRANS >& rhs ) {
            Matrix< T > temp( t( rhs.rhs() ) );
            lhs += temp;
        }
                                                                                  
    };
    // A += trans( expression( B ) )
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_INPLACE_ADD, MatrixExpression<
    const MatrixExpression< const L, const R, O >, const MatrixExpression<
    const L, const R, O >, M_TRANS > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression<
        const MatrixExpression< const L, const R, O >,
        const MatrixExpression< const L, const R, O >, M_TRANS >& rhs ) {
            Matrix< T > temp1( rhs.rhs());
            Matrix< T > temp2( temp1.size2(), temp1.size1() );
            trans( temp1, temp2 );
            lhs += temp2;
        }
    };
    // A -= B
    template< typename T >
    class OpExecutor< Matrix< T >, M_INPLACE_SUB, Matrix< T > > {
    public:
        static void apply( Matrix< T >& lhs, const Matrix< T >& rhs ) {
            lhs -= rhs;
        }
    };
    // A -= trans( B )
    template< typename T >
    class OpExecutor< Matrix< T >, M_INPLACE_SUB, MatrixExpression< 
    const Matrix< T >, const Matrix< T >, M_TRANS > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression< 
        const Matrix< T >, const Matrix< T >, M_TRANS >& rhs ) {
            Matrix< T > temp( rhs );
            lhs -= temp;
        }
    };
    // A -= trans( expression( B ) )
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_INPLACE_SUB,
            MatrixExpression< const MatrixExpression< const L, const R, O >,
            const MatrixExpression< const L, const R, O >, M_TRANS > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression< 
            const MatrixExpression< const L, const R, O >,
            const MatrixExpression< const L, const R, O >, M_TRANS >& rhs ) {
            Matrix< T > temp1( rhs.rhs());
            Matrix< T > temp2( temp1.size2(), temp1.size1() );
            trans( temp1, temp2 );
            lhs -= temp2;
        }
    };
    /*                        A Oper B * a                         */
    // A += B * alpha
    template< typename T, typename S >
    class OpExecutor< Matrix< T >, M_INPLACE_ADD, MatrixExpression< 
    const Matrix< T >, const S, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression< const 
            Matrix< T >, const S, M_SCALE >& proxy ) {
                inplace_add( lhs, proxy.lhs(),  T( proxy.rhs() ) );
        }
    };
    // A += - B  
    template< typename T >
    class OpExecutor< Matrix< T >, M_INPLACE_ADD, MatrixExpression< 
    const Matrix< T >, const Matrix< T >, M_NEGATIVE> > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression< const 
            Matrix< T >, const Matrix< T >, M_NEGATIVE>& proxy ) {
                inplace_add( lhs, proxy.lhs(),  T( - 1 )  );
        }
    };
    // A -= B * alpha
    template< typename T, typename S >
    class OpExecutor< Matrix< T >, M_INPLACE_SUB, MatrixExpression< 
    const Matrix< T >, const S, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression< const 
            Matrix< T >, const S, M_SCALE >& proxy ) {
                inplace_add( lhs, proxy.lhs(),  - T( proxy.rhs() ) );
        }
    };
    // A -= - B 
    template< typename T >
    class OpExecutor< Matrix< T >, M_INPLACE_SUB, MatrixExpression< 
    const Matrix< T >, const Matrix< T >, M_NEGATIVE > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression< const 
            Matrix< T >, const Matrix< T >, M_NEGATIVE>& proxy ) {
                inplace_add( lhs, proxy.lhs(),  T( 1 ) );
        }
    };
    // A = B * a
    template< typename T, typename S >
    class OpExecutor< Matrix< T >, M_ASSIGN, MatrixExpression<
    const Matrix< T >, const S, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression< 
        const Matrix< T >, const S, M_SCALE >& proxy ) {
            inplace_add2( lhs, proxy.lhs(),  T( proxy.rhs() ) );
        }
    };
    // A = expression( B ) * a
    template< typename T, typename L, typename R, Oper O, typename S >
    class OpExecutor< Matrix< T >, M_ASSIGN, MatrixExpression< 
    const MatrixExpression< const L, const R, O >, const S, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression<
         const MatrixExpression< const L,
                const R, O >, const S, M_SCALE >& proxy ) {
            Matrix< T > temp( proxy.lhs() );
            lhs = temp * proxy.rhs();
        }
    };
    /*                        A Oper B / a                         */
    // A += B / alpha
    template< typename T, typename S >
    class OpExecutor< Matrix< T >, M_INPLACE_ADD, MatrixExpression< 
    const Matrix< T >, const S, M_DIV > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression< const 
            Matrix< T >, const S, M_DIV >& proxy ) {
                inplace_add( lhs, proxy.lhs(),  1 / T( proxy.rhs() ) );
        }
    };
    // A += expression( B ) / alpha
    template< typename T, typename S, typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_INPLACE_ADD, MatrixExpression< 
    const MatrixExpression< const L, const R, O >, const S, M_DIV > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression< const 
            MatrixExpression< const L, const R, O >, const S, M_DIV >& proxy ) {
            Matrix< T > temp( proxy.lhs() );
            lhs += temp / T( proxy.rhs() );
        }
    };
    // A -= B / alpha
    template< typename T, typename S >
    class OpExecutor< Matrix< T >, M_INPLACE_SUB, MatrixExpression< 
    const Matrix< T >, const S, M_DIV > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression< const 
            Matrix< T >, const S, M_DIV >& proxy ) {
                inplace_add( lhs, proxy.lhs(),  - 1 / T ( proxy.rhs() ) );
        }
    };
    // A -= expression( B ) / alpha
    template< typename T, typename S, typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_INPLACE_SUB, MatrixExpression< 
    const MatrixExpression< const L, const R, O >, const S, M_DIV > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression< const 
            MatrixExpression< const L, const R, O >, const S, M_DIV >& proxy ) {
            Matrix< T > temp( proxy.lhs() );
            lhs -= temp / T( proxy.rhs() );
        }
    };
    // A = B / a
    template< typename T, typename S >
    class OpExecutor< Matrix< T >, M_ASSIGN, MatrixExpression<
    const Matrix< T >, const S, M_DIV > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression< 
        const Matrix< T >, const S, M_DIV >& proxy ) {
            inplace_add2( lhs, proxy.lhs(),  1 / T( proxy.rhs() ) );
        }
    };
    // A = expression( B ) / a
    template< typename T, typename L, typename R, Oper O, typename S >
    class OpExecutor< Matrix< T >, M_ASSIGN, MatrixExpression< 
    const MatrixExpression< const L, const R, O >, const S, M_DIV > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression<
         const MatrixExpression< const L,
                const R, O >, const S, M_DIV >& proxy ) {
            Matrix< T > temp( proxy.lhs() );
            lhs = temp * ( 1 / T ( proxy.rhs() ) );
        }
    };
    // A = - B
    template< typename T >
    class OpExecutor< Matrix< T >, M_ASSIGN, MatrixExpression<
    const Matrix< T >, const Matrix< T >, M_NEGATIVE > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression< 
        const Matrix< T >, const Matrix< T >, M_NEGATIVE >& proxy ) {
            lhs = - 1 * proxy.lhs();
        }
    };
    // A = - expression( B )
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_ASSIGN, MatrixExpression< 
    const MatrixExpression< const L, const R, O >, 
            const MatrixExpression< const L, const R, O >, M_NEGATIVE > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression<
         const MatrixExpression< const L,
                const R, O >, const MatrixExpression< const L,
                const R, O >, M_NEGATIVE >& proxy ) {
            Matrix< T > temp( proxy.lhs() );
            lhs = - 1 * temp;
        }
    };
    // A += expression( B ) * a
    template< typename T, typename L, typename R, Oper O, typename S >
    class OpExecutor< Matrix< T >, M_INPLACE_ADD, MatrixExpression< 
    const MatrixExpression< const L, const R, O >, const S, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression<
        const MatrixExpression< const L, const R, O >, const S, M_SCALE >& proxy  ) {
            Matrix< T > temp( proxy.lhs() );
            lhs += temp * proxy.rhs();
        }
    };
    // A -= expression( B ) * a
    template< typename T, typename L, typename R, Oper O, typename S >
    class OpExecutor< Matrix< T >, M_INPLACE_SUB, MatrixExpression< 
    const MatrixExpression< const L, const R, O >, const S, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression<
        const MatrixExpression< const L, const R, O >, const S, M_SCALE >& proxy  ) {
            Matrix< T > temp( proxy.lhs() );
            lhs -= temp * proxy.rhs();
        }
    };
    // A += - expression( B )
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_INPLACE_ADD, MatrixExpression< 
    const MatrixExpression< const L, const R, O >, 
    const MatrixExpression< const L, const R, O >, M_NEGATIVE > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression<
        const MatrixExpression< const L, const R, O >, 
        const MatrixExpression< const L, const R, O >, M_NEGATIVE >& proxy  ) {
            Matrix< T > temp( proxy.lhs() );
            lhs += temp * (  - 1 );
        }
    };
    // A -= - expression( B )
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_INPLACE_SUB, MatrixExpression< 
    const MatrixExpression< const L, const R, O >, 
    const MatrixExpression< const L, const R, O >, M_NEGATIVE > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression<
        const MatrixExpression< const L, const R, O >, 
        const MatrixExpression< const L, const R, O >, M_NEGATIVE >& proxy  ) {
            Matrix< T > temp( proxy.lhs() );
            lhs -= temp * (  - 1 );
        }
    };
    // A += expression( B ) + expression( C )
    template< typename T, typename L, typename R >
    class OpExecutor< Matrix< T >, M_INPLACE_ADD, MatrixExpression< const L, 
            const R, M_ADD > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression< const L, 
            const R, M_ADD >& proxy ) {
            if( aliasing( lhs, proxy ) ) {
                Matrix< T > temp( proxy.lhs() );
                OpExecutor< Matrix< T >, M_INPLACE_ADD, R >::apply( 
                temp, proxy.rhs());
                lhs += temp;
            } else {
                lhs += proxy.lhs();
                OpExecutor< Matrix< T >, M_INPLACE_ADD, R >::apply( lhs,
                        proxy.rhs());
            }
        }
    };
    // A -= expression( B ) + expression( C )
    template< typename T, typename L, typename R >
    class OpExecutor< Matrix< T >, M_INPLACE_SUB, MatrixExpression< const L, 
            const R, M_ADD > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression< const L, 
            const R, M_ADD >& proxy ) {
            if( aliasing( lhs, proxy ) ) {
                Matrix< T > temp( proxy.lhs() );
                OpExecutor< Matrix< T >, M_INPLACE_ADD, R >::apply( 
                temp, proxy.rhs());
                lhs -= temp;
            } else {
                lhs -= proxy.lhs();
                OpExecutor< Matrix< T >, M_INPLACE_SUB, R >::apply( lhs,
                        proxy.rhs());
            }
        }
    };
    // A = expression( B ) - expression( C )
    template< typename T, typename L, typename R >
    class OpExecutor< Matrix< T >, M_ASSIGN, MatrixExpression< const L, 
            const R, M_SUB > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression< const L, 
            const R, M_SUB >& proxy ) {
            if( aliasing( lhs, proxy ) ) {
                Matrix< T > temp( proxy.lhs() );
                OpExecutor< Matrix< T >, M_INPLACE_SUB, R >::apply( 
                temp, proxy.rhs());
                lhs = temp;
            } else {
                lhs = proxy.lhs();
                OpExecutor< Matrix< T >, M_INPLACE_SUB, R >::apply( lhs,
                        proxy.rhs());
            }
        }
    };
    // A += expression( B ) - expression( C )
    template< typename T, typename L, typename R >
    class OpExecutor< Matrix< T >, M_INPLACE_ADD, MatrixExpression< const L, 
            const R, M_SUB > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression< const L, 
            const R, M_SUB >& proxy ) {
            if( aliasing( lhs, proxy ) ) {
                Matrix< T > temp( proxy.lhs() );
                OpExecutor< Matrix< T >, M_INPLACE_SUB, R >::apply( 
                temp, proxy.rhs());
                lhs += temp;
            } else {
                lhs += proxy.lhs();
                OpExecutor< Matrix< T >, M_INPLACE_SUB, R >::apply( lhs,
                        proxy.rhs());
            }
        }
    };
    // A -= expression( B ) - expression( C )
    template< typename T, typename L, typename R >
    class OpExecutor< Matrix< T >, M_INPLACE_SUB, MatrixExpression< const L, 
            const R, M_SUB > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression< const L, 
            const R, M_SUB >& proxy ) {
            if( aliasing( lhs, proxy ) ) {
                Matrix< T > temp( proxy.lhs() );
                OpExecutor< Matrix< T >, M_INPLACE_SUB, R >::apply( 
                temp, proxy.rhs());
                lhs -= temp;
            } else {
                lhs -= proxy.lhs();
                OpExecutor< Matrix< T >, M_INPLACE_ADD, R >::apply( lhs,
                        proxy.rhs());
            }
        }
    };
    /* Matrix - Matrix products */
    // C = A * B
    template< typename T >
    class OpExecutor< Matrix< T >, M_ASSIGN, MatrixExpression<
    const Matrix< T >, const Matrix< T >, M_MULT > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression<
        const Matrix< T >, const Matrix< T >, M_MULT >& proxy ) {
            if( aliasing( lhs, proxy ) ) {
                Matrix< T > temp( proxy );
                lhs = temp;
            } else {
                m_mult( proxy.lhs(), proxy.rhs(), lhs, MagmaNoTrans, MagmaNoTrans );
            }
        }
    };
    // C = A * t( B )
    template< typename T >
    class OpExecutor< Matrix< T >, M_ASSIGN, MatrixExpression<
    const Matrix< T >, const MatrixExpression< const Matrix< T >, 
            const Matrix< T >, M_TRANS >, M_MULT > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression<
    const Matrix< T >, const MatrixExpression< const Matrix< T >, 
            const Matrix< T >, M_TRANS >, M_MULT >& proxy ) {
            if( aliasing( lhs, proxy ) ) {
                Matrix< T > temp( proxy );
                lhs = temp;
            } else {
                m_mult( proxy.lhs(), proxy.rhs().lhs(), lhs,
                        MagmaNoTrans, MagmaTrans );
            }
        }
    };
    // C = A * expression( B )
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_ASSIGN,  
            MatrixExpression< const Matrix< T >, 
            const MatrixExpression< const L, const R, O >,
            M_MULT > > {
    public:
        static void apply( Matrix< T >& lhs,
                 const MatrixExpression< const Matrix< T >, 
            const MatrixExpression< const L, const R, O >,
            M_MULT >& proxy ) {
            Matrix< T > temp( proxy.rhs() );
            m_mult( proxy.lhs(), temp, lhs, MagmaNoTrans, MagmaNoTrans );
        }
    };
    // C = t( A ) * B
    template< typename T >
    class OpExecutor< Matrix< T >, M_ASSIGN, MatrixExpression<
    const MatrixExpression< const Matrix< T >, 
            const Matrix< T >, M_TRANS >,
    const Matrix< T >, M_MULT > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression<
    const MatrixExpression< const Matrix< T >, 
            const Matrix< T >, M_TRANS >,
    const Matrix< T >, M_MULT >& proxy ) {
            if( aliasing( lhs, proxy ) ) {
                Matrix< T > temp( proxy );
                lhs = temp;
            } else {
                m_mult( proxy.lhs().lhs(), proxy.rhs(), lhs,
                        MagmaTrans, MagmaNoTrans );
            }
        }
    };
    // C = expression( A ) * B
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_ASSIGN,  
            MatrixExpression< const MatrixExpression< const L, const R, O >,
            const Matrix< T >, M_MULT > > {
    public:
        static void apply( Matrix< T >& lhs,
                 const MatrixExpression< const MatrixExpression< const L, const R, O >,
            const Matrix< T >, M_MULT >& proxy ) {
            Matrix< T > temp( proxy.lhs() );
            m_mult( temp, proxy.rhs(), lhs, MagmaNoTrans, MagmaNoTrans );
        }
    };
    // C = t( A ) * t( B )
    template< typename T >
    class OpExecutor< Matrix< T >, M_ASSIGN, MatrixExpression<
    const MatrixExpression< const Matrix< T >, const Matrix< T >, M_TRANS >,
    const MatrixExpression< const Matrix< T >, const Matrix< T >, M_TRANS >,
    M_MULT > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression<
    const MatrixExpression< const Matrix< T >, const Matrix< T >, M_TRANS >,
    const MatrixExpression< const Matrix< T >, const Matrix< T >, M_TRANS >,
    M_MULT >& proxy ) {
            if( aliasing( lhs, proxy ) ) {
                Matrix< T > temp( proxy );
                lhs = temp;
            } else {
                m_mult( proxy.lhs(), proxy.rhs(), lhs, MagmaTrans, MagmaTrans );
            }
        }
    };
    // C = expression( A ) * expression( B )
    template< typename T,
            typename LL, typename LR, Oper LO,
            typename RL, typename RR, Oper RO >
    class OpExecutor< Matrix< T >, 
            M_ASSIGN,
            MatrixExpression< const MatrixExpression< const LL, const LR, LO >,
            const MatrixExpression< const RL, const RR, RO >,
            M_MULT > > {
    public: 
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                const MatrixExpression< const LL, const LR, LO >,
                const MatrixExpression< const RL, const RR, RO >, M_MULT >& 
            proxy ) {
            Matrix< T > temp1( proxy.lhs() );
            Matrix< T > temp2( proxy.rhs() );
            m_mult( temp1, temp2, lhs, MagmaNoTrans, MagmaNoTrans );
        }
    };
    // C += A * B
    template< typename T >
    class OpExecutor< Matrix< T >, M_INPLACE_ADD, MatrixExpression<
    const Matrix< T >, const Matrix< T >, M_MULT > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression<
        const Matrix< T >, const Matrix< T >, M_MULT >& proxy ) {
            if( aliasing( lhs, proxy ) ) {
                Matrix< T > temp( proxy );
                lhs += temp;
            } else {
                m_mult( proxy.lhs(), proxy.rhs(), lhs, 
                        MagmaNoTrans, MagmaNoTrans, T ( 1 ), T( 1 ) );
            }
        }
    };
    // C += A * t( B )
    template< typename T >
    class OpExecutor< Matrix< T >, M_INPLACE_ADD, MatrixExpression<
    const Matrix< T >, const MatrixExpression< const Matrix< T >, 
            const Matrix< T >, M_TRANS >, M_MULT > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression<
    const Matrix< T >, const MatrixExpression< const Matrix< T >, 
            const Matrix< T >, M_TRANS >, M_MULT >& proxy ) {
            if( aliasing( lhs, proxy ) ) {
                Matrix< T > temp( proxy );
                lhs += temp;
            } else {
                m_mult( proxy.lhs(), proxy.rhs().lhs(), lhs,
                        MagmaNoTrans, MagmaTrans, T( 1 ), T( 1 ) );
            }
        }
    };
    // C += A * expression( B )
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_INPLACE_ADD,  
            MatrixExpression< const Matrix< T >, 
            const MatrixExpression< const L, const R, O >,
            M_MULT > > {
    public:
        static void apply( Matrix< T >& lhs,
                 const MatrixExpression< const Matrix< T >, 
            const MatrixExpression< const L, const R, O >,
            M_MULT >& proxy ) {
            Matrix< T > temp( proxy.rhs() );
            m_mult( proxy.lhs(), temp, lhs, MagmaNoTrans, MagmaNoTrans, 
                    T( 1 ), T( 1 ) );
        }
    };
    // C += t( A ) * B
    template< typename T >
    class OpExecutor< Matrix< T >, M_INPLACE_ADD, MatrixExpression<
    const MatrixExpression< const Matrix< T >, 
            const Matrix< T >, M_TRANS >,
    const Matrix< T >, M_MULT > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression<
    const MatrixExpression< const Matrix< T >, 
            const Matrix< T >, M_TRANS >,
    const Matrix< T >, M_MULT >& proxy ) {
            if( aliasing( lhs, proxy ) ) {
                Matrix< T > temp( proxy );
                lhs += temp;
            } else {
                m_mult( proxy.lhs().lhs(), proxy.rhs(), lhs,
                        MagmaTrans, MagmaNoTrans, T( 1 ), T( 1 ) );
            }
        }
    };
    // C += expression( A ) * B
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_INPLACE_ADD,  
            MatrixExpression< const MatrixExpression< const L, const R, O >,
            const Matrix< T >, M_MULT > > {
    public:
        static void apply( Matrix< T >& lhs,
                 const MatrixExpression< const MatrixExpression< const L, const R, O >,
            const Matrix< T >, M_MULT >& proxy ) {
            Matrix< T > temp( proxy.lhs() );
            m_mult( temp, proxy.rhs(), lhs, MagmaNoTrans, MagmaNoTrans, 
                    T( 1 ), T ( 1 ) );
        }
    };
    // C += t( A ) * t( B )
    template< typename T >
    class OpExecutor< Matrix< T >, M_INPLACE_ADD, MatrixExpression<
    const MatrixExpression< const Matrix< T >, const Matrix< T >, M_TRANS >,
    const MatrixExpression< const Matrix< T >, const Matrix< T >, M_TRANS >,
    M_MULT > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression<
    const MatrixExpression< const Matrix< T >, const Matrix< T >, M_TRANS >,
    const MatrixExpression< const Matrix< T >, const Matrix< T >, M_TRANS >,
    M_MULT >& proxy ) {
            if( aliasing( lhs, proxy ) ) {
                Matrix< T > temp( proxy );
                lhs += temp;
            } else {
                m_mult( proxy.lhs(), proxy.rhs(), lhs, MagmaTrans, MagmaTrans,
                        T( 1 ), T( 1 ) );
            }
        }
    };
    // C += expression( A ) * expression( B )
    template< typename T,
            typename LL, typename LR, Oper LO,
            typename RL, typename RR, Oper RO >
    class OpExecutor< Matrix< T >, 
            M_INPLACE_ADD,
            MatrixExpression< const MatrixExpression< const LL, const LR, LO >,
            const MatrixExpression< const RL, const RR, RO >,
            M_MULT > > {
    public: 
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                const MatrixExpression< const LL, const LR, LO >,
                const MatrixExpression< const RL, const RR, RO >, M_MULT >& 
            proxy ) {
            Matrix< T > temp1( proxy.lhs() );
            Matrix< T > temp2( proxy.rhs() );
            m_mult( temp1, temp2, lhs, MagmaNoTrans, MagmaNoTrans, 
                    T( 1 ), T( 1 ) );
        }
    };
    // C -= A * B
    template< typename T >
    class OpExecutor< Matrix< T >, M_INPLACE_SUB, MatrixExpression<
    const Matrix< T >, const Matrix< T >, M_MULT > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression<
        const Matrix< T >, const Matrix< T >, M_MULT >& proxy ) {
            if( aliasing( lhs, proxy ) ) {
                Matrix< T > temp( proxy );
                lhs -= temp;
            } else {
                m_mult( proxy.lhs(), proxy.rhs(), lhs, 
                        MagmaNoTrans, MagmaNoTrans, T ( - 1 ), T( 1 ) );
            }
        }
    };
    // C -= A * t( B )
    template< typename T >
    class OpExecutor< Matrix< T >, M_INPLACE_SUB, MatrixExpression<
    const Matrix< T >, const MatrixExpression< const Matrix< T >, 
            const Matrix< T >, M_TRANS >, M_MULT > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression<
    const Matrix< T >, const MatrixExpression< const Matrix< T >, 
            const Matrix< T >, M_TRANS >, M_MULT >& proxy ) {
            if( aliasing( lhs, proxy ) ) {
                Matrix< T > temp( proxy );
                lhs -= temp;
            } else {
                m_mult( proxy.lhs(), proxy.rhs().lhs(), lhs,
                        MagmaNoTrans, MagmaTrans, T( - 1 ), T( 1 ) );
            }
        }
    };
    // C -= A * expression( B )
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_INPLACE_SUB,  
            MatrixExpression< const Matrix< T >, 
            const MatrixExpression< const L, const R, O >,
            M_MULT > > {
    public:
        static void apply( Matrix< T >& lhs,
                 const MatrixExpression< const Matrix< T >, 
            const MatrixExpression< const L, const R, O >,
            M_MULT >& proxy ) {
            Matrix< T > temp( proxy.rhs() );
            m_mult( proxy.lhs(), temp, lhs, MagmaNoTrans, MagmaNoTrans, 
                    T( - 1 ), T( 1 ) );
        }
    };
    // C -= t( A ) * B
    template< typename T >
    class OpExecutor< Matrix< T >, M_INPLACE_SUB, MatrixExpression<
    const MatrixExpression< const Matrix< T >, 
            const Matrix< T >, M_TRANS >,
    const Matrix< T >, M_MULT > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression<
    const MatrixExpression< const Matrix< T >, 
            const Matrix< T >, M_TRANS >,
    const Matrix< T >, M_MULT >& proxy ) {
            if( aliasing( lhs, proxy ) ) {
                Matrix< T > temp( proxy );
                lhs -= temp;
            } else {
                m_mult( proxy.lhs().lhs(), proxy.rhs(), lhs,
                        MagmaTrans, MagmaNoTrans, T( - 1 ), T( 1 ) );
            }
        }
    };
    // C -= expression( A ) * B
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_INPLACE_SUB,  
            MatrixExpression< const MatrixExpression< const L, const R, O >,
            const Matrix< T >, M_MULT > > {
    public:
        static void apply( Matrix< T >& lhs,
                 const MatrixExpression< const MatrixExpression< const L, const R, O >,
            const Matrix< T >, M_MULT >& proxy ) {
            Matrix< T > temp( proxy.lhs() );
            m_mult( temp, proxy.rhs(), lhs, MagmaNoTrans, MagmaNoTrans, 
                    T( - 1 ), T ( 1 ) );
        }
    };
    // C -= t( A ) * t( B )
    template< typename T >
    class OpExecutor< Matrix< T >, M_INPLACE_SUB, MatrixExpression<
    const MatrixExpression< const Matrix< T >, const Matrix< T >, M_TRANS >,
    const MatrixExpression< const Matrix< T >, const Matrix< T >, M_TRANS >,
    M_MULT > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression<
    const MatrixExpression< const Matrix< T >, const Matrix< T >, M_TRANS >,
    const MatrixExpression< const Matrix< T >, const Matrix< T >, M_TRANS >,
    M_MULT >& proxy ) {
            if( aliasing( lhs, proxy ) ) {
                Matrix< T > temp( proxy );
                lhs -= temp;
            } else {
                m_mult( proxy.lhs(), proxy.rhs(), lhs, MagmaTrans, MagmaTrans,
                        T( - 1 ), T( 1 ) );
            }
        }
    };
    // C -= expression( A ) * expression( B )
    template< typename T,
            typename LL, typename LR, Oper LO,
            typename RL, typename RR, Oper RO >
    class OpExecutor< Matrix< T >, 
            M_INPLACE_SUB,
            MatrixExpression< const MatrixExpression< const LL, const LR, LO >,
            const MatrixExpression< const RL, const RR, RO >,
            M_MULT > > {
    public: 
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                const MatrixExpression< const LL, const LR, LO >,
                const MatrixExpression< const RL, const RR, RO >, M_MULT >& 
            proxy ) {
            Matrix< T > temp1( proxy.lhs() );
            Matrix< T > temp2( proxy.rhs() );
            m_mult( temp1, temp2, lhs, MagmaNoTrans, MagmaNoTrans, 
                    T( - 1 ), T( 1 ) );
        }
    };
    // 3593
}


#endif /* XMAGMA_OPERATIONS_H */

