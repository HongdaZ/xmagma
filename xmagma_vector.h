/* 
 * File:   xmagma_vector.h
 * Author: hzhang
 * Definition of vector
 * Created on September 9, 2018, 9:29 AM
 */

#ifndef XMAGMA_VECTOR_H
#define XMAGMA_VECTOR_H

#ifdef HAVE_CUBLAS
#include "cublas_v2.h"    
#include "magma_v2.h"
#else 
#include "magma.h" // for clmagma
#endif

#include "xmagma_forwards.h"
#include "xmagma_util.h"
#include "xmagma_tools.h"
#include "xmagma_R_array.h"

namespace xmagma {
    template < typename T, VecType M > class Vector {     
        typedef Vector< T, M > SelfType;
    public: 
        typedef Scalar< T > ValueType;
        typedef magma_int_t size_type;
        // Default constructor. Does not allocate memory
        explicit Vector(): size1_( 0 ) {}
        
        /*  Construct the vector with given dimensions on memory
         *  len                  length of vector
         *  queue             optional queue in which the matrix is created                          
         *  (default argument is the static variable queue)
         */
        explicit Vector( size_type len,     
                magma_queue_t queue = Backend::get_queue() );
        
        /* Construct vector from vector expression
         * L                    type of left hand side argument 
         * R                    type of right hand side argument
         * O                   type of operator
         */
        template< typename L, typename R, Oper O >
        explicit Vector( VectorExpression< const L, const R, O, M > const& 
            proxy );
        
        /* Deep copy of the Vector */
        Vector( const SelfType& other );
        ~Vector() {
            magma_free( elements_ );
        }
        /* Operators whose return value is the reference of the vector 
         * itself
         */
        // v = a
        SelfType& operator=( const T a );
        // v1 = v2
        SelfType& operator=( const SelfType& other );
        template< typename L, typename R, Oper O>
        SelfType& operator=( const VectorExpression< const L, const R,
                O, M >& proxy );
        // v1 = trans( v2 )
        template< VecType M2 >
        SelfType& operator=( const VectorExpression< const Vector< T, M2 >,
                const Vector< T, M2 >, V_TRANS, M >& proxy );
        /* Matrix-vector operations */
        // v1 = A * v2
        SelfType& operator=( const VectorExpression< const Matrix< T >,
                const Vector< T, M >, MV_MULT, M >& proxy );
        // v1 = v2 * A
        SelfType& operator=( const VectorExpression< const Vector< T, M >,
                const Matrix< T >, VM_MULT, M >& proxy );
        // v1 = t( A ) * v2
        SelfType& operator=( const VectorExpression< const MatrixExpression<
        const Matrix< T >, const Matrix< T >, M_TRANS >,
                const Vector< T, M >, MV_MULT, M >& proxy );
        // v1 = v2 * t( A )
        SelfType& operator=( const VectorExpression< const Vector< T, M >,
                const MatrixExpression< const Matrix< T >,
                const Matrix< T >, M_TRANS >,
                 MV_MULT, M >& proxy );
        
        // v1 += v2
        template< typename L, typename R, Oper O>
        SelfType& operator+=( const VectorExpression< const L,
                const R, O, M > & proxy );
        SelfType& operator+=( const SelfType& other );
        // v1 -= v2
        template< typename L, typename R, Oper O >
        SelfType& operator-=( const VectorExpression< const L,
                const R, O, M >& proxy );
        SelfType& operator-=( const SelfType& other );
        // v1 *= a inplace scale a Vector
        SelfType& operator*=( T );
        SelfType& operator/=( T );
        // -v1
        VectorExpression< const SelfType, const SelfType, V_NEGATIVE, M > 
        operator-() const;
        
        /* Return dimensions of the vector */
        size_type size() const { return size1_; }
        size_type size1() const { return size1_; }
        size_type size2() const { return size2_; }
        /* Return pointer of elements */
        const MagmaPtr< T >& get_pointer() const { return elements_; }
        MagmaPtr< T >& get_pointer() { return elements_; }
    private: 
        MagmaPtr< T > elements_;
        size_type size1_; // length of vector
        size_type size2_; // 1
    };  //Vector
    // print Vector
    template< typename T, VecType M >
    void print( Vector< T, M >& a ) {};
    template<>
    void print( Vector< float, ROW >& a ) {
        float* b;
        magma_int_t m = a.size();
        magma_smalloc_cpu ( &b , m ); // host memory for a
        RVector< float > temp( b, m );
        magma_sgetvector( a.size(), a.get_pointer(), 1, temp.begin(), 1, 
                Backend::get_queue() );
        std::cout << temp;
    };
    template<>
    void print( Vector< float, COL >& a ) {
        float* b;
        magma_int_t m = a.size();
        magma_smalloc_cpu ( &b , m ); // host memory for a
        RVector< float > temp( b, m );
        magma_sgetvector( a.size(), a.get_pointer(), 1, temp.begin(), 1, 
                Backend::get_queue() );
        printf( "[\n" );
        for( magma_int_t i = 0; i < m; ++i ) {
            printf( "%f\n", temp[ i ] );
        }
        printf( "];\n" );
    };
    template<>
    void print( Vector< double, ROW >& a ) {
        double* b;
        magma_int_t m = a.size();
        magma_dmalloc_cpu ( &b , m ); // host memory for a
        RVector< double > temp( b, m);
        magma_dgetvector( a.size(), a.get_pointer(), 1, temp.begin(), 1, 
                Backend::get_queue() );
        std::cout << temp;
    };
    template<>
    void print( Vector< double, COL >& a ) {
        double* b;
        magma_int_t m = a.size();
        magma_dmalloc_cpu ( &b , m ); // host memory for a
        RVector< double > temp( b, m);
        magma_dgetvector( a.size(), a.get_pointer(), 1, temp.begin(), 1, 
                Backend::get_queue() );
        printf( "[\n" );
        for( magma_int_t i = 0; i < m; ++i ) {
            printf( "%f\n", temp[ i ] );
        }
        printf( "];\n" );
    };
}


#endif /* XMAGMA_VECTOR_H */

