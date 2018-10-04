/* 
 * File:   xmagma_R_array.h
 * Author: hzhang
 * matrix and vector from R
 * Created on July 21, 2018, 9:56 PM
 */

#ifndef XMAGMA_R_ARRAY_H
#define XMAGMA_R_ARRAY_H

#include <iostream>
#include <omp.h>
#include <xmagma_util.h>

#ifdef HAVE_CUBLAS
#include "cublas_v2.h"    
#include "magma_v2.h"
#else 
#include "magma.h" // for clmagma
#endif
#include "magma_lapack.h" 

namespace xmagma {
    template < typename T >
    class RVector {
    T* start_;
    magma_int_t len_;
    bool r_;
    public:
        RVector( T* ptr, magma_int_t len ): start_( ptr ),
                len_( len ), r_( true ) {}
        RVector( magma_int_t len ): start_( NULL ), len_( len ), r_( false ) {
            host_creator< T >( &start_, len );
        }
        T &operator()( magma_int_t i ) { 
//            if( i >= len_ ){
//                std::cout << "subscript out of bounds" << std::endl;
//            }
            return start_[ i ]; }
        T &operator[]( magma_int_t i ) { 
            return this->operator()( i ); }
        T operator()( magma_int_t i ) const { 
//            if( i >= len_ ){
//                std::cout << "subscript out of bounds" << std::endl;
//            }
            return start_[ i ]; }
        T operator[]( magma_int_t i ) const { 
            return this->operator()( i ) ; }
        magma_int_t size() const { return len_; }
        T* begin(){ return &start_[ 0 ]; }
        const T* begin() const{ return &start_[ 0 ]; }
        T* end(){ return &start_[ 0 ] + len_; }
        ~RVector() {
            if( !r_ ) {
                magma_free_cpu( start_ );
            }
        }
        typedef magma_int_t type;
};
    template < typename T >
    class RMatrix{
    T* start_;
    magma_int_t row_;
    magma_int_t col_;
    bool r_;
public:
    RMatrix( T* ptr, magma_int_t nrow, magma_int_t ncol ):
    start_( ptr ), row_( nrow ), col_( ncol ), r_( true ) {}
    RMatrix( magma_int_t nrow, magma_int_t ncol ):
    start_( NULL ), row_( nrow ), col_( ncol ), r_( false ) {
        host_creator< T >( &start_, row_ * col_ );
    }
    T &operator()( magma_int_t i, magma_int_t j ) { 
//        if( i >= row_ || j >= col_ ){
//            std::cout << "subscript out of bounds" << std::endl;
//        }
        return start_[ j * row_ + i ]; }
    T operator()( magma_int_t i, magma_int_t j ) const { 
//        if( i >= row_ || j >= col_ ){
//            std::cout << "subscript out of bounds" << std::endl;
//        }
        return start_[ j * row_ + i]; }
    magma_int_t size1() const { return row_; }
    magma_int_t size2() const { return col_; }
    typedef magma_int_t size_type;
    T* begin(){ return &start_[ 0 ]; }
    const T* begin() const{ return &start_[ 0 ]; }
    ~RMatrix(){
        if( !r_ ) {
            magma_free_cpu( start_ );
        }
    }
    };
    /* Overload << operator */
    //RMatrix
    template< typename T >
    inline std::ostream&
    operator<<( std::ostream& out, const RMatrix< T >& mat ) {
        out << "[" << "\n";
        for ( magma_int_t i = 0; i < mat.size1(); ++i ) {
            for ( magma_int_t j = 0; j < mat.size2(); ++j ) {
                out << mat( i, j ) << "\t";
            }
            out << "\n";
        }
        out << "];" << "\n";
        return out;
    }
    //RVector
    template< typename T >
    inline std::ostream&
    operator<<( std::ostream& out, const RVector< T >& vec ) {
        out << "[" << "\n";
        for ( magma_int_t i = 0; i < vec.size(); ++i ) {
                out << vec( i ) << "\t";
        }
        out <<"\n" << "];" << "\n";
        return out;
    }
    template< typename T1, typename T2 >
    void host_copy( const RVector< T1 >& v1, RVector< T2 >& v2 ) {
        const T1 *V1PTR = v1.begin();
        T2 *V2PTR = v2.begin();
        int n = v1.size();
        magma_int_t i;
#pragma omp parallel for num_threads( 4 ) \
    shared( V1PTR , V2PTR,  n ) \
    private( i )
        for(  i = 0; i < v1.size(); ++ i ) {
            V2PTR[ i ] = V1PTR[ i ];
        }
    }
    template< typename T1, typename T2 >
    void host_copy( const RMatrix< T1 >& M1, RMatrix< T2 >& M2 ) {
        const T1 *M1PTR = M1.begin();
        T2 *M2PTR = M2.begin();
        int n = M1.size1() * M1.size2();
        magma_int_t i;
#pragma omp parallel for num_threads( 4 ) \
    shared( M1PTR , M2PTR,  n ) \
    private( i )
        for( i = 0; i < n ; ++ i ) {
            M2PTR[ i ] = M1PTR[ i ];
        }
    }
}

#endif /* XMAGMA_R_ARRAY_H */

