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
#include "xmagma_vector_expression.h"
namespace xmagma{
    /* Communicate */
    // Copy matrix 
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
    // Copy vector
    template< VecType M1, VecType M2 > 
    void copy_vector( const Vector< float, M1 >& v1, 
            Vector< float, M2 >& v2 ){
        magma_scopyvector( v1.size(), v1.get_pointer(), 1,
                v2.get_pointer(), 1,
                Backend::get_queue() );
    }
    template< VecType M1, VecType M2 > 
    void copy_vector( const Vector< double, M1 >& v1, 
            Vector< double, M2 >& v2 ){
        magma_dcopyvector( v1.size(), v1.get_pointer(), 1,
                v2.get_pointer(), 1,
                Backend::get_queue() );
    }
    // Transfer matrix from host to device
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
    // Transfer vector from host to device
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
    // Transfer matrix from device to host 
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
    // Transfer vector from device to host
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
    // inverse
    void inv( Matrix< float >& A ) {
        magma_int_t ldwork, *ipiv, info;
        magmaFloat_ptr dwork;
        magma_imalloc_cpu( &ipiv, A.size1() );
        ldwork = A.size1() * magma_get_sgetri_nb( A.size1() );
        magma_smalloc( &dwork,  ldwork );
        magma_sgetrf_gpu( A.size1(), A.size1(), A.get_pointer(), 
                A.ld(), ipiv, &info );
        magma_sgetri_gpu( A.size1(), A.get_pointer(), 
                A.ld(), ipiv, dwork, ldwork, &info );
        magma_free_cpu( ipiv );
        magma_free( dwork );
    }
    void inv( Matrix< double >& A ) {
        magma_int_t ldwork, *ipiv, info;
        magmaDouble_ptr dwork;
        magma_imalloc_cpu( &ipiv, A.size1() );
        ldwork = A.size1() * magma_get_dgetri_nb( A.size1() );
        magma_dmalloc( &dwork,  ldwork );
        magma_dgetrf_gpu( A.size1(), A.size1(), A.get_pointer(), 
                A.ld(), ipiv, &info );
        magma_dgetri_gpu( A.size1(), A.get_pointer(), 
                A.ld(), ipiv, dwork, ldwork, &info );
        magma_free_cpu( ipiv );
        magma_free( dwork );
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
    // inplace add vector
    // y = a * x + y
    template< VecType M >
    void inplace_add( Vector< float, M >& y, const Vector< float, M >& x,
            float a ) {
        magma_saxpy( y.size(), a, x.get_pointer(), 1, 
                y.get_pointer(), 1, Backend::get_queue() );
    }
    template< VecType M >
    void inplace_add( Vector< double, M >& y, const Vector< double, M >& x,
            double a ) {
        magma_daxpy( y.size(), a, x.get_pointer(), 1, 
                y.get_pointer(), 1, Backend::get_queue() );
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
    // y = A * x
    template< VecType M >
    void mv_mult( const Matrix< float >& A, const Vector< float, M >& x,
            Vector< float, M >& y, magma_trans_t transA, 
            float a, float b ) {
        magmablas_sgemv( transA, A.size1(), A.size2(), a, A.get_pointer(),
                A.ld(), x.get_pointer(), 1, b, y.get_pointer(), 1, Backend::get_queue() );
    }
    template< VecType M >
    void mv_mult( const Matrix< double >& A, const Vector< double, M >& x,
            Vector< double, M >& y, magma_trans_t transA, 
            double a, double b ) {
        magmablas_dgemv( transA, A.size1(), A.size2(), a, A.get_pointer(),
                A.ld(), x.get_pointer(), 1, b, y.get_pointer(), 1, Backend::get_queue() );
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
    // set all elements of a vector to be a constant value
    template< VecType M >
    void set_const(  Vector< float, M >& v, float a ) {
        magmablas_slaset( MagmaFull, v.size1(), 1, a, a, v.get_pointer(),
                v.size1(), Backend::get_queue() );
    }
    template< VecType M >
    void set_const(  Vector< double, M >& v, double a ) {
        magmablas_dlaset( MagmaFull, v.size1(), 1, a, a, v.get_pointer(),
                v.size1(), Backend::get_queue() );
    }
    // scale
    // scale matrix
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
    // scale vector
    template< VecType M >
    void scale( Vector< float, M >& x, float a ) {
        magma_sscal( x.size(), a, x.get_pointer(), 1, Backend::get_queue() );
    }
    template< VecType M >
    void scale( Vector< double, M >& x, double a ) {
        magma_dscal( x.size(), a, x.get_pointer(), 1, Backend::get_queue() );
    }
    // vector inner product: x * y
    template< VecType M1, VecType M2 >
    void v_inner( const Vector< float, M1 >& x, 
            const Vector< float, M2 >& y, float& p ) {
        magma_sdot( x.size(), x.get_pointer(), 1, y.get_pointer(), 1, 
                Backend::get_queue() );
    }
    template< VecType M1, VecType M2 >
    void v_inner( const Vector< double, M1 >& x, 
            const Vector< double, M2 >& y, double& p ) {
        p = magma_ddot( x.size(), x.get_pointer(), 1, y.get_pointer(), 1, 
                Backend::get_queue() );
    }
    // x inner y
    template< typename T >
    T operator*( const Vector< T, ROW>& x, const Vector< T, COL >& y ) {
       T p;
       v_inner( x, y, p );
       return p;
    }
    // expression( x ) inner y
    template< typename T, typename L, typename R, Oper O >
    T operator*( const VectorExpression< const T, const L , const R, O, ROW >& x,
            const Vector< T, COL >& y ) {
        T p;
        Vector< T, ROW > temp( x );
        v_inner( temp, y, p );
        return p;
    }
    // x inner expression( y )
    template< typename T, typename L, typename R, Oper O >
    T operator*( const Vector< T, ROW >& x, 
            const VectorExpression< const T, const L , const R, O, COL >& y ) {
        T p;
        Vector< T, COL > temp( y );
        v_inner( x, temp, p );
        return p;
    }
    // expression( x ) inner expression( y )
    template< typename T, typename L1, typename R1, Oper O1,
            typename L2, typename R2, Oper O2 >
    T operator*( const VectorExpression< const T, const L1 , const R1, O1, ROW >& x,
            const VectorExpression< const T, const L2 , const R2, O2, COL >& y ) {
        T p;
        Vector< T, ROW > temp1( x );
        Vector< T, COL > temp2( y );
        v_inner( temp1, temp2, p );
        return p;
    }
    // outer product
    template< VecType M1, VecType M2 >
    void v_outer( const Vector< float, M1 >& x, const Vector< float, M2 >& y,
            Matrix< float >& A, float a = 1 ) {
        magma_sger( x.size(), y.size(), a, x.get_pointer(), 1, y.get_pointer(), 
                1, A.get_pointer(), A.ld(), Backend::get_queue() );
    }
    template< VecType M1, VecType M2 >
    void v_outer( const Vector< double, M1 >& x, const Vector< double, M2 >& y,
            Matrix< double >& A, double a = 1 ) {
        magma_dger( x.size(), y.size(), a, x.get_pointer(), 1, y.get_pointer(), 
                1, A.get_pointer(), A.ld(), Backend::get_queue() );
    }
    /* Matrix expressions */
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
    template< typename T >
    MatrixExpression< const Matrix< T >, const int,  M_SCALE >
    operator*( const Matrix< T >& A, const int& a ) {
        return MatrixExpression< const Matrix< T >, const int, M_SCALE >
                ( A,  a );
    }
    template< typename T >
    MatrixExpression< const Matrix< T >, const float,  M_SCALE >
    operator*( const Matrix< T >& A, const float& a ) {
        return MatrixExpression< const Matrix< T >, const float, M_SCALE >
                ( A,  a );
    }
    template< typename T >
    MatrixExpression< const Matrix< T >, const double,  M_SCALE >
    operator*( const Matrix< T >& A, const double& a ) {
        return MatrixExpression< const Matrix< T >, const double, M_SCALE >
                ( A,  a );
    }
    // expression( A ) * a;
    template< typename L, typename R, Oper O >
    MatrixExpression< const MatrixExpression< const L, const R, O >,
            const int, M_SCALE >
    operator*( const MatrixExpression< const L, const R, O >& proxy, 
            const int& a ) {
        return MatrixExpression< const MatrixExpression< const L, const R, O >,
            const int, M_SCALE >( proxy,  a );
    }
    template< typename L, typename R, Oper O >
    MatrixExpression< const MatrixExpression< const L, const R, O >,
            const float, M_SCALE >
    operator*( const MatrixExpression< const L, const R, O >& proxy, 
            const float& a ) {
        return MatrixExpression< const MatrixExpression< const L, const R, O >,
            const float, M_SCALE >( proxy,  a );
    }
    template< typename L, typename R, Oper O >
    MatrixExpression< const MatrixExpression< const L, const R, O >,
            const double, M_SCALE >
    operator*( const MatrixExpression< const L, const R, O >& proxy, 
            const double& a ) {
        return MatrixExpression< const MatrixExpression< const L, const R, O >,
            const double, M_SCALE >( proxy,  a );
    }
    // a * A = A * a
    template< typename T >
    MatrixExpression< const Matrix< T >, const int,  M_SCALE >
    operator*( const int& a, const Matrix< T >& A ) {
        return MatrixExpression< const Matrix< T >, const int,  M_SCALE >( A, a );
    }
    template< typename T >
    MatrixExpression< const Matrix< T >, const float,  M_SCALE >
    operator*( const float& a, const Matrix< T >& A ) {
        return MatrixExpression< const Matrix< T >, const float,  M_SCALE >( A, a );
    }
    template< typename T >
    MatrixExpression< const Matrix< T >, const double,  M_SCALE >
    operator*( const double& a, const Matrix< T >& A ) {
        return MatrixExpression< const Matrix< T >, const double,  M_SCALE >( A, a );
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
    template< typename T >
    MatrixExpression< const MatrixExpression< const Vector< T, COL >, 
            const Vector< T, COL >, V_OUTER >, const int, M_SCALE >
    operator*=( const MatrixExpression< const Vector< T, COL >,
            const Vector< T, COL >, V_OUTER >&
    proxy, const int& a ) {
        return MatrixExpression< const MatrixExpression< const Vector< T, COL >, 
            const Vector< T, COL >, V_OUTER >, const int, M_SCALE >( proxy, a );
    }
    template< typename T >
    MatrixExpression< const MatrixExpression< const Vector< T, COL >, 
            const Vector< T, COL >, V_OUTER >, const float, M_SCALE >
    operator*=( const MatrixExpression< const Vector< T, COL >,
            const Vector< T, COL >, V_OUTER >&
    proxy, const float& a ) {
        return MatrixExpression< const MatrixExpression< const Vector< T, COL >, 
            const Vector< T, COL >, V_OUTER >, const float, M_SCALE >( proxy, a );
    }
    template< typename T >
    MatrixExpression< const MatrixExpression< const Vector< T, COL >, 
            const Vector< T, COL >, V_OUTER >, const double, M_SCALE >
    operator*=( const MatrixExpression< const Vector< T, COL >,
            const Vector< T, COL >, V_OUTER >&
    proxy, const double& a ) {
        return MatrixExpression< const MatrixExpression< const Vector< T, COL >, 
            const Vector< T, COL >, V_OUTER >, const double, M_SCALE >( proxy, a );
    }
    // a * expression( v1  * t( v2 ) )
    template< typename T >
    MatrixExpression< const MatrixExpression< const Vector< T, COL >, 
            const Vector< T, COL >, V_OUTER >, const int, M_SCALE >
    operator*=( const int& a, const MatrixExpression< const Vector< T, COL >,
            const Vector< T, COL >, V_OUTER >&
    proxy ) {
        return proxy * a;
    }
    template< typename T >
    MatrixExpression< const MatrixExpression< const Vector< T, COL >, 
            const Vector< T, COL >, V_OUTER >, const float, M_SCALE >
    operator*=( const float& a, const MatrixExpression< const Vector< T, COL >,
            const Vector< T, COL >, V_OUTER >&
    proxy ) {
        return proxy * a;
    }
    template< typename T >
    MatrixExpression< const MatrixExpression< const Vector< T, COL >, 
            const Vector< T, COL >, V_OUTER >, const double, M_SCALE >
    operator*=( const double& a, const MatrixExpression< const Vector< T, COL >,
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
    template< typename LL, typename LR, Oper LO,
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
    // solve( A ): inverse of A
    template< typename T >
    MatrixExpression< const Matrix< T >, const Matrix< T >, M_INV >
    solve( const Matrix< T >& A ) {
        return MatrixExpression< const Matrix< T >, const Matrix< T >,
                M_INV >( A, A );
    }
    // solve( expression( A ) )
    template< typename L, typename R, Oper O >
    MatrixExpression< const MatrixExpression< const L, const R, O >,
            const MatrixExpression< const L, const R, O >, M_INV > 
    solve( const MatrixExpression< const L, const R, O >& proxy ) {
        return MatrixExpression< const MatrixExpression< const L, const R,
                O >, const MatrixExpression< const L, const R, O >, M_INV >
                ( proxy, proxy );
    }
    /* Vector expressions */
    // expression( x ) + expression( y )
    template< typename T, typename L1, typename R1, Oper O1, VecType M,
            typename L2, typename R2, Oper O2 >
    VectorExpression< const T, const VectorExpression< const T, const L1, const R1, O1, M >,
            const VectorExpression< const T, const L2, const R2, O2, M >, V_ADD, M >
    operator+( const VectorExpression< const T, const L1, const R1, O1, M >& x, 
            const VectorExpression< const T, const L2, const R2, O2, M >& y ) {
        assert( x.size1() == y.size1() &&
            bool( "Vectors have different lengths" ) );
        return VectorExpression< const T, const VectorExpression< const T, const L1, const R1, O1, M >,
            const VectorExpression< const T, const L2, const R2, O2, M >, V_ADD, M >
                ( x, y );
    }
    // expression( x ) + y
    template< typename L, typename R, Oper O, VecType M, typename T >
    VectorExpression< const T, const VectorExpression< const T, const L, const R, O, M >,
            const Vector< T, M >, V_ADD, M >
    operator+( const VectorExpression< const T, const L, const R, O, M >& x, 
            const Vector< T, M >& y ) {
        assert( x.size1() == y.size1() && 
            bool( "Vectors have different lengths" ) );
        return VectorExpression< const T, const VectorExpression< const T, const L, 
                const R, O, M >, 
                const Vector< T, M >, V_ADD, M>( x, y );
    }
    // x + expression( y ) = expression( y ) + x
    template< typename L, typename R, Oper O, VecType M, typename T >
    VectorExpression< const T, const VectorExpression< const T, const L, const R, O, M >,
            const Vector< T, M >, V_ADD, M >
    operator+( const Vector< T, M >& y,
            const VectorExpression< const T, const L, const R, O, M >& x ) {
        assert( x.size1() == y.size1() && 
            bool( "Vectors have different lengths" ) );
        return VectorExpression< const T, const VectorExpression< const T, const L, 
                const R, O, M >, 
                const Vector< T, M >, V_ADD, M>( x, y );
    }
    // x + y
    template< typename T, VecType M >
    VectorExpression< const T, const Vector< T, M >, const Vector< T, M >, V_ADD, M >
    operator+( const Vector< T, M >& x, const Vector< T, M >& y ) {
        return VectorExpression< const T, const Vector< T, M >, 
                const Vector< T, M >, V_ADD, M >( x, y );
    }
    // expression( x ) - expression( y )
    template< typename T, typename L1, typename R1, Oper O1, VecType M,
            typename L2, typename R2, Oper O2 >
    VectorExpression< const T, const VectorExpression< const T, const L1, const R1, O1, M >,
            const VectorExpression< const T, const L2, const R2, O2, M >, V_SUB, M >
    operator-( const VectorExpression< const T, const L1, const R1, O1, M >& x, 
            const VectorExpression< const T, const L2, const R2, O2, M >& y ) {
        assert( x.size1() == y.size1() &&
            bool( "Vectors have different lengths" ) );
        return VectorExpression< const T, const VectorExpression< const T, const L1, const R1, O1, M >,
            const VectorExpression< const T, const L2, const R2, O2, M >, V_SUB, M >
                ( x, y );
    }
    // expression( x ) - y
    template< typename L, typename R, Oper O, VecType M, typename T >
    VectorExpression< const T, const VectorExpression< const T, const L, const R, O, M >,
            const Vector< T, M >, V_SUB, M >
    operator-( const VectorExpression< const T, const L, const R, O, M >& x, 
            const Vector< T, M >& y ) {
        assert( x.size1() == y.size1() && 
            bool( "Vectors have different lengths" ) );
        return VectorExpression< const T, const VectorExpression< const T, const L, 
                const R, O, M >, 
                const Vector< T, M >, V_SUB, M>( x, y );
    }
    // x - expression( y )
    template< typename L, typename R, Oper O, VecType M, typename T >
    VectorExpression< const T, const Vector< T, M >,
            const VectorExpression< const T, const L, const R, O, M >,
            V_SUB, M >
    operator-( const Vector< T, M >& x, 
            const VectorExpression< const T, const L, const R, O, M >& y ) {
        return VectorExpression< const T, const Vector< T, M >,
                const VectorExpression< const T, const L, const R, O, M >,
                V_SUB, M >( x, y );
    }
    // x - y
    template< typename T, VecType M >
    VectorExpression< const T, const Vector< T, M >, const Vector< T, M >, V_SUB, M >
    operator-( const Vector< T, M >& x, const Vector< T, M >& y ) {
        return VectorExpression< const T, const Vector< T, M >, const Vector< T, M >,
                V_SUB, M >( x, y ); 
    }
    // scale: x * a
    template< typename T, VecType M >
    VectorExpression< const T, const Vector< T, M >, const int, V_SCALE, M >
    operator*( const Vector< T, M >& x, const int& a ) {
        return VectorExpression< const T, const Vector< T, M >, const int, V_SCALE, M >
                ( x, a );
    }
    template< typename T, VecType M >
    VectorExpression< const T, const Vector< T, M >, const float, V_SCALE, M >
    operator*( const Vector< T, M >& x, const float& a ) {
        return VectorExpression< const T, const Vector< T, M >, const float, V_SCALE, M >
                ( x, a );
    }
    template< typename T, VecType M >
    VectorExpression< const T, const Vector< T, M >, const double, V_SCALE, M >
    operator*( const Vector< T, M >& x, const double& a ) {
        return VectorExpression< const T, const Vector< T, M >, const double, V_SCALE, M >
                ( x, a );
    }
    // expression( x ) * a;
    template< typename T, typename L, typename R, Oper O, VecType M >
    VectorExpression< const T, const VectorExpression< const T, const L, const R, O, M >,
            const int, V_SCALE, M >
    operator*( const VectorExpression< const T, const L, const R, O, M >& proxy, 
            const int& a ) {
        return VectorExpression< const T, const VectorExpression< const T, const L, 
                const R, O, M >,
            const int, V_SCALE, M >( proxy,  a );
    }
    template< typename T, typename L, typename R, Oper O, VecType M >
    VectorExpression< const T, const VectorExpression< const T, const L, const R, O, M >,
            const float, V_SCALE, M >
    operator*( const VectorExpression< const T,const L, const R, O, M >& proxy, 
            const float& a ) {
        return VectorExpression< const T, const VectorExpression< const T, const L, 
                const R, O, M >,
            const float, V_SCALE, M >( proxy,  a );
    }
    template< typename T, typename L, typename R, Oper O, VecType M >
    VectorExpression< const T, const VectorExpression< const T, const L, const R, O, M >,
            const double, V_SCALE, M >
    operator*( const VectorExpression< const T, const L, const R, O, M >& proxy, 
            const double& a ) {
        return VectorExpression< const T, const VectorExpression< const T, const L, 
                const R, O, M >,
            const double, V_SCALE, M >( proxy,  a );
    }
    // a * x = x * a
    template< typename T, VecType M >
    VectorExpression< const T, const Vector< T, M >, const int, V_SCALE, M >
    operator*( const int& a, const Vector< T, M >& x ) {
        return VectorExpression< const T, const Vector< T, M >, const int, V_SCALE, M >
                ( x, a );
    }
    template< typename T, VecType M >
    VectorExpression< const T, const Vector< T, M >, const float, V_SCALE, M >
    operator*( const float& a, const Vector< T, M >& x ) {
        return VectorExpression< const T, const Vector< T, M >, const float, V_SCALE, M >
                ( x, a );
    }
    template< typename T, VecType M >
    VectorExpression< const T, const Vector< T, M >, const double, V_SCALE, M >
    operator*( const double& a, const Vector< T, M >& x ) {
        return VectorExpression< const T, const Vector< T, M >, const double, V_SCALE, M >
                ( x, a );
    }
    // a * expression( x );
    template< typename T, typename L, typename R, Oper O, VecType M >
    VectorExpression< const T, const VectorExpression< const T, const L, const R, O, M >,
            const int, V_SCALE, M >
    operator*( const int& a, 
            const VectorExpression< const T, const L, const R, O, M >& proxy
             ) {
        return VectorExpression< const T, const VectorExpression< const T, const L, 
                const R, O, M >,
            const int, V_SCALE, M >( proxy,  a );
    }
    template< typename T, typename L, typename R, Oper O, VecType M >
    VectorExpression< const T, const VectorExpression< const T, const L, const R, O, M >,
            const float, V_SCALE, M >
    operator*( const float& a, 
            const VectorExpression< const T, const L, const R, O, M >& proxy
             ) {
        return VectorExpression< const T, const VectorExpression< const T, const L, 
                const R, O, M >,
            const float, V_SCALE, M >( proxy,  a );
    }
    template< typename T, typename L, typename R, Oper O, VecType M >
    VectorExpression< const T, const VectorExpression< const T, const L, const R, O, M >,
            const double, V_SCALE, M >
    operator*( const double& a, 
            const VectorExpression< const T, const L, const R, O, M >& proxy
             ) {
        return VectorExpression< const T, const VectorExpression< const T, const L, 
                const R, O, M >,
            const double, V_SCALE, M >( proxy,  a );
    }
    // -x
    template< typename T, VecType M >
    VectorExpression< const T, const Vector< T, M >, const Vector< T, M >, V_NEGATIVE,
            M >
    Vector< T, M >::operator-() const {
        return VectorExpression< const T, const SelfType, const SelfType,
                V_NEGATIVE, M >( *this, *this );
    }
    // x / a = x * ( 1 / a )
    template< typename T, typename S, VecType M >
    VectorExpression< const T, const Vector< T, M >, const S, V_DIV, M >
    operator/( const Vector< T, M >& x, const S& a ) {
        assert( a != 0 
                && bool( "Divided by zero!" ) );
        return VectorExpression< const T, const Vector< T, M >, const S, V_DIV, M >
                ( x, a );
    }
    // expression( x ) / a
    template< typename T, typename L, typename R, Oper O, typename S, VecType M >
    VectorExpression< const T, const VectorExpression< const T, const L, const R, O, M >,
            const S, V_DIV, M >
    operator/( const VectorExpression< const T, const L, const R, O, M >& x,
            const S& a ) {
        assert( a != 0 
                && bool( "Divided by zero!" ) );
        return VectorExpression< const T, const VectorExpression< const T, const L, 
                const R, O, M >, const S, V_DIV, M >( x, a );
    }
    // t( x ) (col vector)
    template< typename T >
    VectorExpression< const T, const Vector< T, COL >, const Vector< T, COL >, V_TRANS,
            ROW >
    t( const Vector< T, COL >& x ) {
        return VectorExpression< const T, const Vector< T, COL >, 
                const Vector< T, COL >, V_TRANS,
            ROW >( x, x );
    }
    // t( x ) (row vector)
    template< typename T >
    VectorExpression< const T, const Vector< T, ROW >, const Vector< T, ROW >, V_TRANS,
            COL >
    t( const Vector< T, ROW >& x ) {
        return VectorExpression< const T, const Vector< T, ROW >, 
                const Vector< T, ROW >, V_TRANS,
            COL >( x, x );
    }
    // t( expression( x ) ) (col vector)
    template< typename T, typename L, typename R, Oper O >
    VectorExpression< const T, const VectorExpression< const T, const L, const R, O, COL >, 
            const VectorExpression< const T, const L, const R, O, COL >, V_TRANS,
            ROW >
    t( const VectorExpression< const T, const L, const R, O, COL >& x ) {
        return VectorExpression< const T, const VectorExpression< const T, const L, const R,
                O, COL >, 
            const VectorExpression< const T, const L, const R, O, COL >, V_TRANS,
            ROW >( x, x );
    }
    // t( expression( x ) ) (row vector)
    template< typename T, typename L, typename R, Oper O >
    VectorExpression< const T, const VectorExpression< const T, const L, const R, O, ROW >, 
            const VectorExpression< const T, const L, const R, O, ROW >, V_TRANS,
            COL >
    t( const VectorExpression< const T, const L, const R, O, ROW >& x ) {
        return VectorExpression< const T, const VectorExpression< const T, const L, const R,
                O, ROW >, 
            const VectorExpression< const T, const L, const R, O, ROW >, V_TRANS,
            COL >( x, x );
    }
    // x * t( y ) 
    template< typename T >
    MatrixExpression< const Vector< T, COL >, const Vector< T, COL >, V_OUTER >
    operator*( const Vector< T, COL >& x, const VectorExpression< const T,
        const Vector< T, COL >, const Vector< T, COL >, V_TRANS, ROW>& y ) {
        return MatrixExpression< const Vector< T, COL >, 
                const Vector< T, COL >, V_OUTER >( x, y.lhs() );
    }
    // expression( x ) * t( y )
    template< typename T, typename L, typename R, Oper O >
    MatrixExpression< const VectorExpression< const T, const L, const R, O, COL >,
            const Vector< T, COL >, V_OUTER >
    operator*( const VectorExpression< const T, const L, const R, O, COL >& x,
            const VectorExpression< const T, const Vector< T, COL >, 
            const Vector< T, COL >, V_TRANS, ROW >& y ) {
        return MatrixExpression< const VectorExpression< const T, const L, 
                const R, O, COL >, const Vector< T, COL >, V_OUTER >( x, y.lhs() );
    }
    // x * t( expression( y ) )
    template< typename T, typename L, typename R, Oper O >
    MatrixExpression< const Vector< T, COL >, const VectorExpression< const T, const L,
            const R, O, COL >, V_OUTER >
    operator*( const Vector< T, COL >& x, const VectorExpression< const T,
        const VectorExpression< const T, const L, const R, O, COL >, 
            const VectorExpression< const T, const L, const R, O, COL >, V_TRANS, ROW>& y ) {
        return MatrixExpression< const Vector< T, COL >, 
                const VectorExpression< const T, const L, const R, O, COL >, V_OUTER >( x, y.lhs() );
    }
    // expression( x ) * t( expression( y ) )
    template< typename T, typename L1, typename R1, Oper O1,
            typename L2, typename R2, Oper O2 >
    MatrixExpression< const VectorExpression< const T, const L1, const R1, O1, COL >, 
            const VectorExpression< const T, const L2,
            const R2, O2, COL >, V_OUTER >
    operator*( const VectorExpression< const T, const L1, const R1, O1, COL >& x,
            const VectorExpression< const T,
        const VectorExpression< const T, const L2, const R2, O2, COL >, 
            const VectorExpression< const T, const L2, const R2, O2, COL >, V_TRANS, ROW>& y ) {
        return MatrixExpression< const VectorExpression< const T, const L1, const R1, O1, COL >, 
                const VectorExpression< const T, const L2, const R2, O2, COL >, 
                V_OUTER >( x, y.lhs() );
    }

    // x * y (COL * ROW)
    template< typename T >
    MatrixExpression< const Vector< T, COL >, const Vector< T, ROW >, V_OUTER >
    operator*( const Vector< T, COL >& x, const Vector< T, ROW >& y ) {
        return MatrixExpression< const Vector< T, COL >, 
                const Vector< T, ROW >, V_OUTER >( x, y );
    }
    // expression( x ) * y (COL * ROW)
    template< typename T, typename L, typename R, Oper O >
    MatrixExpression< const VectorExpression< const T, const L, const R, O, COL >, 
            const Vector< T, ROW >, V_OUTER >
    operator*( const VectorExpression< const T, const L, const R, O, COL >& x, 
            const Vector< T, ROW >& y ) {
        return MatrixExpression< const VectorExpression< const T, const L, 
                const R, O, COL >, 
                const Vector< T, ROW >, V_OUTER >( x, y );
    }
    // x * expression( y ) (COL * ROW)
    template< typename T, typename L, typename R, Oper O >
    MatrixExpression< const Vector< T, COL >, 
            const VectorExpression< const T, const L, const R, O, ROW >, 
            V_OUTER >
    operator*( const Vector< T, COL >& x, 
            const VectorExpression< const T, const L, const R, O, ROW >& y ) {
        return MatrixExpression< const Vector< T, COL >, 
            const VectorExpression< const T, const L, const R, O, ROW >, 
            V_OUTER >( x, y );
    }
    // expression( x ) * expression( y ) (COL * ROW)
    template< typename T, typename L1, typename R1, Oper O1,
            typename L2, typename R2, Oper O2 >
    MatrixExpression< const VectorExpression< const T, const L1, const R1, O1, COL >, 
            const VectorExpression< const T, const L2, const R2, O2, ROW >, 
            V_OUTER >
    operator*( const VectorExpression< const T, const L1, const R1, O1, COL >& x, 
            const VectorExpression< const T, const L2, const R2, O2, ROW >& y ) {
        return MatrixExpression< const VectorExpression< const T, const L1, 
                const R1, O1, COL >, 
            const VectorExpression< const T, const L2, const R2, O2, ROW >, 
            V_OUTER >( x, y );
    }
    /* OpExecutor for vector */
    // y = t( expression( x ) )
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Vector< T, COL >, V_ASSIGN, VectorExpression< const T,
        const VectorExpression< const T, const L, const R, O, ROW >,
        const VectorExpression< const T, const L, const R, O, ROW >, V_TRANS, COL> > {
    public:
        static void apply( Vector< T, COL >& y, const VectorExpression< const T,
        const VectorExpression< const T, const L, const R, O, ROW >,
        const VectorExpression< const T, const L, const R, O, ROW >, V_TRANS,
                COL >& x ) {
            Vector< T, ROW > temp( x.rhs() );
            y = t( temp );
        }
    };
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Vector< T, ROW >, V_ASSIGN, VectorExpression< const T,
        const VectorExpression< const T, const L, const R, O, COL >,
        const VectorExpression< const T, const L, const R, O, COL >, V_TRANS, ROW > > {
    public:
        static void apply( Vector< T, ROW >& y, const VectorExpression< const T,
        const VectorExpression< const T, const L, const R, O, COL >,
        const VectorExpression< const T, const L, const R, O, COL >, V_TRANS,
                ROW >& x ) {
            Vector< T, COL > temp( x.rhs() );
            y = t( temp );
        }
    };
    // y += x
    template< typename T, VecType M >
    class OpExecutor< Vector< T, M >, V_INPLACE_ADD,  Vector< T, M > > {
    public:
        static void apply( Vector< T, M >& lhs, const Vector< T, M >& rhs ) {
            lhs += rhs;
        }
    };
    // z = x ( expr ) + y ( expr )
    template< typename T, typename L, typename R, VecType M >
    class OpExecutor< Vector< T, M >, V_ASSIGN, VectorExpression< const T, const L, 
            const R, V_ADD, M > > {
    public:
        static void apply( Vector< T, M >& lhs, const VectorExpression< const T, const L, 
            const R, V_ADD, M >& proxy ) {
            if( aliasing( lhs, proxy ) ) {
                Vector< T, M > temp( proxy.lhs() );
                OpExecutor< Vector< T, M >, V_INPLACE_ADD, R >::apply( 
                temp, proxy.rhs());
                lhs = temp;
            } else {
                lhs = proxy.lhs();
                OpExecutor< Vector< T, M >, V_INPLACE_ADD, R >::apply( lhs,
                        proxy.rhs());
            }
        }
    };
    // y += trans( x )
    template< typename T >
    class OpExecutor< Vector< T, COL >, V_INPLACE_ADD, 
            VectorExpression< const T, const Vector< T, ROW >, 
                                         const Vector< T, ROW >, V_TRANS, COL > > {
    public:
        static void apply( Vector< T, COL >& lhs, const VectorExpression< const T,
        const Vector< T, ROW >,
                const Vector< T, ROW >, V_TRANS, COL >& rhs ) {
            Vector< T, COL >temp( t( rhs.rhs() ) );
            lhs += temp;
        }                                                                           
    };
    template< typename T >
    class OpExecutor< Vector< T, ROW >, V_INPLACE_ADD, 
            VectorExpression< const T, const Vector< T, COL >, 
                                         const Vector< T, COL >, V_TRANS, ROW > > {
    public:
        static void apply( Vector< T, ROW >& lhs, const VectorExpression< const T,
        const Vector< T, COL >,
                const Vector< T, COL >, V_TRANS, ROW >& rhs ) {
            Vector< T, ROW >temp( t( rhs.rhs() ) );
            lhs += temp;
        }                                                                           
    };
    // y += trans( expression( x ) )
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Vector< T, COL >, V_INPLACE_ADD, VectorExpression< const T,
    const VectorExpression< const T, const L, const R, O, ROW >, const VectorExpression< const T,
    const L, const R, O, ROW >, V_TRANS, COL > > {
    public:
        static void apply( Vector< T, COL >& lhs, const VectorExpression< const T,
    const VectorExpression< const T, const L, const R, O, ROW >, const VectorExpression< const T,
    const L, const R, O, ROW >, V_TRANS, COL >& rhs ) {
            Vector< T, ROW > temp1( rhs.rhs());
            Vector< T, COL > temp2( temp1.size1() );
            temp2 = t( temp1 );
            lhs += temp2;
        }
    };
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Vector< T, ROW >, V_INPLACE_ADD, VectorExpression< const T,
    const VectorExpression< const T, const L, const R, O, COL >, const VectorExpression< const T,
    const L, const R, O, COL >, V_TRANS, ROW > > {
    public:
        static void apply( Vector< T, ROW >& lhs, const VectorExpression< const T,
    const VectorExpression< const T, const L, const R, O, COL >, const VectorExpression< const T,
    const L, const R, O, COL >, V_TRANS, ROW >& rhs ) {
            Vector< T, COL > temp1( rhs.rhs());
            Vector< T, ROW > temp2( temp1.size1() );
            temp2 = t( temp1 );
            lhs += temp2;
        }
    };
    // y -= x
    template< typename T, VecType M >
    class OpExecutor< Vector< T, M >, V_INPLACE_SUB, Vector< T, M > > {
    public:
        static void apply( Vector< T, M >& lhs, const Vector< T, M >& rhs ) {
            lhs -= rhs;
        }
    };
    // y -= trans( x )
    template< typename T >
    class OpExecutor< Vector< T, COL >, V_INPLACE_SUB, VectorExpression< const T, 
    const Vector< T, ROW >, const Vector< T, ROW >, V_TRANS, COL > > {
    public:
        static void apply( Vector< T, COL >& lhs, const VectorExpression< const T, 
    const Vector< T, ROW >, const Vector< T, ROW >, V_TRANS, COL >& rhs ) {
            Vector< T, COL > temp( rhs );
            lhs -= temp;
        }
    };
    template< typename T >
    class OpExecutor< Vector< T, ROW >, V_INPLACE_SUB, VectorExpression< const T, 
    const Vector< T, COL>, const Vector< T, COL >, V_TRANS, ROW > > {
    public:
        static void apply( Vector< T, ROW >& lhs, const VectorExpression< const T, 
    const Vector< T, COL >, const Vector< T, COL >, V_TRANS, ROW >& rhs ) {
            Vector< T, ROW > temp( rhs );
            lhs -= temp;
        }
    };
    // y -= trans( expression( x ) )
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Vector< T, COL >, V_INPLACE_SUB,
            VectorExpression< const T, const VectorExpression< const T, const L, const R, O, ROW >,
            const VectorExpression< const T, const L, const R, O, ROW >, V_TRANS, COL > > {
    public:
        static void apply( Vector< T, COL >& lhs, const VectorExpression< const T,
        const VectorExpression< const T, const L, const R, O, ROW >,
            const VectorExpression< const T, const L, const R, O, ROW >,
                V_TRANS, COL >& rhs ) {
            Vector< T, ROW > temp1( rhs.rhs());
            Vector< T, COL > temp2( temp1.size1() );
            temp2 = t( temp1 );
            lhs -= temp2;
        }
    };
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Vector< T, ROW >, V_INPLACE_SUB,
            VectorExpression< const T, const VectorExpression< const T, const L, const R, O, COL >,
            const VectorExpression< const T, const L, const R, O, COL >, V_TRANS, ROW > > {
    public:
        static void apply( Vector< T, ROW >& lhs, const VectorExpression< const T,
        const VectorExpression< const T, const L, const R, O, COL >,
            const VectorExpression< const T, const L, const R, O, COL >,
                V_TRANS, ROW >& rhs ) {
            Vector< T, COL > temp1( rhs.rhs());
            Vector< T, ROW > temp2( temp1.size1() );
            temp2 = t( temp1 );
            lhs -= temp2;
        }
    };
    /*                        y Oper x * a                         */
    // y += x * alpha
    template< typename T, typename S, VecType M >
    class OpExecutor< Vector< T, M >, V_INPLACE_ADD, VectorExpression< const T, 
    const Vector< T, M >, const S, V_SCALE, M > > {
    public:
        static void apply( Vector< T, M >& lhs, const VectorExpression< const T, 
    const Vector< T, M >, const S, V_SCALE, M >& proxy ) {
                inplace_add( lhs, proxy.lhs(),  T( proxy.rhs() ) );
        }
    };
    // y += - x  
    template< typename T, VecType M >
    class OpExecutor< Vector< T, M >, V_INPLACE_ADD, VectorExpression< const T, 
    const Vector< T, M >, const Vector< T, M >, V_NEGATIVE, M> > {
    public:
        static void apply( Vector< T, M >& lhs, const VectorExpression< const T, 
    const Vector< T, M >, const Vector< T, M >, V_NEGATIVE, M>& proxy ) {
                inplace_add( lhs, proxy.lhs(),  T( - 1 )  );
        }
    };
    // y -= x * alpha
    template< typename T, typename S, VecType M >
    class OpExecutor< Vector< T, M >, V_INPLACE_SUB, VectorExpression< const T, 
    const Vector< T, M >, const S, V_SCALE, M > > {
    public:
        static void apply( Vector< T, M >& lhs, const VectorExpression< const T, 
    const Vector< T, M >, const S, V_SCALE, M >& proxy ) {
                inplace_add( lhs, proxy.lhs(),  - T( proxy.rhs() ) );
        }
    };
    // y -= - x 
    template< typename T, VecType M >
    class OpExecutor< Vector< T, M >, V_INPLACE_SUB, VectorExpression< const T, 
    const Vector< T, M >, const Vector< T, M >, V_NEGATIVE, M > > {
    public:
        static void apply( Vector< T, M >& lhs, const VectorExpression< const T, 
    const Vector< T, M >, const Vector< T, M >, V_NEGATIVE, M >& proxy ) {
                inplace_add( lhs, proxy.lhs(),  T( 1 ) );
        }
    };
    // y = x * a
    template< typename T, typename S, VecType M >
    class OpExecutor< Vector< T, M >, V_ASSIGN, VectorExpression< const T,
    const Vector< T, M >, const S, V_SCALE, M > > {
    public:
        static void apply( Vector< T, M >& lhs, const VectorExpression< const T,
    const Vector< T, M >, const S, V_SCALE, M >& proxy ) {
            if( aliasing( lhs, proxy ) ) {
                scale( lhs, T( proxy.rhs() ) );
            } else {
                lhs = 0;
                inplace_add( lhs, proxy.lhs(), T( proxy.rhs() ) );
            }
        }
    };
    // y = expression( x ) * a
    template< typename T, typename L, typename R, Oper O, typename S, 
            VecType M >
    class OpExecutor< Vector< T, M >, V_ASSIGN, VectorExpression< const T, 
    const VectorExpression< const T, const L, const R, O, M >, const S, V_SCALE, M > > {
    public:
        static void apply( Vector< T, M >& lhs, const VectorExpression< const T, 
    const VectorExpression< const T, const L, const R, O, M >, const S, V_SCALE, M >
        & proxy ) {
            Vector< T, M > temp( proxy.lhs() );
            lhs = temp * proxy.rhs();
        }
    };
    /*                        y Oper x / a                         */
    // y += x / alpha
    template< typename T, typename S, VecType M >
    class OpExecutor< Vector< T, M >, V_INPLACE_ADD, VectorExpression< const T, 
    const Vector< T, M >, const S, V_DIV, M > > {
    public:
        static void apply( Vector< T, M >& lhs, const VectorExpression< const T, 
    const Vector< T, M >, const S, V_DIV, M >& proxy ) {
                inplace_add( lhs, proxy.lhs(),  1 / T( proxy.rhs() ) );
        }
    };
    // y += expression( x ) / alpha
    template< typename T, typename S, typename L, typename R, Oper O, 
            VecType M >
    class OpExecutor< Vector< T, M >, V_INPLACE_ADD, VectorExpression< const T, 
    const VectorExpression< const T, const L, const R, O, M >, const S, V_DIV, M > > {
    public:
        static void apply( Vector< T, M >& lhs, const VectorExpression< const T, 
    const VectorExpression< const T, const L, const R, O, M >, const S, V_DIV, M >&
        proxy ) {
            Vector< T, M > temp( proxy.lhs() );
            lhs += temp / T( proxy.rhs() );
        }
    };
    // y -= x / alpha
    template< typename T, typename S, VecType M >
    class OpExecutor< Vector< T, M >, V_INPLACE_SUB, VectorExpression< const T, 
    const Vector< T, M >, const S, V_DIV, M > > {
    public:
        static void apply( Vector< T, M >& lhs, const VectorExpression< const T, 
    const Vector< T, M >, const S, V_DIV, M >& proxy ) {
                inplace_add( lhs, proxy.lhs(),  - 1 / T ( proxy.rhs() ) );
        }
    };
    // y -= expression( x ) / alpha
    template< typename T, typename S, typename L, typename R, Oper O,
            VecType M >
    class OpExecutor< Vector< T, M >, V_INPLACE_SUB, VectorExpression< const T, 
    const VectorExpression< const T, const L, const R, O, M >, const S, V_DIV, M > > {
    public:
        static void apply( Vector< T, M >& lhs, const VectorExpression< const T, 
    const VectorExpression< const T, const L, const R, O, M >, const S, V_DIV, M >&
        proxy ) {
            Vector< T, M > temp( proxy.lhs() );
            lhs -= temp / T( proxy.rhs() );
        }
    };
    // y = x / a
    template< typename T, typename S, VecType M >
    class OpExecutor< Vector< T, M >, V_ASSIGN, VectorExpression< const T,
    const Vector< T, M >, const S, V_DIV, M > > {
    public:
        static void apply( Vector< T, M >& lhs, const VectorExpression< const T,
    const Vector< T, M >, const S, V_DIV, M >& proxy ) {
            if( aliasing( lhs, proxy ) ) {
                scale( lhs, 1 / T( proxy.rhs() ) );
            } else {
                lhs = 0;
                inplace_add( lhs, proxy.lhs(), 1 / T( proxy.rhs() ) );
            }
        }
    };
    // y = expression( x ) / a
    template< typename T, typename L, typename R, Oper O,
            typename S, VecType M >
    class OpExecutor< Vector< T, M >, V_ASSIGN, VectorExpression< const T, 
    const VectorExpression< const T, const L, const R, O, M >, const S, V_DIV, M > > {
    public:
        static void apply( Vector< T, M >& lhs, const VectorExpression< const T, 
    const VectorExpression< const T, const L, const R, O, M >, const S, V_DIV, M >& 
        proxy ) {
            Vector< T, M > temp( proxy.lhs() );
            lhs = temp * ( 1 / T ( proxy.rhs() ) );
        }
    };
    // y = - x
    template< typename T, VecType M >
    class OpExecutor< Vector< T, M >, V_ASSIGN, VectorExpression< const T,
    const Vector< T, M >, const Vector< T, M >, V_NEGATIVE, M > > {
    public:
        static void apply( Vector< T, M >& lhs, const VectorExpression< const T,
    const Vector< T, M >, const Vector< T, M >, V_NEGATIVE, M >&
        proxy ) {
            lhs = - 1 * proxy.lhs();
        }
    };
    // y = - expression( x )
    template< typename T, typename L, typename R, Oper O, VecType M >
    class OpExecutor< Vector< T, M >, V_ASSIGN, VectorExpression< const T, 
    const VectorExpression< const T, const L, const R, O, M >, 
            const VectorExpression< const T, const L, const R, O, M >, V_NEGATIVE, M > > {
    public:
        static void apply( Vector< T, M >& lhs, const VectorExpression< const T, 
    const VectorExpression< const T, const L, const R, O, M >, 
            const VectorExpression< const T, const L, const R, O, M >, 
                V_NEGATIVE, M >& proxy ) {
             Vector< T, M > temp( proxy.lhs() );
            lhs = - 1 * temp;
        }
    };
    // y += expression( x ) * a
    template< typename T, typename L, typename R, Oper O, 
            typename S, VecType M >
    class OpExecutor< Vector< T, M >, V_INPLACE_ADD, VectorExpression< const T, 
    const VectorExpression< const T, const L, const R, O, M >, const S, V_SCALE, M > > {
    public:
        static void apply( Vector< T, M >& lhs, const VectorExpression< const T, 
    const VectorExpression< const T, const L, const R, O, M >, const S, V_SCALE, M >&
        proxy  ) {
            Vector< T, M > temp( proxy.lhs() );
            lhs += temp * proxy.rhs();
        }
    };
    // y -= expression( x ) * a
    template< typename T, typename L, typename R, Oper O, typename S,
            VecType M >
    class OpExecutor< Vector< T, M >, V_INPLACE_SUB, VectorExpression< const T, 
    const VectorExpression< const T, const L, const R, O, M >, const S, V_SCALE, M > > {
    public:
        static void apply( Vector< T, M >& lhs, const VectorExpression< const T, 
    const VectorExpression< const T, const L, const R, O, M >, const S, V_SCALE, M >&
        proxy  ) {
            Vector< T, M > temp( proxy.lhs() );
            lhs -= temp * proxy.rhs();
        }
    };
    // y += - expression( x )
    template< typename T, typename L, typename R, Oper O, VecType M >
    class OpExecutor< Vector< T, M >, V_INPLACE_ADD, VectorExpression< const T, 
    const VectorExpression< const T, const L, const R, O, M >, 
    const VectorExpression< const T, const L, const R, O, M >, V_NEGATIVE, M > > {
    public:
        static void apply( Vector< T, M >& lhs, const VectorExpression< const T, 
    const VectorExpression< const T, const L, const R, O, M >, 
    const VectorExpression< const T, const L, const R, O, M >, V_NEGATIVE, M >& proxy  ) {
            Vector< T, M > temp( proxy.lhs() );
            lhs += temp * (  - 1 );
        }
    };
    // y -= - expression( x )
    template< typename T, typename L, typename R, Oper O, VecType M >
    class OpExecutor< Vector< T, M >, V_INPLACE_SUB, VectorExpression< const T, 
    const VectorExpression< const T, const L, const R, O, M >, 
    const VectorExpression< const T, const L, const R, O, M >, V_NEGATIVE, M > > {
    public:
        static void apply( Vector< T, M >& lhs, const VectorExpression< const T, 
    const VectorExpression< const T, const L, const R, O, M >, 
    const VectorExpression< const T, const L, const R, O, M >, V_NEGATIVE, M >&
        proxy  ) {
            Vector< T, M > temp( proxy.lhs() );
            lhs -= temp * (  - 1 );
        }
    };
    // z += expression( x ) + expression( y )
    template< typename T, typename L, typename R, VecType M >
    class OpExecutor< Vector< T, M >, V_INPLACE_ADD, VectorExpression< const T, const L, 
            const R, V_ADD, M > > {
    public:
        static void apply( Vector< T, M >& lhs, const VectorExpression< const T, const L, 
            const R, V_ADD, M >& proxy ) {
            if( aliasing( lhs, proxy ) ) {
                Vector< T, M > temp( proxy.lhs() );
                OpExecutor< Vector< T, M >, V_INPLACE_ADD, R >::apply( 
                temp, proxy.rhs());
                lhs += temp;
            } else {
                lhs += proxy.lhs();
                OpExecutor< Vector< T, M >, V_INPLACE_ADD, R >::apply( lhs,
                        proxy.rhs());
            }
        }
    };
    // z -= expression( x ) + expression( y )
    template< typename T, typename L, typename R, VecType M >
    class OpExecutor< Vector< T, M >, V_INPLACE_SUB, VectorExpression< const T, const L, 
            const R, V_ADD, M > > {
    public:
        static void apply( Vector< T, M >& lhs, const VectorExpression< const T, const L, 
            const R, V_ADD, M >& proxy ) {
            if( aliasing( lhs, proxy ) ) {
                Vector< T, M > temp( proxy.lhs() );
                OpExecutor< Vector< T, M >, V_INPLACE_ADD, R >::apply( 
                temp, proxy.rhs());
                lhs -= temp;
            } else {
                lhs -= proxy.lhs();
                OpExecutor< Vector< T, M >, V_INPLACE_SUB, R >::apply( lhs,
                        proxy.rhs());
            }
        }
    };
    // z = expression( x ) - expression( y )
    template< typename T, typename L, typename R, VecType M >
    class OpExecutor< Vector< T, M >, V_ASSIGN, VectorExpression< const T, const L, 
            const R, V_SUB, M > > {
    public:
        static void apply( Vector< T, M >& lhs, const VectorExpression< const T, const L, 
            const R, V_SUB, M >& proxy ) {
            if( aliasing( lhs, proxy ) ) {
                Vector< T, M > temp( proxy.lhs() );
                OpExecutor< Vector< T, M >, V_INPLACE_SUB, R >::apply( 
                temp, proxy.rhs());
                lhs = temp;
            } else {
                lhs = proxy.lhs();
                OpExecutor< Vector< T, M >, V_INPLACE_SUB, R >::apply( lhs,
                        proxy.rhs());
            }
        }
    };
    // z += expression( x ) - expression( y )
    template< typename T, typename L, typename R, VecType M >
    class OpExecutor< Vector< T, M >, V_INPLACE_ADD, VectorExpression< const T, const L, 
            const R, V_SUB, M > > {
    public:
        static void apply( Vector< T, M >& lhs, const VectorExpression< const T, const L, 
            const R, V_SUB, M >& proxy ) {
            if( aliasing( lhs, proxy ) ) {
                Vector< T, M > temp( proxy.lhs() );
                OpExecutor< Vector< T, M >, V_INPLACE_SUB, R >::apply( 
                temp, proxy.rhs());
                lhs += temp;
            } else {
                lhs += proxy.lhs();
                OpExecutor< Vector< T, M >, V_INPLACE_SUB, R >::apply( lhs,
                        proxy.rhs());
            }
        }
    };
    // z -= expression( x ) - expression( y )
    template< typename T, typename L, typename R, VecType M >
    class OpExecutor< Vector< T, M >, V_INPLACE_SUB, VectorExpression< const T, const L, 
            const R, V_SUB, M > > {
    public:
        static void apply( Vector< T, M >& lhs, const VectorExpression< const T, const L, 
            const R, V_SUB, M >& proxy ) {
            if( aliasing( lhs, proxy ) ) {
                Vector< T, M > temp( proxy.lhs() );
                OpExecutor< Vector< T, M >, V_INPLACE_SUB, R >::apply( 
                temp, proxy.rhs());
                lhs -= temp;
            } else {
                lhs -= proxy.lhs();
                OpExecutor< Vector< T, M >, V_INPLACE_ADD, R >::apply( lhs,
                        proxy.rhs());
            }
        }
    };
    /* OpExecutor for Matrix */
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
    // A = inv( expression )
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_ASSIGN, MatrixExpression<
            const MatrixExpression< const L, const R, O >, 
            const MatrixExpression< const L, const R, O >, M_INV > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression<
        const MatrixExpression< const L, const R, O >, 
        const MatrixExpression< const L, const R, O >, M_INV >& rhs ) {
            Matrix< T > temp( rhs.rhs() );
            lhs = solve( temp );
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
    // A += inv( B )
    template< typename T >
    class OpExecutor< Matrix< T >, M_INPLACE_ADD, 
            MatrixExpression< const Matrix< T >, 
                                         const Matrix< T >, M_INV > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression<
                const Matrix< T >,
                const Matrix< T >, M_INV >& rhs ) {
            Matrix< T > temp( solve( rhs.rhs() ) );
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
    // A += inv( expression( B ) )
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_INPLACE_ADD, MatrixExpression<
    const MatrixExpression< const L, const R, O >, const MatrixExpression<
    const L, const R, O >, M_INV > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression<
        const MatrixExpression< const L, const R, O >,
        const MatrixExpression< const L, const R, O >, M_INV >& rhs ) {
            Matrix< T > temp( rhs.rhs());
            inv( temp );
            lhs += temp;
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
    // A -= inv( B )
    template< typename T >
    class OpExecutor< Matrix< T >, M_INPLACE_SUB, 
            MatrixExpression< const Matrix< T >, 
                                         const Matrix< T >, M_INV > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression<
                const Matrix< T >,
                const Matrix< T >, M_INV >& rhs ) {
            Matrix< T > temp( solve( rhs.rhs() ) );
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
    // A -= inv( expression( B ) )
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_INPLACE_SUB, MatrixExpression<
    const MatrixExpression< const L, const R, O >, const MatrixExpression<
    const L, const R, O >, M_INV > > {
    public:
        static void apply( Matrix< T >& lhs, const MatrixExpression<
        const MatrixExpression< const L, const R, O >,
        const MatrixExpression< const L, const R, O >, M_INV >& rhs ) {
            Matrix< T > temp( rhs.rhs() );
            inv( temp );
            lhs -= temp;
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
                m_mult( proxy.lhs().lhs(), proxy.rhs().lhs(), lhs, MagmaTrans, MagmaTrans );
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
                m_mult( proxy.lhs().lhs(), proxy.rhs().lhs(), lhs, MagmaTrans, MagmaTrans,
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
                m_mult( proxy.lhs().lhs(), proxy.rhs().lhs(), lhs, MagmaTrans, MagmaTrans,
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
    /* Matrix-vector products */
    // y = A * x (COL)
    template< typename T >
    class OpExecutor< Vector< T, COL >, V_ASSIGN, 
            VectorExpression< const T, const Matrix< T >, 
                const Vector< T, COL >, MV_MULT, COL > > {
    public:
        static void apply( Vector< T, COL >& lhs, 
                const VectorExpression< const T, const Matrix< T >, 
                    const Vector< T, COL >, MV_MULT, COL >& rhs ) {
            if( aliasing( lhs, rhs.rhs() ) ) {
                Vector< T, COL > temp( rhs );
                lhs = temp;
            } else {
                mv_mult( rhs.lhs(), rhs.rhs(), lhs, MagmaNoTrans, 1, 0 );
            }
        }
    };
    // y = x * A (ROW)
    template< typename T >
    class OpExecutor< Vector< T, ROW >, V_ASSIGN, 
            VectorExpression< const T, const Vector< T, ROW >,
                const Matrix< T >, VM_MULT, ROW > > {
    public:
        static void apply( Vector< T, ROW >& lhs, 
                const VectorExpression< const T, const Vector< T, ROW >,
                const Matrix< T >, VM_MULT, ROW >& rhs ) {
            if( aliasing( lhs, rhs.lhs() ) ) {
                Vector< T, ROW > temp( rhs );
                lhs = temp;
            } else {
                mv_mult( rhs.rhs(), rhs.lhs(), lhs, MagmaTrans, 1, 0 );
            }
        }
    };
    // y = t( A ) * x
    template< typename T >
    class OpExecutor< Vector< T, COL >, V_ASSIGN, 
            VectorExpression< const T, const MatrixExpression< 
                const Matrix< T >, const Matrix< T >, M_TRANS >, 
                const Vector< T, COL >, MV_MULT, COL > > {
    public:
        static void apply( Vector< T, COL >& lhs, 
                const VectorExpression< const T, const MatrixExpression< 
                const Matrix< T >, const Matrix< T >, M_TRANS >, 
                const Vector< T, COL >, MV_MULT, COL >& rhs ) {
            if( aliasing( lhs, rhs.rhs() ) ) {
                Vector< T, COL > temp( rhs );
                lhs = temp;
            } else {
                mv_mult( rhs.lhs().lhs(), rhs.rhs(), lhs, MagmaTrans, 1, 0 );
            }
        }
    };
    // y = x * t( A ) (ROW)
    template< typename T >
    class OpExecutor< Vector< T, ROW >, V_ASSIGN, 
            VectorExpression< const T, const Vector< T, ROW >,
                const MatrixExpression< 
                const Matrix< T >, const Matrix< T >, M_TRANS >,
                VM_MULT, ROW > > {
    public:
        static void apply( Vector< T, ROW >& lhs, 
                const VectorExpression< const T, const Vector< T, ROW >,
                const MatrixExpression< 
                const Matrix< T >, const Matrix< T >, M_TRANS >,
                VM_MULT, ROW >& rhs ) {
            if( aliasing( lhs, rhs.lhs() ) ) {
                Vector< T, ROW > temp( rhs );
                lhs = temp;
            } else {
                mv_mult( rhs.rhs().lhs(), rhs.lhs(), lhs, MagmaNoTrans, 1, 0 );
            }
        }
    };
    // y = expression( A ) * x
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Vector< T, COL >,
            V_ASSIGN, 
            VectorExpression< const T, 
                const MatrixExpression< const L, const R, O >,
                const Vector< T, COL >,
                MV_MULT, 
                COL >
           > {
    public:
        static void apply( Vector< T, COL >& lhs,
                const VectorExpression< const T, 
                const MatrixExpression< const L, const R, O >,
                const Vector< T, COL >,
                MV_MULT, 
                COL >& rhs ) {
            Matrix< T > temp( rhs.lhs() );
            mv_mult( temp, rhs.rhs(), lhs, MagmaNoTrans, 1, 0 );
        }
    };
    // y = x * expression( A )
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Vector< T, ROW >,
            V_ASSIGN, 
            VectorExpression< const T, 
                const Vector< T, ROW >,
                const MatrixExpression< const L, const R, O >,
                VM_MULT, 
                ROW >
           > {
    public:
        static void apply( Vector< T, ROW >& lhs,
                const VectorExpression< const T, 
                const Vector< T, ROW >,
                const MatrixExpression< const L, const R, O >,
                VM_MULT, 
                ROW >& rhs ) {
            Matrix< T > temp( rhs.rhs() );
            mv_mult( temp, rhs.lhs(), lhs, MagmaTrans, 1, 0 );
        }
    };
    // y = t( expression( A ) ) * x
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Vector< T, COL >,
            V_ASSIGN, 
            VectorExpression< const T, 
                const MatrixExpression< 
                    const MatrixExpression< const L, const R, O >,
                    const MatrixExpression< const L, const R, O >,
                    M_TRANS >,
                const Vector< T, COL >,
                MV_MULT, 
                COL >
           > {
    public:
        static void apply( Vector< T, COL >& lhs,
                const VectorExpression< const T, 
                const MatrixExpression< 
                    const MatrixExpression< const L, const R, O >,
                    const MatrixExpression< const L, const R, O >,
                    M_TRANS >,
                const Vector< T, COL >,
                MV_MULT, 
                COL >& rhs ) {
            Matrix< T > temp( rhs.lhs().lhs() );
            mv_mult( temp, rhs.rhs(), lhs, MagmaTrans, 1, 0 );
        }
    };
    // y = x * t( expression( A ) )
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Vector< T, ROW >,
            V_ASSIGN, 
            VectorExpression< const T, 
                const Vector< T, ROW >,
                const MatrixExpression< 
                    const MatrixExpression< const L, const R, O >,
                    const MatrixExpression< const L, const R, O >,
                    M_TRANS >,
                VM_MULT, 
                ROW >
           > {
    public:
        static void apply( Vector< T, ROW >& lhs,
                const VectorExpression< const T, 
                const Vector< T, ROW >,
                const MatrixExpression< 
                    const MatrixExpression< const L, const R, O >,
                    const MatrixExpression< const L, const R, O >,
                    M_TRANS >,
                VM_MULT, 
                ROW >& rhs ) {
            Matrix< T > temp( rhs.rhs().rhs() );
            mv_mult( temp, rhs.lhs(), lhs, MagmaNoTrans, 1, 0 );
        }
    };
    // y = A * expression( x )
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Vector< T, COL >, V_ASSIGN, 
            VectorExpression< const T, const Matrix< T >, 
                const VectorExpression< const T, const L, const R, O, COL >,
                MV_MULT, COL > > {
    public:
        static void apply( Vector< T, COL >& lhs, 
                const VectorExpression< const T, const Matrix< T >, 
                    const VectorExpression< const T, const L, 
                        const R, O, COL >, MV_MULT, COL >& rhs ) {
            Vector< T, COL > temp( rhs.rhs() );
            mv_mult( rhs.lhs(), temp, lhs, MagmaNoTrans, 1, 0 );
        }
    };
    // y = expression( x ) * A
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Vector< T, ROW >, V_ASSIGN, 
            VectorExpression< const T, 
                const VectorExpression< const T, const L, const R, O, ROW >,
            const Matrix< T >, VM_MULT, ROW > > {
    public:
        static void apply( Vector< T, ROW >& lhs, 
                const VectorExpression< const T, 
                const VectorExpression< const T, const L, const R, O, ROW >,
            const Matrix< T >, VM_MULT, ROW >& rhs ) {
            Vector< T, ROW > temp( rhs.lhs() );
            mv_mult( rhs.rhs(), temp, lhs, MagmaTrans, 1, 0 );
        }
    };
    // y = t( A ) * expression( x )
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Vector< T, COL >, V_ASSIGN, 
            VectorExpression< const T, 
                const MatrixExpression< const Matrix< T >, 
                    const Matrix< T >, M_TRANS >, 
                const VectorExpression< const T, const L, const R, O, COL >,
                MV_MULT, COL > > {
    public:
        static void apply( Vector< T, COL >& lhs, 
                const VectorExpression< const T, 
                const MatrixExpression< const Matrix< T >, 
                    const Matrix< T >, M_TRANS >, 
                    const VectorExpression< const T, const L, 
                        const R, O, COL >, MV_MULT, COL >& rhs ) {
            Vector< T, COL > temp( rhs.rhs() );
            mv_mult( rhs.lhs().lhs(), temp, lhs, MagmaTrans, 1, 0 );
        }
    };
    // y = expression( x ) * t( A )
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Vector< T, ROW >, V_ASSIGN, 
            VectorExpression< const T, 
                const VectorExpression< const T, const L, const R, O, ROW >,
            const MatrixExpression< const Matrix< T >, 
                    const Matrix< T >, M_TRANS >, VM_MULT, ROW > > {
    public:
        static void apply( Vector< T, ROW >& lhs, 
                const VectorExpression< const T, 
                const VectorExpression< const T, const L, const R, O, ROW >,
            const MatrixExpression< const Matrix< T >, 
                    const Matrix< T >, M_TRANS >, VM_MULT, ROW >& rhs ) {
            Vector< T, ROW > temp( rhs.lhs() );
            mv_mult( rhs.rhs().rhs(), temp, lhs, MagmaNoTrans, 1, 0 );
        }
    };
    // y = expression( A ) * expression( x )
    template< typename T, typename L1, typename R1, Oper O1,
            typename L2, typename R2, Oper O2 >
    class OpExecutor< Vector< T, COL >, V_ASSIGN,
            VectorExpression< const T,
                const MatrixExpression< const L1, const R1, O1 >,
                const VectorExpression< const T, const L2, const R2, O2, COL >,
                MV_MULT, COL > 
        > {
    public: 
        static void apply( Vector< T, COL >& lhs, 
                const VectorExpression< const T, 
                    const MatrixExpression< const L1, const R1, O1 >,
                    const VectorExpression< const T, const L2, const R2, O2, COL >,
                MV_MULT, COL >& rhs ) {
            Matrix< T > m( rhs.lhs() );
            Vector< T, COL > v( rhs.rhs() );
            mv_mult( m, v, lhs, MagmaNoTrans, 1, 0 );
        }
    };
    // y = expression( x ) * expression( A ) 
    template< typename T, typename L1, typename R1, Oper O1,
            typename L2, typename R2, Oper O2 >
    class OpExecutor< Vector< T, ROW >, V_ASSIGN,
            VectorExpression< const T,
                const VectorExpression< const T, const L2, const R2, O2, ROW >,
                const MatrixExpression< const L1, const R1, O1 >,
                VM_MULT, ROW > 
        > {
    public: 
        static void apply( Vector< T, ROW >& lhs, 
                const VectorExpression< const T,
                const VectorExpression< const T, const L2, const R2, O2, ROW >,
                const MatrixExpression< const L1, const R1, O1 >,
                VM_MULT, ROW >& rhs ) {
            Matrix< T > m( rhs.rhs() );
            Vector< T, ROW > v( rhs.lhs() );
            mv_mult( m, v, lhs, MagmaTrans, 1, 0 );
        }
    };
    // y = t( expression( A ) ) * expression( x )
    template< typename T, typename L1, typename R1, Oper O1,
            typename L2, typename R2, Oper O2 >
    class OpExecutor< Vector< T, COL >, V_ASSIGN,
            VectorExpression< const T,
                const MatrixExpression<
                    const MatrixExpression< const L1, const R1, O1 >,
                    const MatrixExpression< const L1, const R1, O1 >,
                    M_TRANS >,
                const VectorExpression< const T, const L2, const R2, O2, COL >,
                MV_MULT, COL > 
        > {
    public: 
        static void apply( Vector< T, COL >& lhs, 
                const VectorExpression< const T,
                const MatrixExpression<
                    const MatrixExpression< const L1, const R1, O1 >,
                    const MatrixExpression< const L1, const R1, O1 >,
                    M_TRANS >,
                const VectorExpression< const T, const L2, const R2, O2, COL >,
                MV_MULT, COL >& rhs ) {
            Matrix< T > m( rhs.lhs().lhs() );
            Vector< T, COL > v( rhs.rhs() );
            mv_mult( m, v, lhs, MagmaTrans, 1, 0 );
        }
    };
    // y = expression( x ) * t( expression( A ) ) 
    template< typename T, typename L1, typename R1, Oper O1,
            typename L2, typename R2, Oper O2 >
    class OpExecutor< Vector< T, ROW >, V_ASSIGN,
            VectorExpression< const T,
                const VectorExpression< const T, const L2, const R2, O2, ROW >,
                const MatrixExpression<
                    const MatrixExpression< const L1, const R1, O1 >,
                    const MatrixExpression< const L1, const R1, O1 >,
                    M_TRANS >,
                VM_MULT, ROW > 
        > {
    public: 
        static void apply( Vector< T, ROW >& lhs, 
                const VectorExpression< const T,
                const VectorExpression< const T, const L2, const R2, O2, ROW >,
                const MatrixExpression<
                    const MatrixExpression< const L1, const R1, O1 >,
                    const MatrixExpression< const L1, const R1, O1 >,
                    M_TRANS >,
                VM_MULT, ROW >& rhs ) {
            Matrix< T > m( rhs.rhs().rhs() );
            Vector< T, ROW > v( rhs.lhs() );
            mv_mult( m, v, lhs, MagmaNoTrans, 1, 0 );
        }
    };
    // y += A * x (COL)
    template< typename T >
    class OpExecutor< Vector< T, COL >, V_INPLACE_ADD, 
            VectorExpression< const T, const Matrix< T >, 
                const Vector< T, COL >, MV_MULT, COL > > {
    public:
        static void apply( Vector< T, COL >& lhs, 
                const VectorExpression< const T, const Matrix< T >, 
                    const Vector< T, COL >, MV_MULT, COL >& rhs ) {
            if( aliasing( lhs, rhs.rhs() ) ) {
                Vector< T, COL > temp( rhs );
                lhs += temp;
            } else {
                mv_mult( rhs.lhs(), rhs.rhs(), lhs, MagmaNoTrans, 1, 1 );
            }
        }
    };
    // y += x * A (ROW)
    template< typename T >
    class OpExecutor< Vector< T, ROW >, V_INPLACE_ADD, 
            VectorExpression< const T, const Vector< T, ROW >,
                const Matrix< T >, VM_MULT, ROW > > {
    public:
        static void apply( Vector< T, ROW >& lhs, 
                const VectorExpression< const T, const Vector< T, ROW >,
                const Matrix< T >, VM_MULT, ROW >& rhs ) {
            if( aliasing( lhs, rhs.lhs() ) ) {
                Vector< T, ROW > temp( rhs );
                lhs += temp;
            } else {
                mv_mult( rhs.rhs(), rhs.lhs(), lhs, MagmaTrans, 1, 1 );
            }
        }
    };
    // y += t( A ) * x
    template< typename T >
    class OpExecutor< Vector< T, COL >, V_INPLACE_ADD, 
            VectorExpression< const T, const MatrixExpression< 
                const Matrix< T >, const Matrix< T >, M_TRANS >, 
                const Vector< T, COL >, MV_MULT, COL > > {
    public:
        static void apply( Vector< T, COL >& lhs, 
                const VectorExpression< const T, const MatrixExpression< 
                const Matrix< T >, const Matrix< T >, M_TRANS >, 
                const Vector< T, COL >, MV_MULT, COL >& rhs ) {
            if( aliasing( lhs, rhs.rhs() ) ) {
                Vector< T, COL > temp( rhs );
                lhs += temp;
            } else {
                mv_mult( rhs.lhs().lhs(), rhs.rhs(), lhs, MagmaTrans, 1, 1 );
            }
        }
    };
    // y += x * t( A ) (ROW)
    template< typename T >
    class OpExecutor< Vector< T, ROW >, V_INPLACE_ADD, 
            VectorExpression< const T, const Vector< T, ROW >,
                const MatrixExpression< 
                const Matrix< T >, const Matrix< T >, M_TRANS >,
                VM_MULT, ROW > > {
    public:
        static void apply( Vector< T, ROW >& lhs, 
                const VectorExpression< const T, const Vector< T, ROW >,
                const MatrixExpression< 
                const Matrix< T >, const Matrix< T >, M_TRANS >,
                VM_MULT, ROW >& rhs ) {
            if( aliasing( lhs, rhs.lhs() ) ) {
                Vector< T, ROW > temp( rhs );
                lhs += temp;
            } else {
                mv_mult( rhs.rhs().lhs(), rhs.lhs(), lhs, MagmaNoTrans, 1, 1 );
            }
        }
    };
    // y += expression( A ) * x
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Vector< T, COL >,
            V_INPLACE_ADD, 
            VectorExpression< const T, 
                const MatrixExpression< const L, const R, O >,
                const Vector< T, COL >,
                MV_MULT, 
                COL >
           > {
    public:
        static void apply( Vector< T, COL >& lhs,
                const VectorExpression< const T, 
                const MatrixExpression< const L, const R, O >,
                const Vector< T, COL >,
                MV_MULT, 
                COL >& rhs ) {
            Matrix< T > temp( rhs.lhs() );
            mv_mult( temp, rhs.rhs(), lhs, MagmaNoTrans, 1, 1 );
        }
    };
    // y += x * expression( A )
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Vector< T, ROW >,
            V_INPLACE_ADD, 
            VectorExpression< const T, 
                const Vector< T, ROW >,
                const MatrixExpression< const L, const R, O >,
                VM_MULT, 
                ROW >
           > {
    public:
        static void apply( Vector< T, ROW >& lhs,
                const VectorExpression< const T, 
                const Vector< T, ROW >,
                const MatrixExpression< const L, const R, O >,
                VM_MULT, 
                ROW >& rhs ) {
            Matrix< T > temp( rhs.rhs() );
            mv_mult( temp, rhs.lhs(), lhs, MagmaTrans, 1, 1 );
        }
    };
    // y += t( expression( A ) ) * x
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Vector< T, COL >,
            V_INPLACE_ADD, 
            VectorExpression< const T, 
                const MatrixExpression< 
                    const MatrixExpression< const L, const R, O >,
                    const MatrixExpression< const L, const R, O >,
                    M_TRANS >,
                const Vector< T, COL >,
                MV_MULT, 
                COL >
           > {
    public:
        static void apply( Vector< T, COL >& lhs,
                const VectorExpression< const T, 
                const MatrixExpression< 
                    const MatrixExpression< const L, const R, O >,
                    const MatrixExpression< const L, const R, O >,
                    M_TRANS >,
                const Vector< T, COL >,
                MV_MULT, 
                COL >& rhs ) {
            Matrix< T > temp( rhs.lhs().lhs() );
            mv_mult( temp, rhs.rhs(), lhs, MagmaTrans, 1, 1 );
        }
    };
    // y += x * t( expression( A ) )
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Vector< T, ROW >,
            V_INPLACE_ADD, 
            VectorExpression< const T, 
                const Vector< T, ROW >,
                const MatrixExpression< 
                    const MatrixExpression< const L, const R, O >,
                    const MatrixExpression< const L, const R, O >,
                    M_TRANS >,
                VM_MULT, 
                ROW >
           > {
    public:
        static void apply( Vector< T, ROW >& lhs,
                const VectorExpression< const T, 
                const Vector< T, ROW >,
                const MatrixExpression< 
                    const MatrixExpression< const L, const R, O >,
                    const MatrixExpression< const L, const R, O >,
                    M_TRANS >,
                VM_MULT, 
                ROW >& rhs ) {
            Matrix< T > temp( rhs.rhs().rhs() );
            mv_mult( temp, rhs.lhs(), lhs, MagmaNoTrans, 1, 1 );
        }
    };
    // y += A * expression( x )
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Vector< T, COL >, V_INPLACE_ADD, 
            VectorExpression< const T, const Matrix< T >, 
                const VectorExpression< const T, const L, const R, O, COL >,
                MV_MULT, COL > > {
    public:
        static void apply( Vector< T, COL >& lhs, 
                const VectorExpression< const T, const Matrix< T >, 
                    const VectorExpression< const T, const L, 
                        const R, O, COL >, MV_MULT, COL >& rhs ) {
            Vector< T, COL > temp( rhs.rhs() );
            mv_mult( rhs.lhs(), temp, lhs, MagmaNoTrans, 1, 1 );
        }
    };
    // y += expression( x ) * A
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Vector< T, ROW >, V_INPLACE_ADD, 
            VectorExpression< const T, 
                const VectorExpression< const T, const L, const R, O, ROW >,
            const Matrix< T >, VM_MULT, ROW > > {
    public:
        static void apply( Vector< T, ROW >& lhs, 
                const VectorExpression< const T, 
                const VectorExpression< const T, const L, const R, O, ROW >,
            const Matrix< T >, VM_MULT, ROW >& rhs ) {
            Vector< T, ROW > temp( rhs.lhs() );
            mv_mult( rhs.rhs(), temp, lhs, MagmaTrans, 1, 1 );
        }
    };
    // y += t( A ) * expression( x )
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Vector< T, COL >, V_INPLACE_ADD, 
            VectorExpression< const T, 
                const MatrixExpression< const Matrix< T >, 
                    const Matrix< T >, M_TRANS >, 
                const VectorExpression< const T, const L, const R, O, COL >,
                MV_MULT, COL > > {
    public:
        static void apply( Vector< T, COL >& lhs, 
                const VectorExpression< const T, 
                const MatrixExpression< const Matrix< T >, 
                    const Matrix< T >, M_TRANS >, 
                    const VectorExpression< const T, const L, 
                        const R, O, COL >, MV_MULT, COL >& rhs ) {
            Vector< T, COL > temp( rhs.rhs() );
            mv_mult( rhs.lhs().lhs(), temp, lhs, MagmaTrans, 1, 1 );
        }
    };
    // y += expression( x ) * t( A )
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Vector< T, ROW >, V_INPLACE_ADD, 
            VectorExpression< const T, 
                const VectorExpression< const T, const L, const R, O, ROW >,
            const MatrixExpression< const Matrix< T >, 
                    const Matrix< T >, M_TRANS >, VM_MULT, ROW > > {
    public:
        static void apply( Vector< T, ROW >& lhs, 
                const VectorExpression< const T, 
                const VectorExpression< const T, const L, const R, O, ROW >,
            const MatrixExpression< const Matrix< T >, 
                    const Matrix< T >, M_TRANS >, VM_MULT, ROW >& rhs ) {
            Vector< T, ROW > temp( rhs.lhs() );
            mv_mult( rhs.rhs().rhs(), temp, lhs, MagmaNoTrans, 1, 1 );
        }
    };
    // y += expression( A ) * expression( x )
    template< typename T, typename L1, typename R1, Oper O1,
            typename L2, typename R2, Oper O2 >
    class OpExecutor< Vector< T, COL >, V_INPLACE_ADD,
            VectorExpression< const T,
                const MatrixExpression< const L1, const R1, O1 >,
                const VectorExpression< const T, const L2, const R2, O2, COL >,
                MV_MULT, COL > 
        > {
    public: 
        static void apply( Vector< T, COL >& lhs, 
                const VectorExpression< const T, 
                    const MatrixExpression< const L1, const R1, O1 >,
                    const VectorExpression< const T, const L2, const R2, O2, COL >,
                MV_MULT, COL >& rhs ) {
            Matrix< T > m( rhs.lhs() );
            Vector< T, COL > v( rhs.rhs() );
            mv_mult( m, v, lhs, MagmaNoTrans, 1, 1 );
        }
    };
    // y += expression( x ) * expression( A ) 
    template< typename T, typename L1, typename R1, Oper O1,
            typename L2, typename R2, Oper O2 >
    class OpExecutor< Vector< T, ROW >, V_INPLACE_ADD,
            VectorExpression< const T,
                const VectorExpression< const T, const L2, const R2, O2, ROW >,
                const MatrixExpression< const L1, const R1, O1 >,
                VM_MULT, ROW > 
        > {
    public: 
        static void apply( Vector< T, ROW >& lhs, 
                const VectorExpression< const T,
                const VectorExpression< const T, const L2, const R2, O2, ROW >,
                const MatrixExpression< const L1, const R1, O1 >,
                VM_MULT, ROW >& rhs ) {
            Matrix< T > m( rhs.rhs() );
            Vector< T, ROW > v( rhs.lhs() );
            mv_mult( m, v, lhs, MagmaTrans, 1, 1 );
        }
    };
    // y += t( expression( A ) ) * expression( x )
    template< typename T, typename L1, typename R1, Oper O1,
            typename L2, typename R2, Oper O2 >
    class OpExecutor< Vector< T, COL >, V_INPLACE_ADD,
            VectorExpression< const T,
                const MatrixExpression<
                    const MatrixExpression< const L1, const R1, O1 >,
                    const MatrixExpression< const L1, const R1, O1 >,
                    M_TRANS >,
                const VectorExpression< const T, const L2, const R2, O2, COL >,
                MV_MULT, COL > 
        > {
    public: 
        static void apply( Vector< T, COL >& lhs, 
                const VectorExpression< const T,
                const MatrixExpression<
                    const MatrixExpression< const L1, const R1, O1 >,
                    const MatrixExpression< const L1, const R1, O1 >,
                    M_TRANS >,
                const VectorExpression< const T, const L2, const R2, O2, COL >,
                MV_MULT, COL >& rhs ) {
            Matrix< T > m( rhs.lhs().lhs() );
            Vector< T, COL > v( rhs.rhs() );
            mv_mult( m, v, lhs, MagmaTrans, 1, 1 );
        }
    };
    // y += expression( x ) * t( expression( A ) ) 
    template< typename T, typename L1, typename R1, Oper O1,
            typename L2, typename R2, Oper O2 >
    class OpExecutor< Vector< T, ROW >, V_INPLACE_ADD,
            VectorExpression< const T,
                const VectorExpression< const T, const L2, const R2, O2, ROW >,
                const MatrixExpression<
                    const MatrixExpression< const L1, const R1, O1 >,
                    const MatrixExpression< const L1, const R1, O1 >,
                    M_TRANS >,
                VM_MULT, ROW > 
        > {
    public: 
        static void apply( Vector< T, ROW >& lhs, 
                const VectorExpression< const T,
                const VectorExpression< const T, const L2, const R2, O2, ROW >,
                const MatrixExpression<
                    const MatrixExpression< const L1, const R1, O1 >,
                    const MatrixExpression< const L1, const R1, O1 >,
                    M_TRANS >,
                VM_MULT, ROW >& rhs ) {
            Matrix< T > m( rhs.rhs().rhs() );
            Vector< T, ROW > v( rhs.lhs() );
            mv_mult( m, v, lhs, MagmaNoTrans, 1, 1 );
        }
    };
    
    // y -= A * x (COL)
    template< typename T >
    class OpExecutor< Vector< T, COL >, V_INPLACE_SUB, 
            VectorExpression< const T, const Matrix< T >, 
                const Vector< T, COL >, MV_MULT, COL > > {
    public:
        static void apply( Vector< T, COL >& lhs, 
                const VectorExpression< const T, const Matrix< T >, 
                    const Vector< T, COL >, MV_MULT, COL >& rhs ) {
            if( aliasing( lhs, rhs.rhs() ) ) {
                Vector< T, COL > temp( rhs );
                lhs -= temp;
            } else {
                mv_mult( rhs.lhs(), rhs.rhs(), lhs, MagmaNoTrans, -1, 1 );
            }
        }
    };
    // y -= x * A (ROW)
    template< typename T >
    class OpExecutor< Vector< T, ROW >, V_INPLACE_SUB, 
            VectorExpression< const T, const Vector< T, ROW >,
                const Matrix< T >, VM_MULT, ROW > > {
    public:
        static void apply( Vector< T, ROW >& lhs, 
                const VectorExpression< const T, const Vector< T, ROW >,
                const Matrix< T >, VM_MULT, ROW >& rhs ) {
            if( aliasing( lhs, rhs.lhs() ) ) {
                Vector< T, ROW > temp( rhs );
                lhs -= temp;
            } else {
                mv_mult( rhs.rhs(), rhs.lhs(), lhs, MagmaTrans, -1, 1 );
            }
        }
    };
    // y -= t( A ) * x
    template< typename T >
    class OpExecutor< Vector< T, COL >, V_INPLACE_SUB, 
            VectorExpression< const T, const MatrixExpression< 
                const Matrix< T >, const Matrix< T >, M_TRANS >, 
                const Vector< T, COL >, MV_MULT, COL > > {
    public:
        static void apply( Vector< T, COL >& lhs, 
                const VectorExpression< const T, const MatrixExpression< 
                const Matrix< T >, const Matrix< T >, M_TRANS >, 
                const Vector< T, COL >, MV_MULT, COL >& rhs ) {
            if( aliasing( lhs, rhs.rhs() ) ) {
                Vector< T, COL > temp( rhs );
                lhs -= temp;
            } else {
                mv_mult( rhs.lhs().lhs(), rhs.rhs(), lhs, MagmaTrans, -1, 1 );
            }
        }
    };
    // y -= x * t( A ) (ROW)
    template< typename T >
    class OpExecutor< Vector< T, ROW >, V_INPLACE_SUB, 
            VectorExpression< const T, const Vector< T, ROW >,
                const MatrixExpression< 
                const Matrix< T >, const Matrix< T >, M_TRANS >,
                VM_MULT, ROW > > {
    public:
        static void apply( Vector< T, ROW >& lhs, 
                const VectorExpression< const T, const Vector< T, ROW >,
                const MatrixExpression< 
                const Matrix< T >, const Matrix< T >, M_TRANS >,
                VM_MULT, ROW >& rhs ) {
            if( aliasing( lhs, rhs.lhs() ) ) {
                Vector< T, ROW > temp( rhs );
                lhs -= temp;
            } else {
                mv_mult( rhs.rhs().lhs(), rhs.lhs(), lhs, MagmaNoTrans, -1, 1 );
            }
        }
    };
    // y -= expression( A ) * x
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Vector< T, COL >,
            V_INPLACE_SUB, 
            VectorExpression< const T, 
                const MatrixExpression< const L, const R, O >,
                const Vector< T, COL >,
                MV_MULT, 
                COL >
           > {
    public:
        static void apply( Vector< T, COL >& lhs,
                const VectorExpression< const T, 
                const MatrixExpression< const L, const R, O >,
                const Vector< T, COL >,
                MV_MULT, 
                COL >& rhs ) {
            Matrix< T > temp( rhs.lhs() );
            mv_mult( temp, rhs.rhs(), lhs, MagmaNoTrans, -1, 1 );
        }
    };
    // y -= x * expression( A )
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Vector< T, ROW >,
            V_INPLACE_SUB, 
            VectorExpression< const T, 
                const Vector< T, ROW >,
                const MatrixExpression< const L, const R, O >,
                VM_MULT, 
                ROW >
           > {
    public:
        static void apply( Vector< T, ROW >& lhs,
                const VectorExpression< const T, 
                const Vector< T, ROW >,
                const MatrixExpression< const L, const R, O >,
                VM_MULT, 
                ROW >& rhs ) {
            Matrix< T > temp( rhs.rhs() );
            mv_mult( temp, rhs.lhs(), lhs, MagmaTrans, -1, 1 );
        }
    };
    // y -= t( expression( A ) ) * x
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Vector< T, COL >,
            V_INPLACE_SUB, 
            VectorExpression< const T, 
                const MatrixExpression< 
                    const MatrixExpression< const L, const R, O >,
                    const MatrixExpression< const L, const R, O >,
                    M_TRANS >,
                const Vector< T, COL >,
                MV_MULT, 
                COL >
           > {
    public:
        static void apply( Vector< T, COL >& lhs,
                const VectorExpression< const T, 
                const MatrixExpression< 
                    const MatrixExpression< const L, const R, O >,
                    const MatrixExpression< const L, const R, O >,
                    M_TRANS >,
                const Vector< T, COL >,
                MV_MULT, 
                COL >& rhs ) {
            Matrix< T > temp( rhs.lhs().lhs() );
            mv_mult( temp, rhs.rhs(), lhs, MagmaTrans, -1, 1 );
        }
    };
    // y -= x * t( expression( A ) )
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Vector< T, ROW >,
            V_INPLACE_SUB, 
            VectorExpression< const T, 
                const Vector< T, ROW >,
                const MatrixExpression< 
                    const MatrixExpression< const L, const R, O >,
                    const MatrixExpression< const L, const R, O >,
                    M_TRANS >,
                VM_MULT, 
                ROW >
           > {
    public:
        static void apply( Vector< T, ROW >& lhs,
                const VectorExpression< const T, 
                const Vector< T, ROW >,
                const MatrixExpression< 
                    const MatrixExpression< const L, const R, O >,
                    const MatrixExpression< const L, const R, O >,
                    M_TRANS >,
                VM_MULT, 
                ROW >& rhs ) {
            Matrix< T > temp( rhs.rhs().rhs() );
            mv_mult( temp, rhs.lhs(), lhs, MagmaNoTrans, -1, 1 );
        }
    };
    // y -= A * expression( x )
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Vector< T, COL >, V_INPLACE_SUB, 
            VectorExpression< const T, const Matrix< T >, 
                const VectorExpression< const T, const L, const R, O, COL >,
                MV_MULT, COL > > {
    public:
        static void apply( Vector< T, COL >& lhs, 
                const VectorExpression< const T, const Matrix< T >, 
                    const VectorExpression< const T, const L, 
                        const R, O, COL >, MV_MULT, COL >& rhs ) {
            Vector< T, COL > temp( rhs.rhs() );
            mv_mult( rhs.lhs(), temp, lhs, MagmaNoTrans, -1, 1 );
        }
    };
    // y -= expression( x ) * A
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Vector< T, ROW >, V_INPLACE_SUB, 
            VectorExpression< const T, 
                const VectorExpression< const T, const L, const R, O, ROW >,
            const Matrix< T >, VM_MULT, ROW > > {
    public:
        static void apply( Vector< T, ROW >& lhs, 
                const VectorExpression< const T, 
                const VectorExpression< const T, const L, const R, O, ROW >,
            const Matrix< T >, VM_MULT, ROW >& rhs ) {
            Vector< T, ROW > temp( rhs.lhs() );
            mv_mult( rhs.rhs(), temp, lhs, MagmaTrans, -1, 1 );
        }
    };
    // y -= t( A ) * expression( x )
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Vector< T, COL >, V_INPLACE_SUB, 
            VectorExpression< const T, 
                const MatrixExpression< const Matrix< T >, 
                    const Matrix< T >, M_TRANS >, 
                const VectorExpression< const T, const L, const R, O, COL >,
                MV_MULT, COL > > {
    public:
        static void apply( Vector< T, COL >& lhs, 
                const VectorExpression< const T, 
                const MatrixExpression< const Matrix< T >, 
                    const Matrix< T >, M_TRANS >, 
                    const VectorExpression< const T, const L, 
                        const R, O, COL >, MV_MULT, COL >& rhs ) {
            Vector< T, COL > temp( rhs.rhs() );
            mv_mult( rhs.lhs().lhs(), temp, lhs, MagmaTrans, -1, 1 );
        }
    };
    // y -= expression( x ) * t( A )
    template< typename T, typename L, typename R, Oper O >
    class OpExecutor< Vector< T, ROW >, V_INPLACE_SUB, 
            VectorExpression< const T, 
                const VectorExpression< const T, const L, const R, O, ROW >,
            const MatrixExpression< const Matrix< T >, 
                    const Matrix< T >, M_TRANS >, VM_MULT, ROW > > {
    public:
        static void apply( Vector< T, ROW >& lhs, 
                const VectorExpression< const T, 
                const VectorExpression< const T, const L, const R, O, ROW >,
            const MatrixExpression< const Matrix< T >, 
                    const Matrix< T >, M_TRANS >, VM_MULT, ROW >& rhs ) {
            Vector< T, ROW > temp( rhs.lhs() );
            mv_mult( rhs.rhs().rhs(), temp, lhs, MagmaNoTrans, -1, 1 );
        }
    };
    // y -= expression( A ) * expression( x )
    template< typename T, typename L1, typename R1, Oper O1,
            typename L2, typename R2, Oper O2 >
    class OpExecutor< Vector< T, COL >, V_INPLACE_SUB,
            VectorExpression< const T,
                const MatrixExpression< const L1, const R1, O1 >,
                const VectorExpression< const T, const L2, const R2, O2, COL >,
                MV_MULT, COL > 
        > {
    public: 
        static void apply( Vector< T, COL >& lhs, 
                const VectorExpression< const T, 
                    const MatrixExpression< const L1, const R1, O1 >,
                    const VectorExpression< const T, const L2, const R2, O2, COL >,
                MV_MULT, COL >& rhs ) {
            Matrix< T > m( rhs.lhs() );
            Vector< T, COL > v( rhs.rhs() );
            mv_mult( m, v, lhs, MagmaNoTrans, -1, 1 );
        }
    };
    // y -= expression( x ) * expression( A ) 
    template< typename T, typename L1, typename R1, Oper O1,
            typename L2, typename R2, Oper O2 >
    class OpExecutor< Vector< T, ROW >, V_INPLACE_SUB,
            VectorExpression< const T,
                const VectorExpression< const T, const L2, const R2, O2, ROW >,
                const MatrixExpression< const L1, const R1, O1 >,
                VM_MULT, ROW > 
        > {
    public: 
        static void apply( Vector< T, ROW >& lhs, 
                const VectorExpression< const T,
                const VectorExpression< const T, const L2, const R2, O2, ROW >,
                const MatrixExpression< const L1, const R1, O1 >,
                VM_MULT, ROW >& rhs ) {
            Matrix< T > m( rhs.rhs() );
            Vector< T, ROW > v( rhs.lhs() );
            mv_mult( m, v, lhs, MagmaTrans, -1, 1 );
        }
    };
    // y -= t( expression( A ) ) * expression( x )
    template< typename T, typename L1, typename R1, Oper O1,
            typename L2, typename R2, Oper O2 >
    class OpExecutor< Vector< T, COL >, V_INPLACE_SUB,
            VectorExpression< const T,
                const MatrixExpression<
                    const MatrixExpression< const L1, const R1, O1 >,
                    const MatrixExpression< const L1, const R1, O1 >,
                    M_TRANS >,
                const VectorExpression< const T, const L2, const R2, O2, COL >,
                MV_MULT, COL > 
        > {
    public: 
        static void apply( Vector< T, COL >& lhs, 
                const VectorExpression< const T,
                const MatrixExpression<
                    const MatrixExpression< const L1, const R1, O1 >,
                    const MatrixExpression< const L1, const R1, O1 >,
                    M_TRANS >,
                const VectorExpression< const T, const L2, const R2, O2, COL >,
                MV_MULT, COL >& rhs ) {
            Matrix< T > m( rhs.lhs().lhs() );
            Vector< T, COL > v( rhs.rhs() );
            mv_mult( m, v, lhs, MagmaTrans, -1, 1 );
        }
    };
    // y -= expression( x ) * t( expression( A ) ) 
    template< typename T, typename L1, typename R1, Oper O1,
            typename L2, typename R2, Oper O2 >
    class OpExecutor< Vector< T, ROW >, V_INPLACE_SUB,
            VectorExpression< const T,
                const VectorExpression< const T, const L2, const R2, O2, ROW >,
                const MatrixExpression<
                    const MatrixExpression< const L1, const R1, O1 >,
                    const MatrixExpression< const L1, const R1, O1 >,
                    M_TRANS >,
                VM_MULT, ROW > 
        > {
    public: 
        static void apply( Vector< T, ROW >& lhs, 
                const VectorExpression< const T,
                const VectorExpression< const T, const L2, const R2, O2, ROW >,
                const MatrixExpression<
                    const MatrixExpression< const L1, const R1, O1 >,
                    const MatrixExpression< const L1, const R1, O1 >,
                    M_TRANS >,
                VM_MULT, ROW >& rhs ) {
            Matrix< T > m( rhs.rhs().rhs() );
            Vector< T, ROW > v( rhs.lhs() );
            mv_mult( m, v, lhs, MagmaNoTrans, -1, 1 );
        }
    };
    /* Rank 1 update */
    // A = v1 * t( v2 )
    template< typename T, VecType M, VecType M1 >
    class OpExecutor< Matrix< T >, M_ASSIGN, 
            MatrixExpression< const Vector< T, M1 >, 
                const Vector< T, M >, V_OUTER > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< const Vector< T, M1 >, 
                    const Vector< T, M >, V_OUTER >& rhs ) {
            lhs = 0;
            v_outer( rhs.lhs(), rhs.rhs(), lhs, 1 );
        }
    };
    // A = v1 * t( v2 ) * a
    template< typename T, VecType M, VecType M1 >
    class OpExecutor< Matrix< T >, M_ASSIGN,
            MatrixExpression< const MatrixExpression< const Vector< T, M1 >, 
                const Vector< T, M >, V_OUTER >, const int, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const MatrixExpression< const Vector< T, M1 >, 
                        const Vector< T, M >, V_OUTER >, 
                    const int, M_SCALE >& rhs ) {
            lhs = 0;
            v_outer( rhs.lhs().lhs(), rhs.lhs().rhs(), lhs, rhs.rhs() );
        }
    };
    template< typename T, VecType M, VecType M1 >
    class OpExecutor< Matrix< T >, M_ASSIGN,
            MatrixExpression< const MatrixExpression< const Vector< T, M1 >, 
                const Vector< T, M >, V_OUTER >, const float, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const MatrixExpression< const Vector< T, M1 >, 
                        const Vector< T, M >, V_OUTER >, 
                    const float, M_SCALE >& rhs ) {
            lhs = 0;
            v_outer( rhs.lhs().lhs(), rhs.lhs().rhs(), lhs, rhs.rhs() );
        }
    };
    template< typename T, VecType M, VecType M1 >
    class OpExecutor< Matrix< T >, M_ASSIGN,
            MatrixExpression< const MatrixExpression< const Vector< T, M1 >, 
                const Vector< T, M >, V_OUTER >, const double, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const MatrixExpression< const Vector< T, M1 >, 
                        const Vector< T, M >, V_OUTER >, 
                    const double, M_SCALE >& rhs ) {
            lhs = 0;
            v_outer( rhs.lhs().lhs(), rhs.lhs().rhs(), lhs, rhs.rhs() );
        }
    };
    // A += v1 * t( v2 )
    template< typename T, VecType M, VecType M1 >
    class OpExecutor< Matrix< T >, M_INPLACE_ADD, 
            MatrixExpression< const Vector< T, M1 >, 
                const Vector< T, M >, V_OUTER > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< const Vector< T, M1 >, 
                    const Vector< T, M >, V_OUTER >& rhs ) {
            v_outer( rhs.lhs(), rhs.rhs(), lhs, 1 );
        }
    };
    // A += v1 * t( v2 ) * a
    template< typename T, VecType M, VecType M1 >
    class OpExecutor< Matrix< T >, M_INPLACE_ADD,
            MatrixExpression< const MatrixExpression< const Vector< T, M1 >, 
                const Vector< T, M >, V_OUTER >, const int, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const MatrixExpression< const Vector< T, M1 >, 
                        const Vector< T, M >, V_OUTER >, 
                    const int, M_SCALE >& rhs ) {
            v_outer( rhs.lhs().lhs(), rhs.lhs().rhs(), lhs, rhs.rhs() );
        }
    };
    template< typename T, VecType M, VecType M1 >
    class OpExecutor< Matrix< T >, M_INPLACE_ADD,
            MatrixExpression< const MatrixExpression< const Vector< T, M1 >, 
                const Vector< T, M >, V_OUTER >, const float, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const MatrixExpression< const Vector< T, M1 >, 
                        const Vector< T, M >, V_OUTER >, 
                    const float, M_SCALE >& rhs ) {
            v_outer( rhs.lhs().lhs(), rhs.lhs().rhs(), lhs, rhs.rhs() );
        }
    };
    template< typename T, VecType M, VecType M1 >
    class OpExecutor< Matrix< T >, M_INPLACE_ADD,
            MatrixExpression< const MatrixExpression< const Vector< T, M1 >, 
                const Vector< T, M >, V_OUTER >, const double, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const MatrixExpression< const Vector< T, M1 >, 
                        const Vector< T, M >, V_OUTER >, 
                    const double, M_SCALE >& rhs ) {
            v_outer( rhs.lhs().lhs(), rhs.lhs().rhs(), lhs, rhs.rhs() );
        }
    };
    // A -= v1 * t( v2 )
    template< typename T, VecType M, VecType M1 >
    class OpExecutor< Matrix< T >, M_INPLACE_SUB, 
            MatrixExpression< const Vector< T, M1 >, 
                const Vector< T, M >, V_OUTER > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< const Vector< T, M1 >, 
                    const Vector< T, M >, V_OUTER >& rhs ) {
            v_outer( rhs.lhs(), rhs.rhs(), lhs, -1 );
        }
    };
    // A -= v1 * t( v2 ) * a
    template< typename T, VecType M, VecType M1 >
    class OpExecutor< Matrix< T >, M_INPLACE_SUB,
            MatrixExpression< const MatrixExpression< const Vector< T, M1 >, 
                const Vector< T, M >, V_OUTER >, const int, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const MatrixExpression< const Vector< T, M1 >, 
                        const Vector< T, M >, V_OUTER >, 
                    const int, M_SCALE >& rhs ) {
            v_outer( rhs.lhs().lhs(), rhs.lhs().rhs(), lhs, -rhs.rhs() );
        }
    };
    template< typename T, VecType M, VecType M1 >
    class OpExecutor< Matrix< T >, M_INPLACE_SUB,
            MatrixExpression< const MatrixExpression< const Vector< T, M1 >, 
                const Vector< T, M >, V_OUTER >, const float, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const MatrixExpression< const Vector< T, M1 >, 
                        const Vector< T, M >, V_OUTER >, 
                    const float, M_SCALE >& rhs ) {
            v_outer( rhs.lhs().lhs(), rhs.lhs().rhs(), lhs, -rhs.rhs() );
        }
    };
    template< typename T, VecType M, VecType M1 >
    class OpExecutor< Matrix< T >, M_INPLACE_SUB,
            MatrixExpression< const MatrixExpression< const Vector< T, M1 >, 
                const Vector< T, M >, V_OUTER >, const double, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const MatrixExpression< const Vector< T, M1 >, 
                        const Vector< T, M >, V_OUTER >, 
                    const double, M_SCALE >& rhs ) {
            v_outer( rhs.lhs().lhs(), rhs.lhs().rhs(), lhs, -rhs.rhs() );
        }
    };
    // A = expression( v1 ) * t( v2 )
    template< typename T, VecType M, VecType M1, 
            typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_ASSIGN, 
            MatrixExpression< 
                const VectorExpression< const T, const L, const R, O, M1 >, 
                const Vector< T, M >, V_OUTER > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const VectorExpression< const T, const L, const R, O, M1 >, 
                    const Vector< T, M >, V_OUTER >& rhs ) {
            lhs = 0;
            Vector< T, M1 > temp( rhs.lhs() );
            v_outer( temp, rhs.rhs(), lhs, 1 );
        }
    };
    // A = expression( v1 ) * t( v2 ) * a
    template< typename T, VecType M, VecType M1, 
            typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_ASSIGN,
            MatrixExpression< const MatrixExpression<
                const VectorExpression< const T, const L, const R, O, M1 >, 
                const Vector< T, M >, V_OUTER >, const int, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const MatrixExpression< 
                        const VectorExpression< const T, const L,
                            const R, O, M1 >, 
                        const Vector< T, M >, V_OUTER >, 
                    const int, M_SCALE >& rhs ) {
            lhs = 0;
            Vector< T, M1 > temp( rhs.lhs().lhs() );
            v_outer( temp, rhs.lhs().rhs(), lhs, rhs.rhs() );
        }
    };
    template< typename T, VecType M, VecType M1, 
            typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_ASSIGN,
            MatrixExpression< const MatrixExpression<
                const VectorExpression< const T, const L, const R, O, M1 >, 
                const Vector< T, M >, V_OUTER >, const float, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const MatrixExpression< 
                        const VectorExpression< const T, const L,
                            const R, O, M1 >, 
                        const Vector< T, M >, V_OUTER >, 
                    const float, M_SCALE >& rhs ) {
            lhs = 0;
            Vector< T, M1 > temp( rhs.lhs().lhs() );
            v_outer( temp, rhs.lhs().rhs(), lhs, rhs.rhs() );
        }
    };
    template< typename T, VecType M, VecType M1, 
            typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_ASSIGN,
            MatrixExpression< const MatrixExpression<
                const VectorExpression< const T, const L, const R, O, M1 >, 
                const Vector< T, M >, V_OUTER >, const double, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const MatrixExpression< 
                        const VectorExpression< const T, const L,
                            const R, O, M1 >, 
                        const Vector< T, M >, V_OUTER >, 
                    const double, M_SCALE >& rhs ) {
            lhs = 0;
            Vector< T, M1 > temp( rhs.lhs().lhs() );
            v_outer( temp, rhs.lhs().rhs(), lhs, rhs.rhs() );
        }
    };
    // A += expression( v1 ) * t( v2 )
    template< typename T, VecType M, VecType M1, 
            typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_INPLACE_ADD, 
            MatrixExpression< const VectorExpression< const T, const L,
                            const R, O, M1 >, 
                const Vector< T, M >, V_OUTER > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< const VectorExpression< const T, const L,
                            const R, O, M1 >, 
                    const Vector< T, M >, V_OUTER >& rhs ) {
            Vector< T, M1 > temp( rhs.lhs() );
            v_outer( temp, rhs.rhs(), lhs, 1 );
        }
    };
    // A += expression( v1 ) * t( v2 ) * a
    template< typename T, VecType M, VecType M1, 
            typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_INPLACE_ADD,
            MatrixExpression< const MatrixExpression< 
                const VectorExpression< const T, const L,
                            const R, O, M1 >, 
                const Vector< T, M >, V_OUTER >, const int, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const MatrixExpression< 
                        const VectorExpression< const T, const L,
                            const R, O, M1 >, 
                        const Vector< T, M >, V_OUTER >, 
                    const int, M_SCALE >& rhs ) {
            Vector< T, M1 > temp( rhs.lhs().lhs() );
            v_outer( temp, rhs.lhs().rhs(), lhs, rhs.rhs() );
        }
    };
    template< typename T, VecType M, VecType M1, 
            typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_INPLACE_ADD,
            MatrixExpression< const MatrixExpression< 
                const VectorExpression< const T, const L,
                            const R, O, M1 >, 
                const Vector< T, M >, V_OUTER >, const float, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const MatrixExpression< 
                        const VectorExpression< const T, const L,
                            const R, O, M1 >, 
                        const Vector< T, M >, V_OUTER >, 
                    const float, M_SCALE >& rhs ) {
            Vector< T, M1 > temp( rhs.lhs().lhs() );
            v_outer( temp, rhs.lhs().rhs(), lhs, rhs.rhs() );
        }
    };
    template< typename T, VecType M, VecType M1, 
            typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_INPLACE_ADD,
            MatrixExpression< const MatrixExpression< 
                const VectorExpression< const T, const L,
                            const R, O, M1 >, 
                const Vector< T, M >, V_OUTER >, const double, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const MatrixExpression< 
                        const VectorExpression< const T, const L,
                            const R, O, M1 >, 
                        const Vector< T, M >, V_OUTER >, 
                    const double, M_SCALE >& rhs ) {
            Vector< T, M1 > temp( rhs.lhs().lhs() );
            v_outer( temp, rhs.lhs().rhs(), lhs, rhs.rhs() );
        }
    };
    // A -= expression( v1 ) * t( v2 )
    template< typename T, VecType M, VecType M1, 
            typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_INPLACE_SUB, 
            MatrixExpression< 
                const VectorExpression< const T, const L,
                            const R, O, M1 >, 
                const Vector< T, M >, V_OUTER > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const VectorExpression< const T, const L,
                            const R, O, M1 >, 
                    const Vector< T, M >, V_OUTER >& rhs ) {
            Vector< T, M1 > temp( rhs.lhs() );
            v_outer( temp , rhs.rhs(), lhs, -1 );
        }
    };
    // A -= v1 * t( v2 ) * a
    template< typename T, VecType M, VecType M1, 
            typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_INPLACE_SUB,
            MatrixExpression< const MatrixExpression< 
                const VectorExpression< const T, const L,
                            const R, O, M1 >, 
                const Vector< T, M >, V_OUTER >, const int, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const MatrixExpression< 
                        const VectorExpression< const T, const L,
                            const R, O, M1 >, 
                        const Vector< T, M >, V_OUTER >, 
                    const int, M_SCALE >& rhs ) {
            Vector< T, M1 > temp( rhs.lhs().lhs() );
            v_outer( temp, rhs.lhs().rhs(), lhs, -rhs.rhs() );
        }
    };
    template< typename T, VecType M, VecType M1, 
            typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_INPLACE_SUB,
            MatrixExpression< const MatrixExpression< 
                const VectorExpression< const T, const L,
                            const R, O, M1 >, 
                const Vector< T, M >, V_OUTER >, const float, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const MatrixExpression< 
                        const VectorExpression< const T, const L,
                            const R, O, M1 >, 
                        const Vector< T, M >, V_OUTER >, 
                    const float, M_SCALE >& rhs ) {
            Vector< T, M1 > temp( rhs.lhs().lhs() );
            v_outer( temp, rhs.lhs().rhs(), lhs, -rhs.rhs() );
        }
    };
    template< typename T, VecType M, VecType M1, 
            typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_INPLACE_SUB,
            MatrixExpression< const MatrixExpression< 
                const VectorExpression< const T, const L,
                            const R, O, M1 >, 
                const Vector< T, M >, V_OUTER >, const double, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const MatrixExpression< 
                        const VectorExpression< const T, const L,
                            const R, O, M1 >, 
                        const Vector< T, M >, V_OUTER >, 
                    const double, M_SCALE >& rhs ) {
            Vector< T, M1 > temp( rhs.lhs().lhs() );
            v_outer( temp, rhs.lhs().rhs(), lhs, -rhs.rhs() );
        }
    };
    // A = v1 * t( expression( v2 ) )
    template< typename T, VecType M, VecType M1, 
            typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_ASSIGN, 
            MatrixExpression< const Vector< T, M1 >, 
                const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< const Vector< T, M1 >, 
                    const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >& rhs ) {
            lhs = 0;
            Vector< T, M > temp( rhs.rhs() );
            v_outer( rhs.lhs(), temp, lhs, 1 );
        }
    };
    // A = v1 * t( expression( v2 ) ) * a
    template< typename T, VecType M, VecType M1, 
            typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_ASSIGN,
            MatrixExpression< const MatrixExpression< const Vector< T, M1 >, 
                const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >, const int, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const MatrixExpression< const Vector< T, M1 >, 
                        const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >, 
                    const int, M_SCALE >& rhs ) {
            lhs = 0;
            Vector< T, M > temp( rhs.lhs().rhs() );
            v_outer( rhs.lhs().lhs(), temp, lhs, rhs.rhs() );
        }
    };
    template< typename T, VecType M, VecType M1, 
            typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_ASSIGN,
            MatrixExpression< const MatrixExpression< const Vector< T, M1 >, 
                const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >, const float, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const MatrixExpression< const Vector< T, M1 >, 
                        const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >, 
                    const float, M_SCALE >& rhs ) {
            lhs = 0;
            Vector< T, M > temp( rhs.lhs().rhs() );
            v_outer( rhs.lhs().lhs(), temp, lhs, rhs.rhs() );
        }
    };
    template< typename T, VecType M, VecType M1, 
            typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_ASSIGN,
            MatrixExpression< const MatrixExpression< const Vector< T, M1 >, 
                const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >, const double, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const MatrixExpression< const Vector< T, M1 >, 
                        const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >, 
                    const double, M_SCALE >& rhs ) {
            lhs = 0;
            Vector< T, M > temp( rhs.lhs().rhs() );
            v_outer( rhs.lhs().lhs(), temp, lhs, rhs.rhs() );
        }
    };
    // A += v1 * t( expression( v2 ) )
    template< typename T, VecType M, VecType M1, 
            typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_INPLACE_ADD, 
            MatrixExpression< const Vector< T, M1 >, 
                const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< const Vector< T, M1 >, 
                    const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >& rhs ) {
            Vector< T, M > temp( rhs.rhs() );
            v_outer( rhs.lhs(), temp, lhs, 1 );
        }
    };
    // A += v1 * t( expression( v2 ) ) * a
    template< typename T, VecType M, VecType M1, 
            typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_INPLACE_ADD,
            MatrixExpression< const MatrixExpression< const Vector< T, M1 >, 
                const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >, const int, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const MatrixExpression< const Vector< T, M1 >, 
                        const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >, 
                    const int, M_SCALE >& rhs ) {
            Vector< T, M > temp( rhs.lhs().rhs() );
            v_outer( rhs.lhs().lhs(), temp, lhs, rhs.rhs() );
        }
    };
    template< typename T, VecType M, VecType M1, 
            typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_INPLACE_ADD,
            MatrixExpression< const MatrixExpression< const Vector< T, M1 >, 
                const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >, const float, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const MatrixExpression< const Vector< T, M1 >, 
                        const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >, 
                    const float, M_SCALE >& rhs ) {
            Vector< T, M > temp( rhs.lhs().rhs() );
            v_outer( rhs.lhs().lhs(), temp, lhs, rhs.rhs() );
        }
    };
    template< typename T, VecType M, VecType M1, 
            typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_INPLACE_ADD,
            MatrixExpression< const MatrixExpression< const Vector< T, M1 >, 
                const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >, const double, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const MatrixExpression< const Vector< T, M1 >, 
                        const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >, 
                    const double, M_SCALE >& rhs ) {
            Vector< T, M > temp( rhs.lhs().rhs() );
            v_outer( rhs.lhs().lhs(), temp, lhs, rhs.rhs() );
        }
    };
    // A -= v1 * t( expression( v2 ) )
    template< typename T, VecType M, VecType M1, 
            typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_INPLACE_SUB, 
            MatrixExpression< const Vector< T, M1 >, 
                const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< const Vector< T, M1 >, 
                    const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >& rhs ) {
            Vector< T, M > temp( rhs.rhs() );
            v_outer( rhs.lhs(), temp, lhs, -1 );
        }
    };
    // A -= v1 * t( expression( v2 ) ) * a
    template< typename T, VecType M, VecType M1, 
            typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_INPLACE_SUB,
            MatrixExpression< const MatrixExpression< const Vector< T, M1 >, 
                const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >, const int, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const MatrixExpression< const Vector< T, M1 >, 
                        const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >, 
                    const int, M_SCALE >& rhs ) {
            Vector< T, M > temp( rhs.lhs().rhs() );
            v_outer( rhs.lhs().lhs(), temp, lhs, -rhs.rhs() );
        }
    };
    template< typename T, VecType M, VecType M1, 
            typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_INPLACE_SUB,
            MatrixExpression< const MatrixExpression< const Vector< T, M1 >, 
                const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >, const float, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const MatrixExpression< const Vector< T, M1 >, 
                        const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >, 
                    const float, M_SCALE >& rhs ) {
            Vector< T, M > temp( rhs.lhs().rhs() );
            v_outer( rhs.lhs().lhs(), temp, lhs, -rhs.rhs() );
        }
    };
    template< typename T, VecType M, VecType M1, 
            typename L, typename R, Oper O >
    class OpExecutor< Matrix< T >, M_INPLACE_SUB,
            MatrixExpression< const MatrixExpression< const Vector< T, M1 >, 
                const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >, const double, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const MatrixExpression< const Vector< T, M1 >, 
                        const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >, 
                    const double, M_SCALE >& rhs ) {
            Vector< T, M > temp( rhs.lhs().rhs() );
            v_outer( rhs.lhs().lhs(), temp, lhs, -rhs.rhs() );
        }
    };
    // A = expression( v1 ) * t( expression( v2 ) )
    template< typename T, VecType M, VecType M1, 
            typename L, typename R, Oper O,
            typename L1, typename R1, Oper O1 >
    class OpExecutor< Matrix< T >, M_ASSIGN, 
            MatrixExpression< const VectorExpression< const T, const L1,
                            const R1, O1, M1 >, 
                const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< const VectorExpression< const T, const L1,
                            const R1, O1, M1 >, 
                    const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >& rhs ) {
            lhs = 0;
            Vector< T, M1 > temp1( rhs.lhs() );
            Vector< T, M > temp( rhs.rhs() );
            v_outer( temp1, temp, lhs, 1 );
        }
    };
    // A = expression( v1 ) * t( expression( v2 ) ) * a
    template< typename T, VecType M, VecType M1, 
            typename L, typename R, Oper O,
            typename L1, typename R1, Oper O1 >
    class OpExecutor< Matrix< T >, M_ASSIGN,
            MatrixExpression< const MatrixExpression< const VectorExpression< const T, const L1,
                            const R1, O1, M1 >, 
                const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >, const int, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const MatrixExpression< const VectorExpression< const T, const L1,
                            const R1, O1, M1 >, 
                        const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >, 
                    const int, M_SCALE >& rhs ) {
            lhs = 0;
            Vector< T, M1 > temp1( rhs.lhs().lhs() );
            Vector< T, M > temp( rhs.lhs().rhs() );
            v_outer( temp1, temp, lhs, rhs.rhs() );
        }
    };
    template< typename T, VecType M, VecType M1, 
            typename L, typename R, Oper O,
            typename L1, typename R1, Oper O1 >
    class OpExecutor< Matrix< T >, M_ASSIGN,
            MatrixExpression< const MatrixExpression< const VectorExpression< const T, const L1,
                            const R1, O1, M1 >, 
                const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >, const float, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const MatrixExpression< const VectorExpression< const T, const L1,
                            const R1, O1, M1 >, 
                        const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >, 
                    const float, M_SCALE >& rhs ) {
            lhs = 0;
            Vector< T, M1 > temp1( rhs.lhs().lhs() );
            Vector< T, M > temp( rhs.lhs().rhs() );
            v_outer( temp1, temp, lhs, rhs.rhs() );
        }
    };
    template< typename T, VecType M, VecType M1, 
            typename L, typename R, Oper O,
            typename L1, typename R1, Oper O1 >
    class OpExecutor< Matrix< T >, M_ASSIGN,
            MatrixExpression< const MatrixExpression< const VectorExpression< const T, const L1,
                            const R1, O1, M1 >, 
                const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >, const double, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const MatrixExpression< const VectorExpression< const T, const L1,
                            const R1, O1, M1 >, 
                        const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >, 
                    const double, M_SCALE >& rhs ) {
            lhs = 0;
            Vector< T, M1 > temp1( rhs.lhs().lhs() );
            Vector< T, M > temp( rhs.lhs().rhs() );
            v_outer( temp1, temp, lhs, rhs.rhs() );
        }
    };
    // A += expression( v1 ) * t( expression( v2 ) )
    template< typename T, VecType M, VecType M1, 
            typename L, typename R, Oper O,
            typename L1, typename R1, Oper O1 >
    class OpExecutor< Matrix< T >, M_INPLACE_ADD, 
            MatrixExpression< const VectorExpression< const T, const L1,
                            const R1, O1, M1 >, 
                const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< const VectorExpression< const T, const L1,
                            const R1, O1, M1 >, 
                    const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >& rhs ) {
            Vector< T, M1 > temp1( rhs.lhs() );
            Vector< T, M > temp( rhs.rhs() );
            v_outer( temp1, temp, lhs, 1 );
        }
    };
    // A += expression( v1 ) * t( expression( v2 ) ) * a
    template< typename T, VecType M, VecType M1, 
            typename L, typename R, Oper O,
            typename L1, typename R1, Oper O1 >
    class OpExecutor< Matrix< T >, M_INPLACE_ADD,
            MatrixExpression< const MatrixExpression< const VectorExpression< const T, const L1,
                            const R1, O1, M1 >, 
                const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >, const int, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const MatrixExpression< const VectorExpression< const T, const L1,
                            const R1, O1, M1 >, 
                        const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >, 
                    const int, M_SCALE >& rhs ) {
            Vector< T, M1 > temp1( rhs.lhs() );
            Vector< T, M > temp( rhs.lhs().lhs() );
            v_outer( temp1 , temp, lhs, rhs.rhs() );
        }
    };
    template< typename T, VecType M, VecType M1, 
            typename L, typename R, Oper O,
            typename L1, typename R1, Oper O1 >
    class OpExecutor< Matrix< T >, M_INPLACE_ADD,
            MatrixExpression< const MatrixExpression< const VectorExpression< const T, const L1,
                            const R1, O1, M1 >, 
                const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >, const float, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const MatrixExpression< const VectorExpression< const T, const L1,
                            const R1, O1, M1 >, 
                        const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >, 
                    const float, M_SCALE >& rhs ) {
            Vector< T, M1 > temp1( rhs.lhs() );
            Vector< T, M > temp( rhs.lhs().lhs() );
            v_outer( temp1 , temp, lhs, rhs.rhs() );
        }
    };
    template< typename T, VecType M, VecType M1, 
            typename L, typename R, Oper O,
            typename L1, typename R1, Oper O1 >
    class OpExecutor< Matrix< T >, M_INPLACE_ADD,
            MatrixExpression< const MatrixExpression< const VectorExpression< const T, const L1,
                            const R1, O1, M1 >, 
                const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >, const double, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const MatrixExpression< const VectorExpression< const T, const L1,
                            const R1, O1, M1 >, 
                        const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >, 
                    const double, M_SCALE >& rhs ) {
            Vector< T, M1 > temp1( rhs.lhs() );
            Vector< T, M > temp( rhs.lhs().lhs() );
            v_outer( temp1 , temp, lhs, rhs.rhs() );
        }
    };
    // A -= expression( v1 ) * t( expression( v2 ) )
    template< typename T, VecType M, VecType M1, 
            typename L, typename R, Oper O,
            typename L1, typename R1, Oper O1 >
    class OpExecutor< Matrix< T >, M_INPLACE_SUB, 
            MatrixExpression< const VectorExpression< const T, const L1,
                            const R1, O1, M1 >, 
                const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< const VectorExpression< const T, const L1,
                            const R1, O1, M1 >, 
                    const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >& rhs ) {
            Vector< T, M1 > temp1( rhs.lhs() );
            Vector< T, M > temp( rhs.rhs() );
            v_outer( temp1, temp, lhs, -1 );
        }
    };
    // A -= expression( v1 ) * t( expression( v2 ) ) * a
    template< typename T, VecType M, VecType M1, 
            typename L, typename R, Oper O,
            typename L1, typename R1, Oper O1 >
    class OpExecutor< Matrix< T >, M_INPLACE_SUB,
            MatrixExpression< const MatrixExpression< const VectorExpression< const T, const L1,
                            const R1, O1, M1 >, 
                const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >, const int, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const MatrixExpression< const VectorExpression< const T, const L1,
                            const R1, O1, M1 >, 
                        const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >, 
                    const int, M_SCALE >& rhs ) {
            Vector< T, M1 > temp1( rhs.lhs() );
            Vector< T, M > temp( rhs.lhs().lhs() );
            v_outer( temp1 , temp, lhs, -rhs.rhs() );
        }
    };
    template< typename T, VecType M, VecType M1, 
            typename L, typename R, Oper O,
            typename L1, typename R1, Oper O1 >
    class OpExecutor< Matrix< T >, M_INPLACE_SUB,
            MatrixExpression< const MatrixExpression< const VectorExpression< const T, const L1,
                            const R1, O1, M1 >, 
                const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >, const float, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const MatrixExpression< const VectorExpression< const T, const L1,
                            const R1, O1, M1 >, 
                        const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >, 
                    const float, M_SCALE >& rhs ) {
            Vector< T, M1 > temp1( rhs.lhs() );
            Vector< T, M > temp( rhs.lhs().lhs() );
            v_outer( temp1 , temp, lhs, -rhs.rhs() );
        }
    };
    template< typename T, VecType M, VecType M1, 
            typename L, typename R, Oper O,
            typename L1, typename R1, Oper O1 >
    class OpExecutor< Matrix< T >, M_INPLACE_SUB,
            MatrixExpression< const MatrixExpression< const VectorExpression< const T, const L1,
                            const R1, O1, M1 >, 
                const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >, const double, M_SCALE > > {
    public:
        static void apply( Matrix< T >& lhs, 
                const MatrixExpression< 
                    const MatrixExpression< const VectorExpression< const T, const L1,
                            const R1, O1, M1 >, 
                        const VectorExpression< const T, const L,
                            const R, O, M >, V_OUTER >, 
                    const double, M_SCALE >& rhs ) {
            Vector< T, M1 > temp1( rhs.lhs() );
            Vector< T, M > temp( rhs.lhs().lhs() );
            v_outer( temp1 , temp, lhs, -rhs.rhs() );
        }
    };
    
    
}

#endif /* XMAGMA_OPERATIONS_H */

