/* 
 * File:   xmagma_communicate.h
 * Author: hzhang
 * Transfer date between device and host
 * Created on July 23, 2018, 3:03 PM
 */

#ifndef XMAGMA_COMMUNICATE_H
#define XMAGMA_COMMUNICATE_H

#include "xmagma_R_array.h"
#include "xmagma_matrix.h"
#include "xmagma_operations.h"

namespace xmagma {
    
    /* Copy matrix from host to GPU */
    template< typename T >
    void copy( RMatrix< T >& cpu, Matrix< T >& gpu ) {
        if ( cpu.size1() == 0 || cpu.size2() == 0 ) {
            return;
        }
        if(  cpu.size1() != gpu.size1() || cpu.size2() != gpu.size2() ){
            printf( "dimension doesn't match \n" );
            return;
        }
        transfer_matrix< T >( cpu, gpu );
    }
    // GPU to host
    template< typename T >
    void copy( Matrix< T >& gpu, RMatrix< T >& cpu ) {
        if ( gpu.size1() == 0 || gpu.size2() == 0 ) {
            return;
        }
        if(  cpu.size1() != gpu.size1() || cpu.size2() != gpu.size2() ){
            printf( "dimension doesn't match \n" );
            return;
        }
        transfer_matrix< T >( gpu, cpu );
    }
}
#endif /* XMAGMA_COMMUNICATE_H */

