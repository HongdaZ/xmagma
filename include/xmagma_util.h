/* 
 * File:   xmagma_util.h
 * Author: hzhang
 * Convenient templates for using different magma data types and corresponding functions
 * May add complex value types in the future
 * Created on July 20, 2018, 2:47 PM
 */

#ifndef XMAGMA_UTIL_H
#define XMAGMA_UTIL_H

#ifdef HAVE_CUBLAS
#include "cublas_v2.h"    
#include "magma_v2.h"
#else 
#include "magma.h" // for clmagma
#endif
#include "magma_lapack.h"
#include "xmagma_forwards.h" 

namespace xmagma {
    /* for magma data types */
    template < typename T>
    class Buffer {};

    template<> class Buffer< float > {
    public:
        typedef  magmaFloat_ptr type; };
    template<> class Buffer< double > {
    public:
        typedef magmaDouble_ptr type; };

    template < typename T>
    class ScalarValue {};

    template<> class ScalarValue< float > {
    public:
        typedef  float type; };
    template<> class ScalarValue< double > {
    public:
        typedef double type; };
    /* Memory allocators */
    template< typename T > 
    magma_int_t mem_creator( MagmaPtr< T > *ptr_ptr, magma_int_t n ) {
        return 1;
    };
    template<> inline
    magma_int_t mem_creator< float > ( MagmaPtr< float > *ptr_ptr,
            magma_int_t n ) {
        return magma_smalloc( ptr_ptr, n );
    }
    template<> inline
    magma_int_t mem_creator< double > ( MagmaPtr< double > *ptr_ptr,
            magma_int_t n ) {
        return magma_dmalloc( ptr_ptr, n );
    }
    template< typename T > 
    magma_int_t host_creator( MagmaPtr< T > *ptr_ptr, magma_int_t n ) {
        return 1;
    };
    template<> inline
    magma_int_t host_creator< float > ( MagmaPtr< float > *ptr_ptr,
            magma_int_t n ) {
        return magma_smalloc_cpu( ptr_ptr, n );
    }
    template<> inline
    magma_int_t host_creator< double > ( MagmaPtr< double > *ptr_ptr,
            magma_int_t n ) {
        return magma_dmalloc_cpu( ptr_ptr, n );
    }
    
}

#endif /* XMAGMA_UTIL_H */

