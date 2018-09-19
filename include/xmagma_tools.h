/* 
 * File:   xmagma_tools.h
 * Author: hzhang
 * Tools for calculations
 * Created on July 21, 2018, 8:39 PM
 */

#ifndef XMAGMA_TOOLS_H
#define XMAGMA_TOOLS_H

#include "xmagma_forwards.h"
#include "xmagma_matrix.h"
#include "xmagma_matrix_expression.h"

namespace xmagma {
    /* Calculate dimensions of matrix expressions */
    // General case: A + B, A - B, A * B
    template< typename L, typename R, Oper O > 
    class MatrixSize {
    public: 
        static magma_int_t size1( L& lhs, R& rhs )  { return lhs.size1(); }
        static magma_int_t size2( L& lhs, R& rhs ) { return rhs.size2(); }
    };
    
    // v %*% t( v )
    template< typename L, typename R >
    class MatrixSize< L, R, V_OUTER > {
    public:
        static magma_int_t size1( L& lhs, R& rhs ) { return lhs.size1(); }
        static magma_int_t size2( L& lhs, R& rhs ) { return rhs.size1() ; }
    };
    
    // A * a 
    template< typename AnyMatrix, typename T > 
    class MatrixSize< const AnyMatrix, const T, M_SCALE > {
        public:
        static magma_int_t size1( const AnyMatrix& lhs,
            const T& rhs ) { return lhs.size1(); }
        static magma_int_t size2( const AnyMatrix& lhs,
            const T& rhs ) { return lhs.size2(); }
    };
    // A / a
    template< typename AnyMatrix, typename T > 
    class MatrixSize< const AnyMatrix, const T, M_DIV > {
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
    
    /* Calculate length of vector expressions */
    // General case: v1 + v2, v1 - v2
    template< typename L, typename R, Oper O > 
    class VectorSize {
    public: 
        static magma_int_t size( L& lhs, R& rhs ) { return lhs.size1(); }
    };
    // A * v
    template< typename AnyMatrix, typename AnyVector > 
    class VectorSize< const AnyMatrix, const AnyVector, MV_MULT > {
        public:
        static magma_int_t size( const AnyMatrix& lhs,
            const AnyVector& rhs ) { return lhs.size1(); }
    };
    // v * A
    template< typename AnyVector, typename AnyMatrix > 
    class VectorSize< const AnyVector, const AnyMatrix, VM_MULT > {
        public:
        static magma_int_t size( const AnyVector& lhs,
            const AnyMatrix& rhs ) { return lhs.size1(); }
    };
    // v * a 
    template< typename AnyVector, typename T > 
    class VectorSize< const AnyVector, const T, M_SCALE > {
        public:
        static magma_int_t size( const AnyVector& lhs,
            const T& rhs ) { return lhs.size(); }
    };
    // v / a
    template< typename AnyVector, typename T > 
    class VectorSize< const AnyVector, const T, M_DIV > {
        public:
        static magma_int_t size( const AnyVector& lhs,
            const T& rhs ) { return lhs.size(); }
    };
    // Check aliasing of matrices
    template< typename T, typename B >
    bool aliasing( const Matrix< T >&, const B& ) {
        return false;
    }
    template< typename T >
    bool aliasing( const Matrix< T >& A, const Matrix< T >& B ) {
        return A.get_pointer() == B.get_pointer();
    }
    template< typename T, typename L, typename R, Oper O >
    bool aliasing( const Matrix< T >& A, const MatrixExpression< const 
    L, const R, O >& B ) {
        return aliasing( A, B.lhs() ) || aliasing( A, B.rhs() );
    }
    // Check aliasing of vectors
    template< typename T, typename B, VecType M >
    bool aliasing( const Vector< T, M >&, const B& ) {
        return false;
    }
    template< typename T, VecType M >
    bool aliasing( const Vector< T, M >& A, const Vector< T, M >& B ) {
        return A.get_pointer() == B.get_pointer();
    }
    template< typename T, typename L, typename R, Oper O, VecType M >
    bool aliasing( const Vector< T, M >& A, const VectorExpression< const T, const 
    L, const R, O, M >& B ) {
        return aliasing( A, B.lhs() ) || aliasing( A, B.rhs() );
    }
} // xmagma                                                                                                     
#endif /* XMAGMA_TOOLS_H */

