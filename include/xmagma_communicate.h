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
#include "xmagma_vector.h"
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
    /* Copy vector from host to GPU */
    template< typename T, VecType M >
    void copy( RVector< T >& cpu, Vector< T, M >& gpu ) {
        if ( cpu.size() == 0 || cpu.size() == 0 ) {
            return;
        }
        if(  cpu.size() != gpu.size() ){
            printf( "dimension doesn't match \n" );
            return;
        }
        transfer_vector< T, M >( cpu, gpu );
    }
    // GPU to host
    template< typename T, VecType M >
    void copy( Vector< T, M >& gpu, RVector< T >& cpu ) {
        if ( gpu.size() == 0 || gpu.size() == 0 ) {
            return;
        }
        if(  cpu.size() != gpu.size() ){
            printf( "dimension doesn't match \n" );
            return;
        }
        transfer_vector< T >( gpu, cpu );
    }
}
#endif /* XMAGMA_COMMUNICATE_H */

