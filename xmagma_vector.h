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
        explicit Vector( VectorExpression< const L, const R, O > const& 
            proxy );
        
        /* Deep copy of the Vector */
        Vector( const SelfType& other );
        ~Vector() {
            magma_free( elements_ );
        }
        /* Operators whose return value is the reference of the vector 
         * itself
         */
        // A = B
        SelfType& operator=( const SelfType& other );
        // A = a
        SelfType& operator=( const T a );
        template< typename L, typename R, Oper O>
        SelfType& operator=( const VectorExpression< const L, const R,
                O >& proxy );
        /* Matrix-vector operations */
        // v1 = A * v2
        SelfType& operator=( const VectorExpression< const Matrix< T >,
                const Vector< T, COL >, MV_MULT >& proxy );
        // v1 = t( A ) * v2
        SelfType& operator=( const VectorExpression< const MatrixExpression<
        const Matrix< T >, const Matrix< T >, M_TRANS >,
                const Vector< T, COL >, MV_MULT >& proxy );
        
        // A += B
        template< typename L, typename R, Oper O>
        SelfType& operator+=( const VectorExpression< const L,
                const R, O> & proxy );
        SelfType& operator+=( const SelfType& other );
        // A -= B;
        template< typename L, typename R, Oper O >
        SelfType& operator-=( const VectorExpression< const L,
                const R, O >& proxy );
        SelfType& operator-=( const SelfType& other );
        // A *= a inplace scale a Vector
        SelfType& operator*=( T );
        SelfType& operator/=( T );
        // -A
        VectorExpression< const SelfType, const SelfType, V_NEGATIVE > 
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
    template< typename T, VecType Major >
    void print( Vector< T, Major >& a ) {};
    template< VecType Major >
    void print( Vector< float, Major >& a ) {
        float* b;
        magma_int_t m = a.size();
        magma_smalloc_cpu ( &b , m ); // host memory for a
        RVector< float > temp( b, m );
        magma_sgetvector( a.size(), a.get_pointer(), 1, temp.begin(), 1, 
                Backend::get_queue() );
        std::cout << temp;
    };
    template< VecType Major >
    void print( Vector< double, Major >& a ) {
        double* b;
        magma_int_t m = a.size();
        magma_dmalloc_cpu ( &b , m ); // host memory for a
        RVector< double > temp( b, m);
        magma_dgetvector( a.size(), a.get_pointer(), 1, temp.begin(), 1, 
                Backend::get_queue() );
        std::cout << temp;
    };
}


#endif /* XMAGMA_VECTOR_H */

