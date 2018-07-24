/* 
 * File:   xmagma_tools.h
 * Author: hzhang
 * Tools for calculations
 * Created on July 21, 2018, 8:39 PM
 */

#ifndef XMAGMA_TOOLS_H
#define XMAGMA_TOOLS_H

#include "xmagma_forwards.h"

namespace xmagma {
    /* Calculate dimensions of matrix expressions */
    // General case: A + B, A - B, A * B
    template< typename L, typename R, Oper O > 
    class MatrixSize {
    public: 
        static magma_int_t size1( L& lhs, R& rhs ) { return lhs.size1(); }
        static magma_int_t size2( L& lhs, R& rhs ) { return rhs.size2(); }
    };
    
    // v %*% t( v )
    template< typename L, typename R >
    class MatrixSize< const L, const R, V_OUTER > {
    public:
        static magma_int_t size1( L& lhs, R& rhs ) { return lhs.size(); }
        static magma_int_t size2( L& lhs, R& rhs ) { return rhs.size() ; }
    };
    
    // A * a (A / a <=> A * 1 / a)
    template< typename AnyMatrix, typename T > 
    class MatrixSize< const AnyMatrix, const T, M_SCALE > {
        public:
        static magma_int_t size1( const AnyMatrix& lhs,
            const T& rhs ) { return lhs.size1(); }
        static magma_int_t size2( const AnyMatrix& lhs,
            const T& rhs ) { return lhs.size2(); }
    };
 
    // t( A )
    template< typename AnyMatrix >
    class MatrixSize< const AnyMatrix, const AnyMatrix, M_TRANS > {            
    public:
        static magma_int_t size1( const AnyMatrix& lhs, 
                                                const AnyMatrix& rhs ) 
        { return lhs.size2(); } 
        static magma_int_t size2( const AnyMatrix& lhs, 
                                                const AnyMatrix& rhs ) 
        { return lhs.size1(); } 
    };
} // xmagma                                                                                                     
#endif /* XMAGMA_TOOLS_H */

