/* 
 * File:   xmagma_R_array.h
 * Author: hzhang
 * matrix and vector from R
 * Created on July 21, 2018, 9:56 PM
 */

#ifndef XMAGMA_R_ARRAY_H
#define XMAGMA_R_ARRAY_H
namespace xmagma {
    template < typename T >
    class RVector {
    T* start_;
    std::size_t len_;
    public:
        RVector( T* ptr, std::size_t len ): start_( ptr ), len_( len ){};
        T &operator()( std::size_t i ) { 
//            if( i >= len_ ){
//                std::cout << "subscript out of bounds" << std::endl;
//            }
            return start_[ i ]; }
        T &operator[]( std::size_t i ) { 
            return this->operator()( i ); }
        T operator()( std::size_t i ) const { 
//            if( i >= len_ ){
//                std::cout << "subscript out of bounds" << std::endl;
//            }
            return start_[ i ]; }
        T operator[]( std::size_t i ) const { 
            return this->operator()( i ) ; }
        std::size_t size() const { return len_; }
        T* begin(){ return &start_[ 0 ]; }
        T* end(){ return &start_[ 0 ] + len_; }
        typedef std::size_t type;
};
    template < typename T >
    class RMatrix{
    T* start_;
    std::size_t row_;
    std::size_t col_;
public:
    RMatrix( T* ptr, std::size_t nrow, std::size_t ncol ):
    start_( ptr ), row_( nrow ), col_( ncol ){};
    T &operator()( std::size_t i, std::size_t j ) { 
//        if( i >= row_ || j >= col_ ){
//            std::cout << "subscript out of bounds" << std::endl;
//        }
        return start_[ j * row_ + i ]; }
    T operator()( std::size_t i, std::size_t j ) const { 
//        if( i >= row_ || j >= col_ ){
//            std::cout << "subscript out of bounds" << std::endl;
//        }
        return start_[ j * row_ + i]; }
    std::size_t size1() const { return row_; }
    std::size_t size2() const { return col_; }
    typedef std::size_t size_type;
    T* begin(){ return &start_[ 0 ]; }
    };
}

#endif /* XMAGMA_R_ARRAY_H */

