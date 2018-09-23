/* 
 * File:   xmagma_R_array.h
 * Author: hzhang
 * matrix and vector from R
 * Created on July 21, 2018, 9:56 PM
 */

#ifndef XMAGMA_R_ARRAY_H
#define XMAGMA_R_ARRAY_H

#include <iostream>

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
    public:
        RVector( T* ptr, magma_int_t len ): start_( ptr ), len_( len ){};
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
        T* end(){ return &start_[ 0 ] + len_; }
        typedef magma_int_t type;
};
    template < typename T >
    class RMatrix{
    T* start_;
    magma_int_t row_;
    magma_int_t col_;
public:
    RMatrix( T* ptr, magma_int_t nrow, magma_int_t ncol ):
    start_( ptr ), row_( nrow ), col_( ncol ){};
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
}

#endif /* XMAGMA_R_ARRAY_H */

